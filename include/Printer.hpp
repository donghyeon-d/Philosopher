#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <mutex>
#include <iostream>

#include "./Status.hpp"
#include "./Timer.hpp"

class Printer
{
    public :
        static void PrintStatus(int id, PhiloStatus philoStatus);
        static void Lock();
        static void Unlock();
    private :
        static std::mutex _printMutex;
};

#endif