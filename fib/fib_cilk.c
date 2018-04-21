#include <stdlib.h>
#include <stdio.h>
#include <cilk/cilk.h>
#include <time.h>
#include <sys/time.h>

long fib(int n) {
  if (n < 2)
    return n;
  long a = cilk_spawn fib(n-1);
  long b = fib(n-2);
  cilk_sync;
  return a + b;
}

/** compute fibonacci number parallely. When below cutoff, compute serially */
long fib_cutoff(int n, int cutoff) {
    if (n < 2) {
        return n;
    }

    // In case the sequence gets too short, execute the serial version
    if (n < cutoff) {
        return fib_cutoff(n-1, cutoff) + fib_cutoff(n-2, cutoff);
    }
    else {
        long a = cilk_spawn fib_cutoff(n-1, cutoff);
        long b = fib_cutoff(n-2, cutoff);
        cilk_sync;
        return a+b;
    }
}

int main(int argc, char *argv[]) {
  int n = 30;
  int cutoff = 0;
  if(argc > 1) {
        n = atoi(argv[1]);
  }
  if(argc > 2) {
        cutoff = atoi(argv[2]);
  }
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

  //long result = fib(n);
  long result = fib_cutoff(n, cutoff);
  
  gettimeofday(&end, NULL);

  double time = end.tv_sec + end.tv_usec/1000000.0 - (start.tv_sec + start.tv_usec/1000000.0);
  printf("result: %ld, time: %f, throughput: %.0f\n", result, time, task[n]/time);
  return 0;
}

