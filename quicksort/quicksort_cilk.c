/* C implementation with cilk extension QuickSort */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <stddef.h>
#include <cilk/cilk.h>
#include <sys/time.h>

int tasks;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quickSort(int* array, int left, int right)
{
        int i = left, j = right;
        int tmp;
        int pivot = array[(left + right) / 2];

        {
                /* PARTITION PART */
                while (i <= j) {
                        while (array[i] < pivot)
                                i++;
                        while (array[j] > pivot)
                                j--;
                        if (i <= j) {
                                tmp = array[i];
                                array[i] = array[j];
                                array[j] = tmp;
                                i++;
                                j--;
                        }
                }

        }

        if (left < j){ cilk_spawn quickSort(array, left, j); }
        if (i < right){ quickSort(array, i, right); }
        cilk_sync;
}


void quickSort_cutoff(int* array, int left, int right, int cutoff)
{
        int i = left, j = right;
        int tmp;
        int pivot = array[(left + right) / 2];

        {
                /* PARTITION PART */
                while (i <= j) {
                        while (array[i] < pivot)
                                i++;
                        while (array[j] > pivot)
                                j--;
                        if (i <= j) {
                                tmp = array[i];
                                array[i] = array[j];
                                array[j] = tmp;
                                i++;
                                j--;
                        }
                }

        }

        if ( ((right-left)<cutoff) ){
                if (left < j){ quickSort_cutoff(array, left, j, cutoff); }
                if (i < right){ quickSort_cutoff(array, i, right, cutoff); }
        }
        else {
                if (left < j){ cilk_spawn quickSort_cutoff(array, left, j, cutoff); }
                if (i < right){ quickSort_cutoff(array, i, right, cutoff); }
                cilk_sync;
        }
}

/* Function to print an array */
void printArray(int* arr, int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program to test above functions
int main(int argc, char *argv[])
{
    int minNum = 1;
    int lenArr = 268435456;     // 1GB data
    lenArr = atoi(argv[1]);
    int cutoff = 1000;
    if(argc > 2) {
        cutoff = atoi(argv[2]);
    }
    int maxNum = lenArr;

    int* arr;
    arr = (int*) malloc(lenArr*sizeof(int));

    // generate random numbers into the arrays
        int i;
        srand(5); // seed
        printf("Initializing the arrays with random numbers...\n");
        for (i=0; i<lenArr; i++){
                arr[i] = minNum + (rand()%maxNum);
        }
    printf("Initialization finished\n");

        struct timeval start, end;
        gettimeofday(&start, NULL);

//      quickSort(arr, 0, lenArr - 1);

        quickSort_cutoff(arr, 0, lenArr - 1, cutoff);
        gettimeofday(&end, NULL);

//    printArray(arr, 50);

    double time = end.tv_sec + end.tv_usec/1000000.0 - (start.tv_sec + start.tv_usec/1000000.0);

    tasks = lenArr;
    printf("tasks: %d, time: %f, throughput: %.0f\n", tasks, time, tasks/time);

    free(arr);
}





