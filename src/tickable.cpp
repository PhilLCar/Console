#include <tickable.h>

namespace tickable {

//==================================================================================
// ITICKABLE
//==================================================================================
    
    ITickable::ITickable() :
        onPause(false),
        clock(&Clock::getDefaultClock())
    {
        *clock += *this;
    }

    ITickable::ITickable(Clock &clock) :
        onPause(false),
        clock(&clock)
    {
        clock += *this;
    }

    ITickable::~ITickable()
    {
        terminate();
    }

    void ITickable::pause()
    {
        onPause = true;
    }

    void ITickable::unpause()
    {
        onPause = false;
    }

    bool ITickable::paused()
    {
        return onPause;
    }

    void ITickable::initiate(Clock &clock)
    {
        terminate();
        this->clock = &clock;
        clock += *this;
    }

    void ITickable::terminate()
    {
        if (clock != nullptr) {
            *clock -= *this;
            clock = nullptr;
        }
    }

    bool ITickable::detached() 
    {
        return clock == nullptr;
    }

    void ITickable::ctick()
    {
        if (!onPause) tick();
    }

//==================================================================================
// CLOCK
//==================================================================================  
    
    unsigned long Clock::currentID    = 0;
    Clock         Clock::defaultClock = Clock();
   
    Clock::Clock() :
        tickables()
    {
    }

    Clock::~Clock()
    {
        for (auto *tickable : tickables) {
            tickable->clock = nullptr;
        }
    }

    void Clock::add(ITickable &tickable)
    {
        tickable.id = currentID++;
        tickables.push_back(&tickable);
    }

    void Clock::remove(ITickable &tickable)
    {
        bool scratch = false;
        for (int i = 0; i < tickables.size() - 1; i++) {
            if (tickable.id == tickables[i]->id) scratch = true;
            if (scratch) {
                tickables[i] = tickables[i + 1];
            }
        }
        tickables.pop_back();
    }

    void Clock::tick()
    {
        for (auto *tickable : tickables) {
            tickable->ctick();
        }
    }

    void Clock::defaultTick() {
        defaultClock.tick();
    }

    Clock &Clock::getDefaultClock() 
    {
        return defaultClock;
    }
}