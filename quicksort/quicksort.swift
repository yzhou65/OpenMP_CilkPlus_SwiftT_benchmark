import sys;
import random;
import io;

/* This function takes last element as pivot and places all smaller
 (smaller than pivot) to a new array "less" and all greater elements
 to a new array "greater". Because element of an array is future,
 no swapping can be performed. */
(int p, int o1[], int o2[]) partition(int a[], int lo, int hi) {
    pivot = a[hi];
    int m;
    int n;
    int less[];
    int greater[];
    
    //    foreach j in [lo: hi-1] {
    //      if (a[j] <= pivot) {
    //          less[m] = a[j];
    
    
    //    }
    
    for(int j = lo, m = 0, n = 0; j < hi; j = j+1, m = m+x, n = n+y){
        int x, y;
        if (a[j] <= pivot) {
            less[m] = a[j];
            x = 1;
            y = 0;
        }
        else {
            greater[n] = a[j];
            y = 1;
            x = 0;
        }
    }
    p = pivot;
    o1 = less;
    o2 = greater;
}

(int c[]) quicksort(int b[], int lo, int hi) {
    if(lo < hi) {
        pi, le, gr = partition(b, lo, hi);
        l = quicksort(le, 0, size(le) - 1);
        g = quicksort(gr, 0, size(gr) - 1);
        c = join(l, g, pi);
    }
    else {
        c = b;
    }
}


/* This function in parallel joins the array "less", pivot, array "greater"
 at their correct positions. */
(int o[]) join(int less[], int greater[], int pivot) {
    //    int A[];
    foreach i in [0:size(less)-1] {
        o[i] = less[i];
    }
    o[size(less)] = pivot;
    foreach i in [0:size(greater)-1] {
        o[i + size(less) + 1] = greater[i];
    }
    // o = A;
}

//int arr[] = [10, 7, 6, 9, 8, 1, 5, 2, 3];

int arr[];
int count = toint(argv("count"));
//int num = toint(argv("num"));
foreach i in [0:count-1] {
    //arr[i] = randint(0, num);
    arr[i] = randint(0, count);
}


start = clock() =>
int v[] = quicksort(arr, 0, size(arr)-1) =>
    time = clock() - start;
//foreach value, index in v {
//    printf("v[%i] = %s", index, value);
//}
//printf("time=%.3f, speed=%.1f", time, int2float(9 * 8)/time);
printf("time=%.3f", time);
