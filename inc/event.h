#ifndef INC_EVENT
#define INC_EVENT

#include <tickable.h>

#include <set>
#include <fstream>
#include <iomanip>

#define EVENT_BUFFER_SIZE 1024
#define EVENT_LOG         "/var/log/events.log"

namespace event {
  struct InputEvent {
      struct timeval time;
      unsigned short type;
      unsigned short code;
      unsigned int   value;
  };

  struct EventBuffer {
      int         start;
      int         end;
      InputEvent  buffer[EVENT_BUFFER_SIZE];

      EventBuffer();
      ~EventBuffer();
  };

  class Event {
  public:
    typedef void (*EventFunction)(void *, InputEvent &);

    Event(void *);
    ~Event();

    bool check(InputEvent&);
    void fire(InputEvent&);
    long getUID();

  private:
    long  uid;
    void *sender;
    std::set<EventFunction> calls;
  };
}

#endif