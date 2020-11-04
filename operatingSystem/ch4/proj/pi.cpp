#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

#define TRY_NUM 100
#define THREAD_NUM 4

typedef struct pi_calc_thread_data{
    int seqNum;
    unsigned seed;
    int resNum;
} piThreadData;

void *threadGenSeq(void *args) {
    piThreadData *pPTD = (piThreadData*) args;
    knuth_b gen(pPTD->seed);
    uniform_real_distribution<double> dist(0.0,1.0);
    
    //cout << "thread info{ seq: " << pPTD->seqNum << ", seed: " << pPTD->seed << "}" << endl;  
    
    double an, anp1, sum; // a(n) and a(n plus 1)
    anp1 = dist(gen);
    anp1 = anp1 * anp1;
    for(int i = 0; i < pPTD->seqNum; i++) {
	an = anp1;
	anp1 = dist(gen);
	anp1 = anp1 * anp1;
	sum = an + anp1;
	if(sum < 1.0) {
	    pPTD->resNum++;
	}
	
	//cout << "[" << an << " + " << anp1 << " = " << sum << ", res: " << pPTD->resNum << "]" << endl;
	
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    piThreadData ptd[THREAD_NUM];
    
    // init array ptd, store try num and seed for those threads.
    int eachTPT = TRY_NUM / THREAD_NUM;
    int remainderTPT = TRY_NUM % THREAD_NUM;
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    minstd_rand0 gen(seed);
    for(int i = 0; i < THREAD_NUM; i++)
    {
	ptd[i].seqNum = eachTPT;
	ptd[i].seed = gen();
	ptd[i].resNum = 0;
    }
    ptd[0].seqNum += remainderTPT;
    
    // create the threads
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
    pthread_t threads[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++)
    {
	fail = pthread_create(&threads[i], NULL, threadGenSeq, (void *)(ptd + i));
	if (fail){
	    cout << "Error: unable to create thread, " << fail << endl;
	    exit(-1);
	}
    }
    for(int i = 0; i < THREAD_NUM; i++) {
	fail = pthread_join(threads[i], NULL);
	if (fail){
	    cout << "Error: unable to join thread, " << fail << endl;
	    exit(-1);
	}
    }
    int sum = 0;
    for(int i = 0; i< THREAD_NUM; i++) {
	sum += ptd[i].resNum;

	//cout << "[sum + " << ptd[i].resNum << " = " << sum << "]";
	
    }
    cout << "pi = " << sum * 4.0 / TRY_NUM << endl;
    pthread_exit(NULL);
}




 
