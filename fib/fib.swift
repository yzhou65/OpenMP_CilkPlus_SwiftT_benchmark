import io;
import sys;

(int o) fib(int i) {
    if(i == 0) {
        o = 0;
    }
    else if(i == 1) {
        o = 1;
    }
    else {
        o = fib(i - 1) + fib(i - 2);
    }
}

//int n = toint(argv("n"));
//task = 2 * fib(n + 1) - 1 =>
//    start = clock() =>
//        s = fib(n) =>
//            time = clock() - start;


int task[];
task[28] = 2 * 514229 - 1;
task[29] = 2 * 832040 - 1;
task[30] = 2 * 1346269 - 1;
task[31] = 2 * 2178309 - 1;
task[32] = 2 * 3524578 - 1;
task[33] = 2 * 5702887 - 1;
task[34] = 2 * 9227465 - 1;
task[35] = 2 * 14930352 - 1;
task[36] = 2 * 24157817 - 1;
task[37] = 2 * 39088169 - 1;
task[38] = 2 * 63245986 - 1;
task[39] = 2 * 102334155 - 1;
task[40] = 2 * 165580141 - 1;
task[41] = 2 * 267914296 - 1;
task[42] = 2 * 433494437 - 1;
task[43] = 2 * 701408733 - 1;
task[44] = 2 * (1134903170) - 1;
task[45] = 2 * (1836311903) - 1;
task[46] = 2 * (2971215073) - 1;
task[47] = 2 * (4807526976) - 1;
task[48] = 2 * (7778742049) - 1;
task[49] = 2 * (12586269025) - 1;


int n = toint(argv("n"));
start = clock() =>
    s = fib(n) =>
    time = clock() - start;

//printf("time: %f",time);

printf("fib[%i]: result=%i, time: %f, task: %i, throughput: %f", n, s, time, task[n], int2float(task[n]) / time);
