#include <stdio.h>
#include <stdint.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int count;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

long fib(int n) {
    if(n < 2) {
        return n;
    }
    long i, j;
    #pragma omp task shared(i) firstprivate(n)
    {
        i = fib(n-1);
    }
    #pragma omp task shared(j) firstprivate(n)
    {
        j = fib(n-2);
    }
    #pragma omp taskwait
    return i + j;
}

long fib_cutoff(int n, int cutoff) {
//    pthread_mutex_lock(&mtx);
//    count++;
//    pthread_mutex_unlock(&mtx);

    long i, j;
    if (n < 2) {
        return n;
    }

    // In case the sequence gets too short, execute the serial version
    if (n < cutoff) {
        return fib_cutoff(n-1, cutoff) + fib_cutoff(n-2, cutoff);
    }
    else {
        #pragma omp task shared(i) firstprivate(n, cutoff)
        {
            i=fib_cutoff(n-1, cutoff);
        }
        #pragma omp task shared(j) firstprivate(n, cutoff)
        {
            j=fib_cutoff(n-2, cutoff);
        }
        #pragma omp taskwait
        return i+j;
    }
}


int main(int argc, char *argv[]) {
    int n = atoi(argv[1]); 
    int threads;
    if (argv[2] != NULL) {
        threads = atoi(argv[2]);
    }
    int cutoff = 0;
    if (argc > 3) {
        cutoff = atoi(argv[3]);
    }
    long task[50];
    long r;

    task[28] = 2 * 514229 - 1;
    task[29] = 2 * 832040 - 1;
    task[30] = 2 * 1346269 - 1;
    task[31] = 2 * 2178309 - 1;
    task[32] = 2 * 3524578 - 1;
    task[33] = 2 * 5702887 - 1;
    task[34] = 2 * 9227465 - 1;
    task[39] = 2 * 102334155 - 1;
    task[40] = 2 * 165580141 - 1;
    task[41] = 2 * 267914296 - 1;
    task[42] = 2 * 433494437 - 1;
    task[43] = 2 * 701408733 - 1;
    task[44] = 2 * (long)(1134903170) - 1;
    task[45] = 2 * (long)(1836311903) - 1;
    task[46] = 2 * (long)(2971215073) - 1;
    task[47] = 2 * (long)(4807526976) - 1;
    task[48] = 2 * (long)(7778742049) - 1;
    task[49] = 2 * (long)(12586269025) - 1;

//    start = omp_get_wtime();
    struct timeval begin, end;

        gettimeofday(&begin, NULL);

        #pragma omp parallel num_threads(threads) firstprivate(n) shared(r)
        {
            #pragma omp single
            {
                r = fib_cutoff(n, cutoff);
//                r = fib(n);
            }
        }
  //  time = omp_get_wtime() - start;
        gettimeofday(&end, NULL);

    double time = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);

    printf("time: %f, throughput: %.0f, result: %ld, threads: %d\n", time, task[n]/time, r, threads);
   // printf("%.0f    %f\n", task/time, time);
   //printf("tasks: %d, time: %f, throughput: %.0f, result: %d\n", count, time, co$
}



