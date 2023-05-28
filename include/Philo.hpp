#ifndef PHILO_HPP
#define PHILO_HPP

#include <vector>
#include <ctime>
#include <mutex>
#include <thread>
#include "./Fork.hpp"
#include "./Status.hpp"
#include "./Timer.hpp"
#include "./DiningRule.hpp"
#include "./Printer.hpp"

class Philo
{
    public :
        Philo(int number, std::vector<Fork*> &forks);
        ~Philo();
        void StartDining();
        bool CheckStatus(PhiloStatus status);
        void SetStatus(PhiloStatus status);
        bool IsDied();
        bool IsEnd();
        void ThreadJoin();
        void GrabForks();
        void Eatting();
        void Sleeping();
        bool IsOddNumber();
        bool IsFullEatCount();
        void Free();
        void SpendTime(int milliseconds);

    private:
        int _number;
        pthread_t *_pthread;
        Fork *_leftFork;
        Fork *_rightFork;
        int _eatCount;
        time_t _lastEatTime;
        std::mutex _lastEatTimeMutex;
        PhiloStatus _status;
        std::mutex _statusMutex;

        void SetLastEatTimeAtNow();
        bool GrabLeftFork();
        bool GrabRightFork();
        void GrabForksLeftFirst();
        void GrabForksRightFirst();
        void PutDownForks();
        void AddEatCount();
        void PrintPhiloStatus(PhiloStatus philoStatus);
};


#endif