# Example to compile and run the files

For mdLite.c:  
gcc mdLite.c -o mdLite -lm  
./mdLite 3 1000 400 0.0001

For mdLite_openMP.c:   
gcc mdLite_openMP.c -o mdLite_openMP -fopenmp -lm   
./mdLite_openMP

For mdLite_cilk.c:   
clang -fcilkplus mdLite_cilk.c -o mdLite_cilk -lm  
CILK_NWORKERS=[# of threads] ./mdLite_cilk

