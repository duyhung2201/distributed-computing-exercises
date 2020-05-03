#include <stdio.h>
#include <iostream>
#include "mpi.h"
#include "fstream"

using namespace std; 

#define FILE_NAME "test.txt"


int rank0() {
    int buff[20], size, a[20], sum = 0, temp = 0;
    for (int i =0; i<20; i++)  a[i] = i;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int num = 20/size;

    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, num, MPI_INT, buff, num, MPI_INT, 0, MPI_COMM_WORLD);

    //Gather
    int gather[20];
    MPI_Gather(NULL, num, MPI_INT, gather, num, MPI_INT, 0, MPI_COMM_WORLD);

    //ALL Gather
    int allgather[20];
    MPI_Allgather(NULL, num, MPI_INT, allgather, num, MPI_INT, MPI_COMM_WORLD);

    //ALL To All
    MPI_Alltoall(a, num, MPI_INT, buff, num, MPI_INT, MPI_COMM_WORLD);

    //reduce
    for (int i=0; i<num; i++) 
        sum += buff[i];
    MPI_Reduce(&sum, &temp, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //ALL reduce
    MPI_Allreduce(&sum, &temp, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    //Scan 
    MPI_Scan(&sum, &temp, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    //Reduce Scatter
    MPI_Reduce_scatter(a, &temp, &num, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    return 0;
}

int ranki() {
    int num;

    //Broadcast
    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Scatter
    int buff[num];
    MPI_Scatter(NULL, num, MPI_INT, buff, num, MPI_INT, 0, MPI_COMM_WORLD);

    //Gather
    MPI_Gather(buff, num, MPI_INT, NULL, num, MPI_INT, 0, MPI_COMM_WORLD);

    //ALL Gather
    MPI_Allgather(buff, num, MPI_INT, NULL, num, MPI_INT, MPI_COMM_WORLD);

    //ALL To All
    int all[20];
    MPI_Alltoall(NULL, num, MPI_INT, all, num, MPI_INT, MPI_COMM_WORLD);

    //Reduce
    int sum = 0;
    for (int i=0; i<num; i++) 
        sum += buff[i];
    MPI_Reduce(&sum, NULL, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //ALL reduce
    int temp;
    MPI_Allreduce(&sum, &temp, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    //Scan 
    MPI_Scan(&sum, &temp, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    //Reduce Scatter
    MPI_Reduce_scatter(buff, &temp, &num, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    return 0;
}

int main(int argc, char* argv[])
{
    int rank, sizeFile;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) rank0();
    else ranki();

    MPI_Finalize();
    return 0;
}

