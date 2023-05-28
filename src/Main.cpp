#include "../include/Philo.hpp"
#include "../include/Fork.hpp"
#include "../include/Monitor.hpp"
#include "../include/Parser.hpp"
#include "../include/DiningRule.hpp"
#include "../include/DiningRule.hpp"
#include "../include/Printer.hpp"

#include <vector>

int Parsing(int argc, char **argv);
std::vector<Fork*> InitForkList(int count);
std::vector<Philo*> InitPhiloList(int count, std::vector<Fork*> &forks);
void StartDining(std::vector<Philo*> &philos);
void GarbageCollect(std::vector<Philo*> &philos, std::vector<Fork*> &forks);

int main(int argc, char **argv)
{
    int philoCount = Parsing(argc, argv);
    if (philoCount == -1)
    {
        return 0;
    }

    std::vector<Fork*> forks = InitForkList(philoCount);

    std::vector<Philo*> philos = InitPhiloList(philoCount, forks);

    Monitor monitor(philos);

    StartDining(philos);
    
    monitor.StartMonitoring();

    GarbageCollect(philos, forks);

    // leak 체크를 위한 코드
    // system("leaks philo");

    return 0;
}


int Parsing(int argc, char **argv)
{
    Parser parser(argc, argv);
    if (parser.IsValidParm() != true)
    {
        std::cerr << "Error : Invalid Parm" << std::endl;

        return -1;
    }

    parser.SetDiningRule();

    return std::atoi(argv[1]);
}

std::vector<Fork*> InitForkList(int count)
{
    std::vector<Fork*> forkList;

    for (int i = 0; i < count; i++)
    {
        Fork *fork = new Fork();
        forkList.push_back(fork);
    }

    return forkList;
}

std::vector<Philo*> InitPhiloList(int count, std::vector<Fork*> &forks)
{
    std::vector<Philo*> philoList;

    for (int philoNumber = 0; philoNumber < count; philoNumber++)
    {
        Philo* philo = new Philo(philoNumber, forks);
        philoList.push_back(philo);
    }

    return philoList;
}

void StartDining(std::vector<Philo*> &philos)
{
    for (int philoNum = 0; philoNum < (int)philos.size(); philoNum++)
    {
        philos[philoNum]->StartDining();
    }
}

void GarbageCollect(std::vector<Philo*> &philos, std::vector<Fork*> &forks)
{
    for (int philoNum = 0; philoNum < (int)philos.size(); philoNum++)
    {
        philos[philoNum]->ThreadJoin();
    }

    for (int philoNum = 0; philoNum < (int)philos.size(); philoNum++)
    {
        philos[philoNum]->Free();
        free(forks[philoNum]);
    }

    Timer::Free();
}


