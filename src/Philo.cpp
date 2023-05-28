#include "../include/Philo.hpp"

void* ThreadMainFunc(void* parm)
{
	Philo* philo = reinterpret_cast<Philo*>(parm);
    if (philo->IsOddNumber())
    {
        philo->SpendTime(3);
    }
    while(DiningRule::PhiloCount != 1)
    {
        philo->GrabForks();
        philo->Eatting();
        philo->Sleeping();
        if (philo->CheckStatus(END) || philo->IsFullEatCount())
        {
            break;
        }

        std::this_thread::sleep_until(std::chrono::system_clock::now() + \
            std::chrono::microseconds(200));
    }

    return NULL;
}

Philo::Philo(int number, std::vector<Fork*> &forks)
{
    _number = number;

    int left = number;
    int right = number + 1;
    if (DiningRule::PhiloCount == number + 1)
        right = 0;
    _leftFork = forks[left];
    _rightFork = forks[right];
    _eatCount = 0;
    _lastEatTime = 0;
    _status = THINKING;
    _pthread = new pthread_t;
}

Philo::~Philo()
{
}

void Philo::Free()
{
    free(_pthread);
    free(this);
}

void Philo::StartDining()
{
    pthread_create(_pthread, NULL, ThreadMainFunc, this);
}

void Philo::GrabForks()
{
    if (CheckStatus(THINKING) == false)
    {
        return ;
    }

    if (IsOddNumber())
    {
        GrabForksLeftFirst();
    }
    else
    {
        GrabForksRightFirst();
    }
}

void Philo::Eatting()
{
    if (CheckStatus(GETFORK) == false)
    {
        PutDownForks();
        return ;
    }

    SetStatus(EATTING);
    
    SetLastEatTimeAtNow();
    
    PrintPhiloStatus(EATTING);

    SpendTime(DiningRule::TimeToEat);
    
    PutDownForks();

    AddEatCount();

    if (IsFullEatCount())
    {
        SetStatus(END);
    }
}

void Philo::Sleeping()
{
    if (CheckStatus(EATTING) == false)
    {
        return ;
    }
    SetStatus(SLEEPING);
    PrintPhiloStatus(SLEEPING);

    SpendTime(DiningRule::TimeToSleep);
    
    SetStatus(THINKING);
    PrintPhiloStatus(THINKING);

}

bool Philo::IsDied()
{
    bool result = false;

    _lastEatTimeMutex.lock();
    if (Timer::Now() > 1 && 
        Timer::Now() - _lastEatTime > DiningRule::TimeToDie)
    {
        result = true;
    }
    _lastEatTimeMutex.unlock();

    return result;
}

bool Philo::CheckStatus(PhiloStatus status)
{
    bool result = false;

    _statusMutex.lock();
    
    if (_status == status)
    {
        result = true;
    }

    _statusMutex.unlock();

    return result;
}

void Philo::SetStatus(PhiloStatus status)
{
    if (CheckStatus(END))
    {
        return ;
    }
    _statusMutex.lock();
    _status = status;
    _statusMutex.unlock();
}

void Philo::GrabForksLeftFirst()
{
    while (!_leftFork->Grab())
    {
        if (CheckStatus(END))
            break;
    }
    PrintPhiloStatus(GETFORK);

    while (!_rightFork->Grab())
    {
        if (CheckStatus(END))
        {
            _leftFork->PutDown();
            break;
        }
    }
    PrintPhiloStatus(GETFORK);
    SetStatus(GETFORK);
}

void Philo::GrabForksRightFirst()
{
    while (!_leftFork->Grab())
    {
        if (CheckStatus(END))
            break;
    }
    PrintPhiloStatus(GETFORK);
    while (!_rightFork->Grab())
    {
        if (CheckStatus(END))
        {
            _leftFork->PutDown();
            break;
        }
    }
    PrintPhiloStatus(GETFORK);
    SetStatus(GETFORK);
}

bool Philo::GrabLeftFork()
{
    while (_leftFork->Grab())
    {
        if (CheckStatus(END))
        {
            return false;
        }
    }
    return true;
}

bool Philo::GrabRightFork()
{
    while (_rightFork->Grab())
    {
        if (CheckStatus(END))
        {
            return false;
        }
    }
    return true;
}

void Philo::PutDownForks()
{
    if (IsOddNumber())
    {
        _leftFork->PutDown();
        _rightFork->PutDown();
    }
    else
    {
        _rightFork->PutDown();
        _leftFork->PutDown();
    }
}

void Philo::SetLastEatTimeAtNow()
{
    _lastEatTimeMutex.lock();
    _lastEatTime = Timer::Now();
    _lastEatTimeMutex.unlock();
}

void Philo::AddEatCount()
{
    _eatCount++;
}

void Philo::ThreadJoin()
{
    pthread_join(*_pthread, NULL);
}

void Philo::SpendTime(int milliseconds)
{
    time_t afterMilliseconds = Timer::Now() + milliseconds;
    while (Timer::Now() < afterMilliseconds)
    {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + \
                std::chrono::microseconds(30));
    }
}

bool Philo::IsOddNumber()
{
    if (_number % 2 == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Philo::PrintPhiloStatus(PhiloStatus philoStatus)
{
    Printer::Lock();
    if (CheckStatus(END) == false)
    {
        Printer::PrintStatus(_number, philoStatus);
    }
    Printer::Unlock();
}

bool Philo::IsFullEatCount()
{
    if (DiningRule::MustEat == _eatCount)
    {
        return true;
    }
    else
    {
        return false;
    }
}