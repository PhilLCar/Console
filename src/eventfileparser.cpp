#include <eventfileparser.h>

namespace event {

    EventFileParser *EventFileParser::eventFileParsers[EVENT_FILE_NUMBER] = {};

    EventFileParser::EventFileParser(int eventFileNumber) :
        eventFileNumber(eventFileNumber),
        eventBufferPosition(0)
    {
        std::string fileName = std::string("/dev/input/event") + std::to_string(eventFileNumber);
        eventPollFD[0].fd = open(fileName.c_str(), O_RDONLY | O_NONBLOCK);
        eventPollFD->events = POLLIN;
        if (eventPollFD[0].fd >= 0) {
            readThread = new std::thread(&EventFileParser::read, this);
        }
    }

    EventFileParser::~EventFileParser()
    {
        if (eventPollFD[0].fd >= 0) {
            delete readThread;
            close(eventPollFD[0].fd);
        }
    }

    EventBuffer *EventFileParser::getEventBuffer(int fileNumber)
    {
        if (!eventFileParsers[fileNumber]) {
            eventFileParsers[fileNumber] = new EventFileParser(fileNumber);
        }
        return new EventBuffer {
            .start  = 0,
            .end    = eventFileParsers[fileNumber]->eventBufferPosition,
            .buffer = eventFileParsers[fileNumber]->eventBuffer
        };
    }

    void EventFileParser::read()
    {
        int result;
        while (true) {
            result = poll(eventPollFD, 1, EVENT_TIMEOUT_MS);
            if (result > 0) {
                if (eventPollFD[0].revents & POLLIN) {
                    ssize_t rb = ::read(eventPollFD[0].fd, &eventBuffer[eventBufferPosition], sizeof(InputEvent));

                    if (rb == sizeof(InputEvent)) {
                        eventBufferPosition = (eventBufferPosition + 1) % EVENT_BUFFER_SIZE;
                    }
                }
            }
        }
    }
}