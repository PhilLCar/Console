#ifndef INC_EVENTFILEPARSER
#define INC_EVENTFILEPARSER

#include <event.h>

#include <thread>
#include <fstream>

#define EVENT_FILE_NUMBER 30
#define EVENT_TIMEOUT_MS  -1

namespace event {

    class EventFileParser {
    public:
        static EventBuffer *getEventBuffer(int);
        static void         stopParsingAllFiles();

    private:
        EventFileParser(int);
        ~EventFileParser();

        void read();

        static EventFileParser *eventFileParsers[EVENT_FILE_NUMBER];

        int            eventFileNumber;
        std::ifstream  eventFile;
        int            eventBufferPosition;
        InputEvent     eventBuffer[EVENT_BUFFER_SIZE];
        std::thread   *readThread;
    };
}

#endif