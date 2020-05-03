#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int globaldata[4];/*wants to declare array this way*/
    int localdata;/*without using pointers*/

    int i;
    if (rank == 0) {

        for (i=0; i<size; i++)
            globaldata[i] = i;

        printf("1. Processor %d has data: ", rank);
        for (i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }

    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("2. Processor %d has data %d\n", rank, localdata);
    localdata= 5;
    printf("3. Processor %d now has %d\n", rank, localdata);

    MPI_Gather(&localdata, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("4. Processor %d has data: ", rank);
        for (i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }


    MPI_Finalize();
    return 0;
}
