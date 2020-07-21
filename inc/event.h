#ifndef INC_EVENT
#define INC_EVENT

#include <tickable.h>

#include <set>
#include <fstream>
#include <iomanip>

#define EVENT_BUFFER_SIZE 1024
#define EVENT_LOG         "/var/log/events.log"

namespace event {
  typedef struct input_event {
      struct timeval time;
      unsigned short type;
      unsigned short code;
      unsigned int value;
  } InputEvent;

  typedef struct event_buffer {
      int         start;
      int        &end;
      InputEvent *buffer;
  } EventBuffer;

  class Event {
  public:
    typedef void (*EventFunction)(Event *, InputEvent &);

    Event();
    ~Event();

    bool check(InputEvent&);
    void fire(InputEvent&);
    long getUID();

  private:
    long uid;
    std::set<EventFunction> calls;
  };
}

#endif