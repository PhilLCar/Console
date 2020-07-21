#include <console.h>
#include <tickable.h>

int main(int argc, char **argv)
{
    drawing::Console::clear();
    drawing::Console::drawTitleTextBox(2, 4, 15, 6, "Test!", "Yo waddupdup, this is a test", { drawing::Console::COLOR_RED, drawing::Console::COLOR_BACKGROUND_BLUE }, drawing::Console::LINE_DOUBLE);
    //Console::drawLabel(3, 5, "Test!", { Console::COLOR_RED });
    tickable::Dummy d;
    tickable::Clock &clock = tickable::Clock::getDefaultClock();
    clock.start();
    getc(stdin);
    clock.stop();
}