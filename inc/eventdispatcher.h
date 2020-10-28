#ifndef INC_EVENTDISPATCHER
#define INC_EVENTDISPATCHER

#include <event.h>
#include <tickable.h>

#include <set>

namespace event {
  class EventDispatcher : public tickable::ITickable {
    friend EventBuffer;
    friend Event;

  public:
    static EventDispatcher &getDispatcher();
    void tick() override;

  private:
    EventDispatcher();

    void registerBuffer(EventBuffer *);
    void unregisterBuffer(EventBuffer *);
    void subscribe(Event *);
    void unsubscribe(Event *);

  private:
    static EventDispatcher *instance;

    std::set<EventBuffer *> eventBuffers;
    std::set<Event *>       events;
  };
}

#endif