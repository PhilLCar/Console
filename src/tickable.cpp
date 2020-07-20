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

    Clock *ITickable::getClock()
    {
        return clock;
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
   
    Clock::Clock() : Clock(1.0)
    {
    }

    Clock::Clock(double frequency) :
        ticking(false),
        overrun(false),
        nOverrun(0),
        currentTick(0),
        tickables()
    {
        setFrequency(frequency);
    }

    Clock::~Clock()
    {
        stop();
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

    void Clock::start()
    {
        if (!ticking) {
            ticking = true;
            execution = new std::thread(&Clock::autotick, this);
        }
    }

    void Clock::stop()
    {
        if (ticking) {
            ticking = false;
            execution->join();
            delete execution;
        }
    }

    void Clock::tick()
    {
        for (auto *tickable : tickables) {
            tickable->ctick();
        }
    }

    void Clock::setFrequency(double frequency)
    {
        sleepTime.tv_sec = static_cast<time_t>(1.0 / frequency);
        sleepTime.tv_nsec = static_cast<long>(NANOSECONDS_IN_SECOND / frequency) % static_cast<long>(NANOSECONDS_IN_SECOND);
    }

    double Clock::getFrequency()
    {
        return 1.0 / (sleepTime.tv_sec + static_cast<double>(sleepTime.tv_nsec) / NANOSECONDS_IN_SECOND); 
    }

    unsigned long Clock::clock()
    {
        return currentTick;
    }

    bool Clock::overrunning()
    {
        return overrun;
    }

    Clock &Clock::getDefaultClock() 
    {
        return defaultClock;
    }

    void Clock::autotick() 
    {
        // This calculates the number of ticks in 5% of the iteration period
        int padding = 0.05 * (1.0 / getFrequency()) * CLOCKS_PER_SEC;

        while (ticking) {
            std::thread sleepThread(nanosleep(&sleepTime, nullptr));
            tick();
            clock_t ticks = ::clock();
            sleepThread.join();
            ticks = ::clock() - ticks;
            // If joining the sleep thread takes less than 5% of the iteration period
            // the iteration is deemed to be overruning
            overrun = ticks < padding;
            if (overrun) nOverrun++;
            currentTick += 1;
        }
    }
}