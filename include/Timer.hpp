#ifndef TIMER_HPP
# define TIMER_HPP

#include <sys/time.h>
#include <ctime>

class Timer
{
    public :
        static void SetStartTime();
        static time_t Now();
        static void Free();
    private :
        static timeval* _start;
};

#endif