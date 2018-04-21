#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <cilk/cilk.h>

int main(int argc, char *argv[]) {
    int n = 100000;
    if(argc > 1) {
        n = atoi(argv[1]);
    }

    struct timeval start, end;
    double time;
    int i;
    gettimeofday(&start, NULL);

    cilk_for(i = 0; i < n; i++){
        sleep(0);
    }
    gettimeofday(&end, NULL);

    time = end.tv_sec + end.tv_usec/1000000.0 - (start.tv_sec + start.tv_usec/1000000.0);
    printf("time: %f, task: %d, throughput: %f\n", time, n, n/time);
}