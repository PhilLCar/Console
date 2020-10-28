#ifndef INC_EVENTFILEPARSER
#define INC_EVENTFILEPARSER

#include <event.h>

#include <thread>
#include <fstream>

#define EVENT_FILE_NUMBER 30

namespace event {

    class EventFileParser {
    public:
        static void init(int);
        static void kill(int);
        static void killAll();

    private:
        EventFileParser(int);
        ~EventFileParser();

        void read();

        static EventFileParser *eventFileParsers[EVENT_FILE_NUMBER];

        int            eventFileNumber;
        std::ifstream  eventFile;
        EventBuffer   *eventBuffer;
        std::thread   *readThread;
    };
}

#endif