#define N 2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

void print_results(char *p, int a[N][N], int b[N][N], int c[N][N])
{
    int i, j;

    printf("a= \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf(" %d", a[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    printf("b= \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf(" %d", b[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    printf("%s\n", p);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf(" %d", c[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int main(int argc, char *argv[])
{
    int i, j, k, rank, size, sum = 0;
    // int a[N][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 1, 2, 3}, {4, 5, 6, 7}};
    // int b[N][N] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 1, 2, 3}, {4, 5, 6, 7}};
    int a[N][N] = {{1, 2}, {3, 4}};
    int b[N][N] = {{1, 2}, {3, 4}};
    int c[N][N], d[N][N];
    int aa[N], cc[N];
    double begin = 0.0, end = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Synchronize all processes and get the begin time
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();

    //scatter rows of first matrix to different processes
    MPI_Scatter(a, N * N / size, MPI_INT, aa, N * N / size, MPI_INT, 0, MPI_COMM_WORLD); // N = size => 1 row on 1 process

    //broadcast second matrix to all processes
    MPI_Bcast(b, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    //perform vector multiplication by all processes
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            sum = sum + aa[j] * b[j][i];
        }
        cc[i] = sum;
        sum = 0;
    }

    MPI_Gather(cc, N * N / size, MPI_INT, c, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    MPI_Finalize();
    if (rank == 0)
    {
        print_results("a x b = ", a, b, c);
        printf("On Multi-process, it took %fs seconds to execute \n\n", end - begin);
    }

    // times take in single-process
    clock_t t;
    t = clock();
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            d[i][j] = 0;
            for (k = 0; k < N; k++)
            {
                d[i][j] += a[i][k] * b[k][j];
            }
        }
    };
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    printf("On single-process, it took %f seconds to execute \n", time_taken);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf(" %d", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}