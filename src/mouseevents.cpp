#include <mouseevents.h>

namespace event
{
  Event *MouseEvents::events[MOUSE_EVENT_NUM] = {};

  void MouseEvents::activate() {
    // Here create all events that relate to mouse
    // by overloading the check function
    events[MOUSE_DOWN] = new Event();
  }

  void MouseEvents::deactivate() {
    delete events[MOUSE_DOWN];
  }
}
