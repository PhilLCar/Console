#include <application.h>
#include <tickable.h>
#include <event.h>
#include <eventdispatcher.h>
#include <eventfileparser.h>

int main(int argc, char **argv) {
  // CLOCKS
  tickable::Clock uiClock(10.0); // 10Hz
  tickable::Clock evClock(60.0); // 60Hz
  // EVENTS
  event::EventDispatcher *evd = event::EventDispatcher::getDispatcher();
  evd->initiate(evClock);

  event::EventBuffer *mouseBuffer = event::EventFileParser::getEventBuffer(5);
  evd->registerBuffer(mouseBuffer);

  event::Event dummy;
  // START
  evClock.start();

  console::Application::main(argc, argv);

  evd->unregisterBuffer(mouseBuffer);
  delete mouseBuffer;
  // STOP
  evClock.stop();
}