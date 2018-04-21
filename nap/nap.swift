import sys;
import io;

void V[];

int n = toint(argv("n"));

foreach i in [1:n] {
    V[i] = propagate();
}

start = clock() =>
    V => sleep(0) =>
    time = clock() - start;

printf("time: %f, task: %i, throughput: %f", time, n, int2float(n)/time);
