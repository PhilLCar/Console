#include <event.h>
#include <eventdispatcher.h>

namespace event {

  Event::Event() {
    EventDispatcher::getDispatcher()->subscribe(this);
  }

  Event::~Event() {
    EventDispatcher::getDispatcher()->unsubscribe(this);
  }

  bool Event::check(InputEvent &) {
    return true;
  }

  void Event::fire(InputEvent &inputEvent) {
    std::ofstream log(EVENT_LOG, std::ios_base::app);
    log <<                      std::setw(8) << inputEvent.time.tv_sec  << "."
        << std::setfill('0') << std::setw(4) << inputEvent.time.tv_usec << "::"
        <<  " Type: "  << inputEvent.type
        << ", Code: "  << inputEvent.code
        << ", Value: " << inputEvent.value;
    log.close();
    for (std::set<EventFunction>::iterator it = calls.begin(); it != calls.end(); it++) {
      (*it)(this, inputEvent);
    }
  }
}