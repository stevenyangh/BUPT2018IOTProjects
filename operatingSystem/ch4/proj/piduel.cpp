#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

#define TRY_NUM 100000

double an, anp1;

void *threadGenSeq(void *args) {
    unsigned int *pseed = (unsigned int*) args;
    minstd_rand0 gen(*pseed);
    uniform_real_distribution<double> dist(0.0,1.0);
    
    //cout << "thread info{ seq: " << pPTD->seqNum << ", seed: " << pPTD->seed << "}" << endl;  
    
    double temp; // a(n) and a(n plus 1)
    
    while(true) {
      temp = dist(gen);
      anp1 = temp * temp;	
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    /*
      consider a sequence on R2, which is
      D2 = {(a0, a1), (a1, a2)...}
      where D1 = {a0, a1, a2...} is a uniform distribute on [0,1],
      it can be prove that D2 is uniformdistribution on [0,1]X[0,1], expectation (0.5, 0.5).
      to further utilize the symmetrical property, map (ai-0.5)^2 to the list.
      which can be understood as make a 1/4 circle around (0,0) and r = 1, and do symmetry on both sides of y = x.
      
      we finally use such model:
      gen a = {a0, a1...a(n+1)}, an uniform on [0,1], bn = (an)^2, cn = b(n+1) + bn, return N(cn <= 1)
    */
    int fail;
    pthread_t thread;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    fail = pthread_create(&thread, NULL, threadGenSeq, (void *)&seed);
    if (fail){
      cout << "Error: unable to create thread, " << fail << endl;
      exit(-1);
    }

    usleep(1000);
    
    double a, b, sum;
    int count = 0;
    for(int i = 0; i< TRY_NUM; i++) {
	an = anp1;
	usleep(10);
	a = an;
	b = anp1;
	sum = a + b;
	if(sum < 1.0) {
	    count++;
	}
	cout << "[" << a << " + " << b << " = " << sum << ", res: " << count << "]" << endl;
	//cout << "[sum + " << ptd[i].resNum << " = " << sum << "]";	
    }
    cout << "pi = " << count * 4.0 / TRY_NUM << endl;
    return 0;
}
