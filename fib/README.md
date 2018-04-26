# Example to compile and run the files

For fib.c:  
gcc fib.c -o fib  
./fib [an integer between 30 and 48]

For fib_openmp.c:   
gcc fib_openmp.c -o fib_openmp -fopenmp  
./fib_openmp [int in 30 - 48] [# of threads] [cutoff]

For fib_cilk.c:   
clang -fcilkplus fib_cilk.c -o fib_cilk  
CILK_NWORKERS=[# of threads] ./fib_openmp [int in 30 - 48]

For fib.swift: 
stc fib.swift  
turbine -n [# of processes] fib.tic -n=[int in 30 - 48]
