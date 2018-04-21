#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>
#include <stddef.h>

int tasks;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

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

void quickSort(int arr[], int low, int high)
{
//    pthread_mutex_lock(&mtx);
//    tasks++;
//    pthread_mutex_unlock(&mtx);
//    if (low < high - )

    if (low < high)
    {
        int pi = partition(arr, low, high);

        #pragma omp task shared(arr) //firstprivate(low, pi)
        {
            quickSort(arr, low, pi - 1);
        }
        #pragma omp task shared(arr) //firstprivate(high, pi)
        {
            quickSort(arr, pi + 1, high);
        }
        #pragma omp taskwait
    }
}

/** quicksort main function with cutoff */
void quickSort_cutoff(int* array, int left, int right, int cutoff) 
{
        int i = left, j = right;
        int tmp;
        int pivot = array[(left + right) / 2];

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


        if ((right-left)<cutoff) {
            if (left < j){ quickSort_cutoff(array, left, j, cutoff); }
            if (i < right){ quickSort_cutoff(array, i, right, cutoff); }

        }else{
            #pragma omp task
            {
                    if(left < j) { quickSort_cutoff(array, left, j, cutoff); }
            }
            #pragma omp task
            {
                    if(i < right){ quickSort_cutoff(array, i, right, cutoff); }
            }
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
    int cutoff = 1000;
//    int n = atoi(argv[1]);
    int minNum = 1;
    int lenArr = 268435456;     // 1GB data
    lenArr = atoi(argv[1]);
    int maxNum = lenArr;
    int numThreads = atoi(argv[2]);
    if (argc > 3) {
        cutoff = atoi(argv[3]);
    }
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

    double start = omp_get_wtime( );
//    #pragma omp parallel num_threads(threads) shared(arr, n)

            #pragma omp parallel num_threads(numThreads)
        {
                #pragma omp single nowait
                {
                        quickSort_parallel_internal(arr, 0, lenArr - 1, cutoff);
                }
        }

    double time = omp_get_wtime() - start;
//    printArray(arr, 50);


    tasks = lenArr;
    printf("tasks: %d, time: %f, throughput: %.0f\n", tasks, time, tasks/time);

    free(arr);
}