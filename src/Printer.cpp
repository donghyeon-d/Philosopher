#include "../include/Printer.hpp"

std::mutex Printer::_printMutex;

void Printer::PrintStatus(int id, PhiloStatus philoStatus)
{
    time_t time = Timer::Now();
    std::cout << time << " " << id + 1;
    
    switch (philoStatus)
    {
        case EATTING:
            std::cout << " is eating";
            break;
        case SLEEPING:
            std::cout << " is sleeping";
            break;
        case THINKING:
            std::cout << " is thinking";
            break;
        case GETFORK:
            std::cout << " has taken a fork";
            break;
        case DIE:
            std::cout << " died";
            break;
        default :
            break;
    }
    std::cout << "\n";
}

void Printer::Lock()
{
    _printMutex.lock();
}

void Printer::Unlock()
{
    _printMutex.unlock();
}
