#include <eventfileparser.h>

namespace event {

    EventFileParser *EventFileParser::eventFileParsers[EVENT_FILE_NUMBER] = {};

    EventFileParser::EventFileParser(int eventFileNumber) :
        eventFileNumber(eventFileNumber),
        eventBufferPosition(0)
    {
        std::string fileName = "/dev/input/event" + eventFileNumber;
        eventFile = std::ifstream(fileName);

        readThread = new std::thread(&EventFileParser::read, this);
    }

    EventFileParser::~EventFileParser()
    {
        delete readThread;
        eventFile.close();
    }

    void EventFileParser::getEventBuffer(EventBuffer *eventBuffer, int fileNumber)
    {
        if (!eventFileParsers[fileNumber]) {
            eventFileParsers[fileNumber] = new EventFileParser(fileNumber);
        }
        eventBuffer->start  = 0;
        eventBuffer->end    = eventFileParsers[fileNumber]->eventBufferPosition;
        eventBuffer->buffer = eventFileParsers[fileNumber]->eventBuffer;
    }

    void EventFileParser::read()
    {
        while (true) {
            eventFile >> eventBuffer[eventBufferPosition];
            eventBufferPosition = (eventBufferPosition + 1) % EVENT_BUFFER_SIZE;
        }
    }

    void operator >>(std::ifstream &in, InputEvent &event)
    {
        unsigned char *memPtr = (unsigned char *)&event;
        for (int i = 0; i < sizeof(InputEvent); i++) {
            in >> memPtr[i];
        }
    }
}