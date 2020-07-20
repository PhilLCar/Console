#ifndef INC_EVENTDISPATCHER
#define INC_EVENTDISPATCHER

#include <thread>
#include <fstream>
#include <time.h>
#include <string>
#include <mutex>

#define EVENT_FILE_NUMBER 30
#define EVENT_BUFFER_SIZE 1024

namespace event {
    class EventDispatcher {
    public:
        typedef struct input_event {
            struct timeval time;
            unsigned short type;
            unsigned short code;
            unsigned int value;
        } InputEvent;

        static EventDispatcher *getEventDispatcher(int);
        static void             stopAllDispatchers();

    private:
        EventDispatcher(int);
        ~EventDispatcher();

        void read();

        static EventDispatcher *eventDispatchers[EVENT_FILE_NUMBER];

        int           eventFileNumber;
        std::ifstream eventFile;
        int           eventBufferPosition;
        InputEvent    eventBuffer[EVENT_BUFFER_SIZE];
        std::thread  *readThread;
    };

    void operator >>(std::ifstream &, EventDispatcher::InputEvent &);
}

#endif