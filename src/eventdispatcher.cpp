#include <eventdispatcher.h>

namespace event {
  EventDispatcher *EventDispatcher::instance = NULL;

  EventDispatcher::EventDispatcher()
  {
    instance = this;
  }

  EventDispatcher *EventDispatcher::getDispatcher() {
    if (!instance) new EventDispatcher();
    return instance;
  }

  void EventDispatcher::registerBuffer(EventBuffer *eventBuffer) {
    eventBuffers.insert(*eventBuffer);
  }

  void EventDispatcher::unregisterBuffer(EventBuffer *eventBuffer) {
    eventBuffers.erase(*eventBuffer);
  }

  void EventDispatcher::subscribe(Event *event) {
    events.insert(*event);
  }
  
  void EventDispatcher::unsubscribe(Event *event) {
    events.erase(*event);
  }

  void EventDispatcher::tick() {
    for (std::set<std::reference_wrapper<EventBuffer>>::iterator it = eventBuffers.begin(); it != eventBuffers.end(); it++) {
      EventBuffer &eb = *it;
      for (int i = eb.start; i != eb.end; i = (i + 1) % EVENT_BUFFER_SIZE) {
        for (std::set<std::reference_wrapper<Event>>::iterator jt = events.begin(); jt != events.end(); jt++) {
          Event &e = *jt;
          if (e.check(eb.buffer[i])) e.fire(eb.buffer[i]);
        }
      }
    }
  }

  bool operator<(const std::reference_wrapper<EventBuffer> a, const std::reference_wrapper<EventBuffer> b) {
    return a.get().buffer < b.get().buffer;
  }

  bool operator<(const std::reference_wrapper<Event> a, const std::reference_wrapper<Event> b) {
    return a.get().getUID() < b.get().getUID();
  }
}