#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stddef.h>
#include <sys/time.h>
#include <pthread.h>

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


void quickSort(int* arr, int left, int right) 
{
    pthread_mutex_lock(&mtx);
    tasks++;
    pthread_mutex_unlock(&mtx);
        int i = left, j = right;
        int tmp;
        int pivot = arr[(left + right) / 2];

        /* PARTITION PART */
        while (i <= j) {
                while (arr[i] < pivot)
                        i++;
                while (arr[j] > pivot)
                        j--;
                if (i <= j) {
                        tmp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = tmp;
                        i++;
                        j--;
                }
        }
        /* RECURSION PART */
        if (left < j){ quickSort(arr, left, j);  }
        if (i< right){ quickSort(arr, i, right); }
}

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
    int lenArr = atoi(argv[1]);
    int maxNum = lenArr;
    int* arr = (int*)malloc(lenArr * sizeof(int));

    int i;
    srand(5);  //seed
    printf("Initializing the arrays with random numbers...\n");
    for(i = 0; i < lenArr; i++) {
        arr[i] = minNum + (rand()%maxNum);
    }
    printf("Initialization finished\n");

    struct timeval start, end;
    gettimeofday(&start, NULL);

    quickSort(arr, 0, lenArr-1);

    gettimeofday(&end, NULL);

    double time = end.tv_sec + end.tv_usec/1000000.0 - (start.tv_sec + start.tv_usec/1000000.0);

    printf("tasks: %d, time: %f, throughput: %.0f\n", tasks, time, tasks/time);

    free(arr);
}



