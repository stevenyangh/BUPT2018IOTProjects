#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

int TRY_NUM 100;
#define THREAD_NUM 4;

int main(int argc, char *argv[]) {
    int tryPerThread[THREAD_NUM];
    
    // temp index for for-loop.
    int i;

    // init array tryPerThread, store try num for those threads.
    int eachTPT = TRY_NUM / THREAD_NUM;
    int remainderTPT = TRY_NUM % THREAD_NUM;
    for(i = 0; i < THREAD_NUM; i++)
    {
	tryPerThread[i] = eachTPT;
    }
    tryPerThread[0] += remainderTPT;

    // create the threads
    /*
      consider a sequence on R2, which is
      D2 = {(0.5, a0), (a0, a1), (a1, a2)}
      where D1 = {a0, a1, a2...} is a uniform distribute on [0,1],
      it can be prove that D2 is uniformdistribution on [0,1]X[0,1], expectation (0.5, 0.5).
    */
    for(i = 0; i < threadnum; i++)
    {
	
    }
}

double rangesquare(double x, double y) {
    return (x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5);
}

double average(double a[], int count) {
    int i;
    double sum = 0;
    for(i = 0; i < count; i++ )
    {
	sum += a[i];
    }
    return sum / count;
}

void 
