#include <console.h>
#include <tickable.h>

int main(int argc, char **argv)
{
    Console::clear();
    Console::drawTitleTextBox(2, 4, 15, 6, "Test!", "Yo waddupdup, this is a test", { Console::COLOR_RED, Console::COLOR_BACKGROUND_BLUE }, Console::LINE_DOUBLE);
    //Console::drawLabel(3, 5, "Test!", { Console::COLOR_RED });
    tickable::Dummy d;
    tickable::Clock::defaultTick();
    std::cout << d.getA() << std::endl;
    d.terminate();
    tickable::Clock::defaultTick();
    tickable::Clock::defaultTick();
    std::cout << d.getA() << std::endl;
    d.initiate(tickable::Clock::getDefaultClock());
    tickable::Clock::defaultTick();
    std::cout << d.getA() << std::endl;
    std::cout << "Youpi!" << std::endl;
}