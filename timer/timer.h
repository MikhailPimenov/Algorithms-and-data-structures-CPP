#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
    using clock_type = std::chrono::high_resolution_clock;
    using seconds_type = std::chrono::duration < double, std::ratio < 1 > >;

    std::chrono::time_point < clock_type > m_begin;
public:
    Timer();
    virtual ~Timer();
    void reset();
    double elapsed() const;
};

#endif // TIMER_H
