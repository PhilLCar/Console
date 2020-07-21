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

    std::set<EventBuffer &> eventBuffers;
    std::set<Event &>       events;
  };
}

#endif