#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

long fib(int n) {
  long i, j;
  if (n<2)
    return n;
  else {
    i=fib(n-1);
    j=fib(n-2);
    return i+j;
  }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);

      long task[50];
    task[28] = 2 * 514229 - 1;
    task[29] = 2 * 832040 - 1;
    task[30] = 2 * 1346269 - 1;
    task[31] = 2 * 2178309 - 1;
    task[32] = 2 * 3524578 - 1;
    task[33] = 2 * 5702887 - 1;
    task[34] = 2 * 9227465 - 1;
    task[38] = 2 * 63245986 - 1;
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

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int r = fib(n);
    
    gettimeofday(&end, NULL);
    double time = end.tv_sec + end.tv_usec/1000000.0 - (start.tv_sec + start.tv_usec/1000000.0);

    printf("result: %d, time: %f, throughput: %.0f\n", r, time, task[n]/time);
}

