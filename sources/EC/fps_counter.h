#pragma once
#include <SDL_timer.h>

namespace magma_engine
{
    class Interval
    {
    private:
        unsigned int initial_;

    public:
        
        inline Interval() : initial_((unsigned int)SDL_GetTicks64())
        {
        }

        virtual ~Interval()
        {
        }

        inline unsigned int value() const
        {
            return (unsigned int)SDL_GetTicks64() - initial_;
        }
    };

    class Fps
    {
    protected:
        unsigned int m_fps;
        unsigned int m_fpscount;
        Interval m_fpsinterval;

    public:

        Fps();

        void update();

        inline int get() const
        {
            return m_fps;
        }
    };
}

