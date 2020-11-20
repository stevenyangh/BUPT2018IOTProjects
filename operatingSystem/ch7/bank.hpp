#include <random>
#include <queue>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

#define NUMBER_OF_TASKS 5

// In theory, queue depth should equal number of tasks, but in practice, queue depth can be smaller
#define QUEUE_DEPTH 100

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* need = maxium - allocation */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

std::mt19937_64 randgen;

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

int searchBoolList(bool searchFor, int n, bool a[])
{
    int i;
    bool suc;
    for (i = 0, suc = false; i < n && !suc; i++)
    {
        suc = a[i] == searchFor;
    }
    if (suc)
    {
        return i - 1;
    }
    else
    {
        return -1;
    }
}

bool isSafeState()
{
    // initailizing arrays
    int work[NUMBER_OF_RESOURCES];
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        work[i] = available[i];
    }
    bool finish[NUMBER_OF_CUSTOMERS];
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        finish[i] = false;
    }

    bool flag = true;
    int trueCount = 0;
    while (flag)
    {
        flag = false;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            if (!finish[i] && lessThanList(NUMBER_OF_RESOURCES, need[i], work))
            {
                flag = true;
                addList(NUMBER_OF_RESOURCES, work, allocation[i]);
                finish[i] = true;
                trueCount++;
            }
        }
        // by the end of this turn, if any row i satisfy the requirement, the flag will be set to true, otherwise there is no row that satisfies.
    }
    return trueCount == NUMBER_OF_CUSTOMERS;
}
