#include <application.h>
#include <tickable.h>
#include <event.h>
#include <eventdispatcher.h>
#include <eventfileparser.h>

#ifdef MOUSE_EVENTS
#include <mouseevents.h>
#endif

int main(int argc, char **argv) {
  // CLOCKS
  tickable::Clock uiClock(10.0); // 10Hz
  tickable::Clock evClock(60.0); // 60Hz
  // EVENTS
  event::EventDispatcher &evd = event::EventDispatcher::getDispatcher();
  evd.initiate(evClock);

  #ifdef MOUSE_EVENTS
  event::EventFileParser::init(5);
  event::MouseEvents::activate();
  #endif

  // START
  evClock.start();

  console::Application::main(argc, argv);

  #ifdef MOUSE_EVENTS
  event::EventFileParser::kill(5);
  event::MouseEvents::deactivate();
  #endif

  // STOP
  evClock.stop();
}