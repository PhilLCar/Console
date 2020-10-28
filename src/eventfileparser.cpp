#include <eventfileparser.h>

namespace event {

    EventFileParser *EventFileParser::eventFileParsers[EVENT_FILE_NUMBER] = {};
    EventBuffer     *EventFileParser::eventBuffers[EVENT_FILE_NUMBER]     = {};

    void EventFileParser::init(int fileNumber)
    {
        if (!eventFileParsers[fileNumber]) {
            eventFileParsers[fileNumber] = new EventFileParser(fileNumber);
            eventBuffers[fileNumber]     = new EventBuffer();
        }
    }

    void EventFileParser::kill(int fileNumber) {
        delete eventFileParsers[fileNumber];
        eventFileParsers[fileNumber] = NULL;
        delete eventBuffers[fileNumber];
        eventBuffers[fileNumber] = NULL;
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
        eventFile = std::ifstream(fileName, std::ios_base::binary);
        readThread = new std::thread(&EventFileParser::read, this);
    }

    EventFileParser::~EventFileParser()
    {
        delete readThread;
    }

    void EventFileParser::read()
    {
        int result;
        while (true) {
            EventBuffer *eb = eventBuffers[eventFileNumber];
            eventFile.read((char*)&eb[eb->end], sizeof(InputEvent));
            eb->end = (eb->end + 1) % EVENT_BUFFER_SIZE;
        }
    }
}