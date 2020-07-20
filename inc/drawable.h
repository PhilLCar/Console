#ifndef INC_DRAWABLE
#define INC_DRAWABLE

namespace drawing {
    class IDrawable {
    public:
        virtual void draw() = 0;
    };
}

#endif