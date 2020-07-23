#include <eventfileparser.h>

namespace event {

    EventFileParser *EventFileParser::eventFileParsers[EVENT_FILE_NUMBER] = {};

    EventFileParser::EventFileParser(int eventFileNumber) :
        eventFileNumber(eventFileNumber),
        eventBufferPosition(0)
    {
        std::string fileName = std::string("/dev/input/event") + std::to_string(eventFileNumber);
        eventFile = std::ifstream(fileName, std::ios_base::binary);
        readThread = new std::thread(&EventFileParser::read, this);
    }

    EventFileParser::~EventFileParser()
    {
        delete readThread;
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
            eventFile.read((char*)&eventBuffer[eventBufferPosition], sizeof(InputEvent));
            eventBufferPosition = (eventBufferPosition + 1) % EVENT_BUFFER_SIZE;
        }
    }
}