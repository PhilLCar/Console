#ifndef INC_EVENTDISPATCHER
#define INC_EVENTDISPATCHER

#include <event.h>
#include <tickable.h>

#include <set>

namespace event {
  class EventDispatcher : private tickable::ITickable {
  public:
    static EventDispatcher *getDispatcher();

    void registerBuffer(EventBuffer *);
    void unregisterBuffer(EventBuffer *);
    void subscribe(Event *);
    void unsubscribe(Event *);

  private:
    EventDispatcher();
    void tick() override;

  private:
    static EventDispatcher *instance;

    std::set<std::reference_wrapper<EventBuffer>> eventBuffers;
    std::set<std::reference_wrapper<Event>>       events;
  };

  bool operator<(const std::reference_wrapper<EventBuffer> a, const std::reference_wrapper<EventBuffer> b) {
    return a.get().buffer < b.get().buffer;
  }

  bool operator<(const std::reference_wrapper<Event> a, const std::reference_wrapper<Event> b) {
    return a.get().getUID() < b.get().getUID();
  }
}

#endif