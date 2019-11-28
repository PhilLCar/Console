#ifndef INC_TICKABLE
#define INC_TICKABLE

#include <vector>
#include <thread>
#include <time.h>

#define NANOSECONDS_IN_SECOND  1000000000.0
#define MICROSECONDS_IN_SECOND 1000000.0

namespace tickable {
    class Clock;
    class ITickable {
        friend class Clock;

    public:
        ITickable();
        ITickable(Clock &);
        ~ITickable();

        virtual void tick() = 0;
        void pause();
        void unpause();
        bool paused();
        void initiate(Clock &);
        void terminate();
        bool detached();

        Clock *getClock();

    private:
        void ctick();

    private:
        bool   onPause;
        int    id;
        Clock *clock;
    };

    class Clock {
    public:
        Clock();
        Clock(double);
        ~Clock();

        void add(ITickable &);
        void remove(ITickable &);
        void start();
        void stop();
        void tick();

        void          setFrequency(double);
        double        getFrequency();
        unsigned long getTick();

        void operator +=(ITickable &tickable) {
            add(tickable);
        }
        void operator -=(ITickable &tickable) {
            remove(tickable);
        }

        static Clock &getDefaultClock();
    private:
        void autotick();

    private:
        static unsigned long currentID;
        static Clock         defaultClock;

        std::thread             *execution;
        bool                     ticking;
        unsigned long            currentTick;
        struct timespec          sleepTime;
        std::vector<ITickable *> tickables;
    };

    class Dummy : public ITickable {
    public:
        void tick() {
            printf("%d\n", a++);
        }
    private:
        int a = 0;
    };
}

#endif