/*
  Be aware that the the arguments should not be 0
 */

#include <iostream>
#include <string>
#include <thread>

#include "customer.cpp"

#define ERROR_ARG_NUMBER 1

std::thread tl[NUMBER_OF_CUSTOMERS];

int main(int argc, char *argv[])
{
  // parse the paremeters
  if (argc != NUMBER_OF_RESOURCES)
  {
    std::cout << "error, parameter number should be "
         << NUMBER_OF_RESOURCES << ", but gives "
         << argc << std::endl;
    return ERROR_ARG_NUMBER;
  }
  else
  {
    for (int i = 0; i < argc; i++)
    {
      available[i] = atoi(argv[i]);
      if (available[i] == 0)
      {
        std::cout << "error, can't parse parameter["
             << i << "] range (0, " << NUMBER_OF_RESOURCES
             << ")." << std::endl;
        return ERROR_ARG_NUMBER;
      }
      std::random_device rd;
      std::mt19937_64 randGenerator(rd());
      randgen = randGenerator;
      
    }
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

