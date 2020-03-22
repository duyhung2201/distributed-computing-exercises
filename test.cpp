//
//  main.cpp
//  MPI_demo
//
//  Created by Duy Hung Le on 3/21/20.
//  Copyright © 2020 Macintosh. All rights reserved.
//

#include <stdio.h>
#include "mpi.h"
#include "unistd.h"
#include "iostream"

using namespace std;
 
int main(int argc, char* argv[])
{
    int size, rank, count;
    MPI_Status status;
    double a[100],b[300];


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        // MPI_Recv(b,300,MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Send(a,100,MPI_INT, 1, 20, MPI_COMM_WORLD);
        cout << "send done" << endl;
    }
    else if (rank == 1) {
        MPI_Recv(b,300,MPI_INT, MPI_ANY_SOURCE, 20, MPI_COMM_WORLD, &status);
        
        // MPI_Send(b,100,MPI_INT, 0, 20, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

