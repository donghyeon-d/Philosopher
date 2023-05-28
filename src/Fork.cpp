#include "../include/Fork.hpp"
Fork::Fork()
{
    _status = NOTUSED;
}

Fork::~Fork()
{
}

bool Fork::Grab()
{
    _mutex.lock();
    if (_status == NOTUSED)
    {
        _status = USED;
        _mutex.unlock();
        return true;
    }
    _mutex.unlock();
    return false;
}

void Fork::PutDown()
{
    _mutex.lock();
    _status = NOTUSED;
    _mutex.unlock();
}
