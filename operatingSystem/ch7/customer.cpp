#include <iostream>
#include <mutex>
#include "bank.hpp"

std::mutex randomiz_mutex;
std::mutex resource_mutex;

void customer::operator() ()
{
    if(this->entry.empty())
    {
        randomiz_mutex.lock();
        // rand for vec
        randomiz_mutex.unlock();
    }
    else if(this->entry.size() < QUEUE_DEPTH)
    {
        if(resource_mutex.try_lock())
        {
            // do things
            resource_mutex.unlock();
        }
        else
        {
            randomiz_mutex.lock();
            // rand for vec
            randomiz_mutex.unlock();
        }
    }
    else
    {
        resource_mutex.lock();
        // do things
        resource_mutex.unlock();
    }
    
    
}

bool customer::setupRequest(int request[])
{
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        std::uniform_int_distribution<int> dist(0, need[this->procID][i]);
        request[i] = dist(randgen);
    }
    // we assume setup always success.
    return true;
}

int *customer::getRequest()
{
    int prev = (this->entry).front();
    if(this->poolValid[prev])
    {
        return this->taskPool[prev];
    }
    else
    {
        return nullptr;
    }
}

int request_resources(int procID, int request[])
{
    if (lessThanList(NUMBER_OF_RESOURCES, request, need[procID]))
    {
        if (lessThanList(NUMBER_OF_RESOURCES, request, available))
        {
            subList(NUMBER_OF_RESOURCES, available, request);
            addList(NUMBER_OF_RESOURCES, allocation[procID], request);
            subList(NUMBER_OF_RESOURCES, need[procID], request);
            return 0;
        }
        else
        {
            // wait
            return 1;
        }
    }
    else
    {
        // error
        std::cout << "Error, requirement exceed system capacity" << std::endl;
        return 1;
    }
}

int release_resources(int procID, int release[])
{
    // we assume releasing resource always success.
    addList(NUMBER_OF_RESOURCES, available, release);
    subList(NUMBER_OF_RESOURCES, allocation[procID], release);
    addList(NUMBER_OF_RESOURCES, need[procID], release);
    return 0;
}
