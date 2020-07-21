#ifndef INC_EVENTDISPATCHER
#define INC_EVENTDISPATCHER

#include <event.h>
#include <tickable.h>

#include <set>

namespace event {
  class EventDispatcher : public tickable::ITickable {
  public:
    static EventDispatcher *getDispatcher();

    void registerBuffer(EventBuffer *);
    void unregisterBuffer(EventBuffer *);
    void subscribe(Event *);
    void unsubscribe(Event *);
    void tick() override;

  private:
    EventDispatcher();

  private:
    static EventDispatcher *instance;

    std::set<std::reference_wrapper<EventBuffer>> eventBuffers;
    std::set<std::reference_wrapper<Event>>       events;
  };

  bool operator<(const std::reference_wrapper<EventBuffer>, const std::reference_wrapper<EventBuffer>);
  bool operator<(const std::reference_wrapper<Event>, const std::reference_wrapper<Event>);
}

#endif