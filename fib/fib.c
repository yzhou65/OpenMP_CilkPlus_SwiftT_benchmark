#include <stdio.h>
#include <stdint.h>
#include <omp.h>
#include <stdlib.h>

int fib(int n) {
  int i, j;
  if (n<2)
    return n;
  else {
    i=fib(n-1);
    j=fib(n-2);
    return i+j;
  }
}


int main(int argc, char *argv[]) {
    double start;
    double time;
    int n = atoi(argv[1]);
    int task;
    if(n == 38) {
        task = 2 * 63245986 - 1;
    } else if(n == 39) {
        task = 2 * 102334155 - 1;
    } else if(n == 40) {
        task = 2 * 165580141 - 1;
    } else if(n == 37) {
        task = 2 * 39088169 - 1;
    } else if(n == 36) {
        task = 2 * 24157817 - 1;
    } else if(n == 35) {
        task = 2 * 14930352 - 1;
    } else {
        task = 1;
    }

    start = omp_get_wtime();
    int r = fib(n);
    time = omp_get_wtime() - start;
    printf("result: %d, time: %f, throughput: %.0f\n", r, time, task/time);
}