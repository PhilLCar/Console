#include <eventfileparser.h>

namespace event {

    EventFileParser *EventFileParser::eventFileParsers[EVENT_FILE_NUMBER] = {};

    void EventFileParser::init(int fileNumber)
    {
        if (!eventFileParsers[fileNumber]) {
            eventFileParsers[fileNumber] = new EventFileParser(fileNumber);
        }
    }

    void EventFileParser::kill(int fileNumber) {
        delete eventFileParsers[fileNumber];
        eventFileParsers[fileNumber] = NULL;
    }

    void EventFileParser::killAll() {
        for (int i = 0; i < EVENT_FILE_NUMBER; i++) {
            if (eventFileParsers[i]) kill(i);
        }
    }

    EventFileParser::EventFileParser(int eventFileNumber) :
        eventFileNumber(eventFileNumber)
    {
        std::string fileName = std::string("/dev/input/event") + std::to_string(eventFileNumber);
        eventFile   = std::ifstream(fileName, std::ios_base::binary);
        eventBuffer = new EventBuffer();
        readThread  = new std::thread(&EventFileParser::read, this);
    }

    EventFileParser::~EventFileParser()
    {
        pthread_cancel(readThread->native_handle());
        readThread->join();
        delete readThread;
        delete eventBuffer;
    }

    void EventFileParser::read()
    {
        int result;
        while (true) {
            eventFile.read((char*)&eventBuffer->buffer[eventBuffer->end], sizeof(InputEvent));
            eventBuffer->end = (eventBuffer->end + 1) % EVENT_BUFFER_SIZE;
        }
    }
}