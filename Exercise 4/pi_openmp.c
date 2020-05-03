/* This program is to caculate PI using OPENMP
The algorithm is based on integral representation of PI. If f(x)=4/(1+x^2), then PI is the intergral of f(x) from 0 to 1 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 8

static long steps = 1000000000;
double step;

int main(int argc, const char *argv[])
{

    int i, j;
    double x;
    double pi, sum = 0.0;
    double start, delta;

    step = 1.0 / (double)steps;

    int nthreads, tid, procs, maxt, inpar, dynamic, nested;

    /* Compute times for 1-MAX_THREADS */
    for (j = 1; j <= MAX_THREADS; j++)
    {
        omp_set_num_threads(j);
        sum = 0.0;
        start = omp_get_wtime();

        omp_set_dynamic(1);
        omp_set_nested(1);

#pragma omp parallel private(nthreads, tid)
        {
#pragma omp for reduction(+ \
                          : sum) private(x)
            for (i = 0; i < steps; i++)
            {
                x = (i + 0.5) * step;
                sum += 4.0 / (1.0 + x * x);
            }
            /* End for parallel */
            tid = omp_get_thread_num();
            pi = step * sum;
            delta = omp_get_wtime() - start;
#pragma omp master
            {
                /* Get environment information */
                procs = omp_get_num_procs();
                nthreads = omp_get_num_threads();
                maxt = omp_get_max_threads();
                inpar = omp_in_parallel();
                dynamic = omp_get_dynamic();
                nested = omp_get_nested();

                /* Print environment information */
                printf("------------------------------------------------------\n");
                printf("*  Running on %d threads: \n", j);
                printf("a. The number of processors available: %d \n", procs);
                printf("c. The maximum number of threads available: %d \n", maxt);
                printf("b.  Threads number: %d \n", tid);
                printf("b.  Number of threads: %d \n", nthreads);

                if (inpar == 0)
                    printf("d. You are IN parallel region!\n");
                else
                    printf("d. You are NOT IN parallel region.\n");

                if (dynamic == 0)
                    printf("e. Dynamic threads are NOT ENABLED.\n");
                else
                    printf("e. Dynamic threads are ENABLED!\n");

                if (nested == 0)
                    printf("f. Nested parallelism is NOT SUPPORTED.\n");
                else
                    printf("f. Nested parallelism is SUPPORTED!\n");

                /* Print PI */
                printf("PI = %.16g computed in %.4g seconds\n \n", pi, delta);
            }
        }
    }
}