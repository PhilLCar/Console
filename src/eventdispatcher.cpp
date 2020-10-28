#include <eventdispatcher.h>

namespace event {
  EventDispatcher *EventDispatcher::instance = NULL;

  EventDispatcher::EventDispatcher()
  {
    instance = this;
  }

  EventDispatcher &EventDispatcher::getDispatcher() {
    if (!instance) new EventDispatcher();
    return *instance;
  }

  void EventDispatcher::registerBuffer(EventBuffer *eventBuffer) {
    eventBuffers.insert(eventBuffer);
  }

  void EventDispatcher::unregisterBuffer(EventBuffer *eventBuffer) {
    eventBuffers.erase(eventBuffer);
  }

  void EventDispatcher::subscribe(Event *event) {
    events.insert(event);
  }
  
  void EventDispatcher::unsubscribe(Event *event) {
    events.erase(event);
  }

  void EventDispatcher::tick() {
    for (std::set<EventBuffer *>::iterator it = eventBuffers.begin(); it != eventBuffers.end(); it++) {
      for (EventBuffer *eb = *it; eb->start != eb->end; eb->start = (eb->start + 1) % EVENT_BUFFER_SIZE) {
        for (std::set<Event *>::iterator jt = events.begin(); jt != events.end(); jt++) {
          Event *e = *jt;
          if (e->check(eb->buffer[eb->start])) e->fire(eb->buffer[eb->start]);
        }
      }
    }
  }
}