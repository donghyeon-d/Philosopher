#ifndef DININGRULE_HPP
# define DININGRULE_HPP

class DiningRule
{
    public :
        static void SetDiningRule(int philoCount, int timeToDie, \
                    int timeToEat, int timeToSleep, int mustEat);
        static int  PhiloCount;
        static int	TimeToDie;
        static int	TimeToEat;
        static int	TimeToSleep;
        static int	MustEat;
};

#endif