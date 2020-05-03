# Distributed_Computing_20192
Complie:
$ mpicc hello.c -o hello  (use mpic++ with .cpp file)
Run with x num threads:
$ mpirun -np x hello 

---------omp---------
Complie:
$ gcc -fopenmp -o hello.c hello
Run && show time:
$ time ./hello 
