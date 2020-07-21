#ifndef INC_EVENTFILEPARSER
#define INC_EVENTFILEPARSER

#include <event.h>

#include <thread>
#include <fstream>
#include <time.h>
#include <string>
#include <mutex>
#include <iomanip>

#define EVENT_FILE_NUMBER 30

namespace event {
    class EventFileParser {
    public:
        static void getEventBuffer(EventBuffer *, int);
        static void stopParsingAllFiles();

    private:
        EventFileParser(int);
        ~EventFileParser();

        void read();

        static EventFileParser *eventFileParsers[EVENT_FILE_NUMBER];

        int           eventFileNumber;
        std::ifstream eventFile;
        int           eventBufferPosition;
        InputEvent    eventBuffer[EVENT_BUFFER_SIZE];
        std::thread  *readThread;
    };

    void operator >>(std::ifstream &, InputEvent &);
}

#endif