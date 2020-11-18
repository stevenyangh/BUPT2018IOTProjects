#include <random>
#include <queue>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

#define QUEUE_DEPTH 5
#define DEFAULT_POOLVALID                 \
    {                                     \
        false, false, false, false, false \
    }
#define DEFAULT_TASK_POOL                                       \
    {                                                           \
        {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, { 0, 0, 0 } \
    }

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* need = maxium - allocation */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

std::mt19937_64 &randgen;

class customer
{
public:
    customer(int procID) : poolValid(DEFAULT_POOLVALID), taskPool(DEFAULT_TASK_POOL)
    {
        this->procID = procID;
    }

    void operator()();

private:
    int procID;
    std::queue<int> entry;
    bool poolValid[QUEUE_DEPTH];
    int taskPool[QUEUE_DEPTH][NUMBER_OF_RESOURCES];

    bool setupRequest(int request[]);
    int pushRequest();
    int *getRequest(); 
    bool popRequest();
};

// a = a + b
void addList(int n, int a[], int b[])
{
    for (int i = 0; i < n; i++)
    {
        a[i] += b[i];
    }
}

// a = a - b
void subList(int n, int a[], int b[])
{
    for (int i = 0; i < n; i++)
    {
        a[i] -= b[i];
    }
}

// true for a less than b(a <= b), false otherwise
bool lessThanList(int n, int a[], int b[])
{
    int i = 0;
    bool flag = true;
    while (i < n && flag)
    {
        flag = a[i] <= b[i];
        i++;
    }
    return flag;
}