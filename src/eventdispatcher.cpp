#include <eventdispatcher.h>

namespace event {




    EventDispatcher::EventDispatcher(int eventFileNumber) :
        eventFileNumber(eventFileNumber),
        eventBufferPosition(0)
    {
        std::string fileName = "/dev/input/event" + eventFileNumber;
        eventFile = std::ifstream(fileName);

        readThread = new std::thread(&EventDispatcher::read, this);
    }

    void EventDispatcher::read()
    {
        while (true) {
            eventFile >> eventBuffer[eventBufferPosition++];
        }
    }

    void operator >>(std::ifstream &in, EventDispatcher::InputEvent &event)
    {
        unsigned char *memPtr = (unsigned char *)&event;
        for (int i = 0; i < sizeof(EventDispatcher::InputEvent); i++) {
            in >> memPtr[i];
        }
    }
}