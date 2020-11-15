/*
  Be aware that the the arguments should not be 0
 */

#include<iostream>
#include<string>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

#define ERROR_ARG_NUMBER 1

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

using namespace std;
int main(int argc, char *argv[]) {
  // parse the paremeters
  if(argc != NUMBER_OF_RESOURCES) {
    cout << "error, parameter number should be "
	 << NUMBER_OF_RESOURCES << ", but gives "
	 << argc << endl;
    return ERROR_ARG_NUMBER;
  } else {
    for(int i = 0; i < argc; i++) {
      available[i] = atoi(argv[i]);
      if(available[i] == 0) {
	cout << "error, can't parse parameter["
	     << i << "] range (0, " << NUMBER_OF_RESOURCES
	     << ")." << endl;
	return ERROR_ARG_NUMBER;
      }
    }
  }
}

int request_resources(int customer_num, int request[]) {
}

int release_resources(int customer_num, int release[]) {
}
