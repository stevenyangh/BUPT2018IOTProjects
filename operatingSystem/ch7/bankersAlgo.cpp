/*
  Be aware that the the arguments should not be 0
 */


#include <string>


#include "./customer.cpp"

#define ERROR_ARG_NUMBER 1

int main(int argc, char *argv[])
{
    // parse the paremeters
    if (argc != NUMBER_OF_RESOURCES + 1)
    {
        std::cout << "error, parameter number should be "
                  << NUMBER_OF_RESOURCES<< ", but gives "
                  << argc - 1<< std::endl;
        return ERROR_ARG_NUMBER;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            available[i] = atoi(argv[i]);
            if (available[i] == 0)
            {
                std::cout << "error, can't parse parameter["
                          << i << "] range (0, " << NUMBER_OF_RESOURCES
                          << ")." << std::endl;
                return ERROR_ARG_NUMBER;
            }
        }
std::cout << "here." << std::endl;
        // setup maxium, here we use average + 1
        for(int i = 0; i < NUMBER_OF_RESOURCES; i++)
        {
            int num = available[i] / NUMBER_OF_CUSTOMERS + 1;
            for(int j = 0; j < NUMBER_OF_CUSTOMERS; j++)
            {
                maximum[j][i] = num;
            }
        }
        //setup allocation to 0
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            for(int j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                allocation[i][j] = 0;
            }
        }
        //setup need
        for(int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            for(int j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }

        std::random_device rd;
        std::mt19937_64 randGenerator(rd());
        randgen = randGenerator;

        customer cus[NUMBER_OF_CUSTOMERS] = {0, 1, 2, 3, 4};
        std::thread th[NUMBER_OF_CUSTOMERS] = {
            std::thread(cus[0]),
            std::thread(cus[1]),
            std::thread(cus[2]),
            std::thread(cus[3]),
            std::thread(cus[4])
        };
        
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
        {
            th[i].join();
        }
        return 0;
    }
}

