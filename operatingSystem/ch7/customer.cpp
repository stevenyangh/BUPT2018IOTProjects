#include <iostream>
#include <thread>
#include <mutex>
#include "./bank.hpp"

std::mutex randomiz_mutex;
std::mutex resource_mutex;

class customer
{
public:
    customer(int ID)
    {
        this->ID = ID;
        this->taskdone = 0;
        for(int i = 0; i < QUEUE_DEPTH; i++)
        {
            poolValid[i] = true;
        }
    }

    void operator()();
    int request_resources(int procID, int request[]);
    int release_resources(int procID, int release[]);

private:
    int ID;
    std::queue<int> entry;
    bool poolValid[QUEUE_DEPTH];
    int taskPool[QUEUE_DEPTH][NUMBER_OF_RESOURCES];
    int nextTask[NUMBER_OF_RESOURCES];
    int taskdone;

    bool setupRequest();
    int pushRequest(int prev);
    int *getFrontRequest();
    bool popRequest();
};

void customer::operator()()
{
    bool prevDone = true;
    int prev = 0;

    // for illustration
    int count = 0;

    while (this->taskdone < NUMBER_OF_TASKS)
    {
        if (prevDone)
        {
            randomiz_mutex.lock();
            setupRequest();
            std::cout << "customer proc[" << this->ID << "] wait for work{"
                      << this->nextTask[0] << this->nextTask[1] << this->nextTask[2] << "}" << std::endl;
            randomiz_mutex.unlock();
            prevDone = false;
            prev = searchBoolList(true, QUEUE_DEPTH, this->poolValid);
        }

        if (prev >= 0)
        {
            resource_mutex.lock();
            request_resources(this->ID, this->nextTask);
            if (isSafeState())
            {
                // for illustration
                std::cout << allocation << std::endl;

                pushRequest(prev);
                prevDone = true;
                taskdone++;
            }
            else
            {
                // for illustration
                count++;
                
                release_resources(this->ID, this->nextTask); // roll back
            }
            resource_mutex.unlock();
        }
        else
        {
            // for illustration
            count++;
            std::cout << "error, not much queue." << std::endl;
        }

        // for illustration
        if (count <= 5)
        {
            return;
        }
    }
}

bool customer::setupRequest()
{
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        std::uniform_int_distribution<int> dist(0, need[this->ID][i]);
        this->nextTask[i] = dist(randgen);
    }
    // we assume setup always success.
    return true;
}

int customer::pushRequest(int prev)
{
    if (prev >= 0)
    {
        this->entry.push(prev);
        this->poolValid[prev] = false;
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            this->taskPool[prev][i] = this->nextTask[i];
        }
    }
    return prev;
}

int *customer::getFrontRequest()
{
    int prev = (this->entry).front();
    if (this->poolValid[prev])
    {
        return this->taskPool[prev];
    }
    else
    {
        return nullptr;
    }
}

bool customer::popRequest()
{
    int prev = (this->entry).front();
    this->poolValid[prev] = true;
    this->entry.pop();
    return true;
}

int customer::request_resources(int procID, int request[])
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

int customer::release_resources(int procID, int release[])
{
    // we assume releasing resource always success.
    addList(NUMBER_OF_RESOURCES, available, release);
    subList(NUMBER_OF_RESOURCES, allocation[procID], release);
    addList(NUMBER_OF_RESOURCES, need[procID], release);
    return 0;
}
