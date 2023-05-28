#include "../include/Parser.hpp"
#include "../include/DiningRule.hpp"

Parser::Parser(int argc, char **argv)
{
    _argc = argc;
    _argv = argv;
}

bool Parser::IsValidParm()
{
    if (IsInvalidCount())
    {
        return false;
    }

    if (IsWrongType())
    {
        return false;
    }

    return true;
}

bool Parser::IsInvalidCount()
{
    if (_argc == 5 || _argc == 6)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Parser::IsWrongType()
{
    for (int i = 1; i < _argc; i++)
    {
        int j = 0;
        while (_argv[i][j] != '\0')
        {
            if (std::isdigit(_argv[i][j]) == false)
            {
                return true;
            }
            j++;
        }
    }

    return false;
}

void Parser::SetDiningRule()
{
    int philoCount = std::atoi(_argv[1]);
    int timeToDie = std::atoi(_argv[2]);
    int timeToEat = std::atoi(_argv[3]);
    int timeToSleep = std::atoi(_argv[4]);
    int mustEat = -1;
    if (_argc == 6)
    {
        mustEat = std::atoi(_argv[5]);
    }

    DiningRule::SetDiningRule(philoCount, timeToDie, \
                    timeToEat, timeToSleep, mustEat);
}