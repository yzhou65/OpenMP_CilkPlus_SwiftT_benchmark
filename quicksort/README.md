# Example to compile and run the files

For quicksort.c:  
gcc quicksort.c -o quicksort  
./quicksort [array length]

For quicksort_openmp.c:   
gcc quicksort_openmp.c -o quicksort_openmp -fopenmp  
./quicksort_openmp [array length] [# of threads] [cutoff]

For quicksort_cilk.c:   
clang -fcilkplus quicksort_cilk.c -o quicksort_cilk  
CILK_NWORKERS=[# of threads] ./quicksort_cilk [array length] [cutoff]

For quicksort.swift: 
stc quicksort.swift  
turbine -n [# of processes] quicksort.tic -count=[array length]
