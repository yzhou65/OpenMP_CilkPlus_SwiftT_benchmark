
#!/bin/bash

# rm -f file.txt
for i in 1 2 4 6 8 12 16 24 32 48 64
do
   # rm -f $i.txt
   # touch $i.txt
   for j in `seq 1 $2`  # how many times you want to run
   # do
        CILK_NWORKERS=$i ./fib_cilk $1 $2
    #    echo "$i thread(s) $j"
   done

   # echo "$i thread(s), $2 tests average:" >> file.txt
    #awk '{total += $1, time +=; count++} END {print total/count}' $i.txt >> file.txt

   # awk '{for (i=1;i<=NF;i++){a[i]+=$i;}} END {for (i=1;i<=NF;i++){printf "%f", a[i]/NR; printf "\t"};printf "\n"}' $i.txt >> file.txt

done