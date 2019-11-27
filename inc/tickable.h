#ifndef INC_TICKABLE
#define INC_TICKABLE

#include <vector>

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
        ~Clock();

        void add(ITickable &);
        void remove(ITickable &);
        void tick();

        void operator +=(ITickable &tickable) {
            add(tickable);
        }
        void operator -=(ITickable &tickable) {
            remove(tickable);
        }

        static void   defaultTick();
        static Clock &getDefaultClock();
    private:
        static unsigned long     currentID;
        static Clock             defaultClock;
        std::vector<ITickable *> tickables;
    };

    class Dummy : public ITickable {
    public:
        void tick() {
            a += 1;
        }
        int getA() {
            return a;
        }
    private:
        int a = 0;
    };
}

#endif