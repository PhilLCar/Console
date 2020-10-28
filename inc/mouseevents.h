#ifndef INC_MOUSE_EVENTS
#define INC_MOUSE_EVENTS

#include <event.h>

namespace event {
  class MouseEvents {
  public:
    static void activate();
    static void deactivate();
  
  private:
    enum AllMouseEvents {
      MOUSE_DOWN = 0,
      MOUSE_EVENT_NUM
    };

    static Event *events[MOUSE_EVENT_NUM];
  };
}

#endif