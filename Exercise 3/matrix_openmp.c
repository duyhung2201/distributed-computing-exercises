#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

#define N 1000

int A[N][N];
int B[N][N];
int C[N][N];

int main()
{
    int i, j, k;
    double start, delta;
    omp_set_num_threads(omp_get_num_procs());
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            A[i][j] = 2;
            B[i][j] = 2;
        }
    start = omp_get_wtime();
#pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            for (k = 0; k < N; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    delta = omp_get_wtime() - start;
    printf("Mutiply two matrix done in %.4g seconds\n", delta);

    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < N; j++)
    //     {
    //         printf("%d\t", C[i][j]);
    //     }
    //     printf("\n");
    // }
}