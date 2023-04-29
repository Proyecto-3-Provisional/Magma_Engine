#include "fps_counter.h"

magma_engine::Fps::Fps() : m_fps(0), m_fpscount(0)
{
}

void magma_engine::Fps::update()
{
    m_fpscount++;

    // one second elapsed? (= 1000 milliseconds)
    if (m_fpsinterval.value() > 1000)
    {
        // save the current counter value to m_fps
        m_fps = m_fpscount;

        // reset the counter and the interval
        m_fpscount = 0;
        m_fpsinterval = Interval();
    }
}
