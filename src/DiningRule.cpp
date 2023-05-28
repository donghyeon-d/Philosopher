#include "../include/DiningRule.hpp"

int DiningRule::PhiloCount;
int DiningRule::TimeToSleep;
int DiningRule::MustEat;
int DiningRule::TimeToDie;
int DiningRule::TimeToEat;

void DiningRule::SetDiningRule(int philoCount, int timeToDie, \
                int timeToEat, int timeToSleep, int mustEat)
{
    PhiloCount = philoCount;
    TimeToDie = timeToDie;
    TimeToEat = timeToEat;
    TimeToSleep = timeToSleep;
    MustEat = mustEat;
}