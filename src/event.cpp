#include <event.h>
#include <eventdispatcher.h>
#include <uidgenerator.h>

namespace event {

  EventBuffer::EventBuffer()
    : start(0)
    , end(0)
    , buffer{}
  {
    EventDispatcher::getDispatcher().registerBuffer(this);
  }

  EventBuffer::~EventBuffer() {
    EventDispatcher::getDispatcher().unregisterBuffer(this);
  }

  Event::Event(void *sender) 
    : uid(console::getNextID())
    , sender(sender)
  {
    EventDispatcher::getDispatcher().subscribe(this);
  }

  Event::~Event() {
    EventDispatcher::getDispatcher().unsubscribe(this);
  }

  bool Event::check(InputEvent &) {
    return true;
  }

  void Event::fire(InputEvent &inputEvent) {
    std::ofstream log(EVENT_LOG, std::ofstream::out | std::ofstream::app);
    log <<                      std::setw(8) << inputEvent.time.tv_sec  << "."
        << std::setfill('0') << std::setw(4) << inputEvent.time.tv_usec << "::"
        <<  " Type: "  << inputEvent.type
        << ", Code: "  << inputEvent.code
        << ", Value: " << inputEvent.value
        << std::endl;
    log.close();
    for (std::set<EventFunction>::iterator it = calls.begin(); it != calls.end(); it++) {
      (*it)(sender, inputEvent);
    }
  }

  long Event::getUID() {
    return uid;
  }
}