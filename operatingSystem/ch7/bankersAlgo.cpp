/*
  Be aware that the the arguments should not be 0
 */

#include <iostream>
#include <string>
#include <random>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

#define ERROR_ARG_NUMBER 1

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* need = maxium - allocation */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

using namespace std;
int main(int argc, char *argv[])
{
  // parse the paremeters
  if (argc != NUMBER_OF_RESOURCES)
  {
    cout << "error, parameter number should be "
         << NUMBER_OF_RESOURCES << ", but gives "
         << argc << endl;
    return ERROR_ARG_NUMBER;
  }
  else
  {
    for (int i = 0; i < argc; i++)
    {
      available[i] = atoi(argv[i]);
      if (available[i] == 0)
      {
        cout << "error, can't parse parameter["
             << i << "] range (0, " << NUMBER_OF_RESOURCES
             << ")." << endl;
        return ERROR_ARG_NUMBER;
      }
    }
  }
}

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
    cout << "Error, requirement exceed system capacity" << endl;
    return 1;
  }
}

int release_resources(int procID, int release[])
{
  // we assume releasing resource always success.
  addList(NUMBER_OF_RESOURCES, available, request);
  subList(NUMBER_OF_RESOURCES, allocation[procID], request);
  addList(NUMBER_OF_RESOURCES, need[procID], request);
  return 0;
}
