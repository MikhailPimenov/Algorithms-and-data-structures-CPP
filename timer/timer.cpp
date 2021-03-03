#include "timer.h"

Timer::Timer(): m_begin { clock_type::now() }
{}
Timer::~Timer()
{}
void Timer::reset()
{
    m_begin = clock_type::now();
}
double Timer::elapsed() const
{
    return std::chrono::duration_cast < seconds_type > ( clock_type::now() - m_begin ).count();
}

