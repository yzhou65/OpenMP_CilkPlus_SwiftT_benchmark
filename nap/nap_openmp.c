#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

double cpu_time() {
    double value;
    value = ( double ) clock ( ) / ( double ) CLOCKS_PER_SEC;

    return value;
}

int main(int argc, char *argv[]) {
    int n = 100000;
    if(argc > 1) {
        n = atoi(argv[1]);
    }
    int threads = 2;
    if(argc > 2) {
        threads = atoi(argv[2]);
    }

    double start;
    double time;

    // start = cpu_time();
    start = omp_get_wtime();

    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for
        for(int i = 0; i < n; i++)
        {
            sleep(0);
        }
    }
    //time = cpu_time() - start;

    time = omp_get_wtime() - start;
    printf("time: %f, task: %d, throughput: %f\n", time, n, n/time);
}