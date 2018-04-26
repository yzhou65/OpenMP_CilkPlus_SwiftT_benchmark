# Example to compile and run the files

For nap.c:  
gcc nap.c -o nap  
./nap [# of times sleep(0)]

For nap_openmp.c:   
gcc nap_openmp.c -o nap_openmp -fopenmp  
./nap_openmp [# of times sleep(0)]

For nap_cilk.c:   
clang -fcilkplus nap_cilk.c -o nap_cilk  
CILK_NWORKERS=[# of threads] ./nap_cilk [# of times sleep(0)]

For nap.swift: 
stc nap.swift  
turbine -n [# of processes] nap.tic -n=[# of times sleep(0)]
