#include <mpi.h>
#include <math.h>
#include <stdio.h>
void main(argc,argv)
int argc;
char *argv[];
{
      int size, i, rank, root;
      char x[4], y[4], a, alphabet;

/* Starts MPI processes ... */

   MPI_Init(&argc,&argv);                 /* starts MPI */
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);   /* get current process id */
   MPI_Comm_size(MPI_COMM_WORLD, &size);     /* get number of processes */

root = 1;
if (rank == 0) {
  printf("\n");
  printf("* MPI_Collective functions\n");
  printf("* Avaiable on 4 processors\n");
  printf("\n\n");
  printf("  Function      Proc  Sendbuf          Recvbuf\n");
  printf("  --------      ----  -------          -------\n");
}

  MPI_Barrier(MPI_COMM_WORLD);

  for (i=0; i<size; i++) {
    x[i] = ' ';
  }
  alphabet = 'a';
/* Performs a gather operation */
  x[0] = alphabet+rank;
  for (i=0; i<size; i++) {
        y[i] = ' ';
  }
  MPI_Gather(x,1,MPI_CHAR,          /* send buf,count,type */
             y,1,MPI_CHAR,          /* recv buf,count,type */
             root,                  /* root (data origin)  */
             MPI_COMM_WORLD);       /* comm,flag           */

  printf(" MPI_Gather    :  %d ", rank);
  for (i=0; i<size; i++) {
    printf("  %c",x[i]);
  }
  printf("     ");
  for (i=0; i<size; i++) {
    printf("  %c",y[i]);
  }
  printf("\n");

  MPI_Barrier(MPI_COMM_WORLD);

/* Performs an all-gather operation */
  x[0] = alphabet+rank;
  for (i=0; i<size; i++) {
    y[i] = ' ';
  }
  MPI_Allgather(x,1,MPI_CHAR,     /* send buf,count,type */
                y,1,MPI_CHAR,     /* recv buf,count,type */
                MPI_COMM_WORLD);  /* comm,flag           */

  printf(" MPI_Allgather :  %d ", rank);
  for (i=0; i<size; i++) {
    printf("  %c",x[i]);
  }
  printf("     ");
  for (i=0; i<size; i++) {
    printf("  %c",y[i]);
  }
  printf("\n");

  MPI_Barrier(MPI_COMM_WORLD);

/* Perform a scatter operation */
  for (i=0; i<size; i++) {
    x[i] = alphabet+i+rank*size;
    y[i] = ' ';
  }
  MPI_Scatter(x,1,MPI_CHAR,      /* send buf,count,type */
              y,1,MPI_CHAR,      /* recv buf,count,type */
              root,              /*    ! data origin    */
              MPI_COMM_WORLD);   /* comm,flag           */

  printf(" MPI_Scatter   :  %d ", rank);
  for (i=0; i<size; i++) {
    printf("  %c",x[i]);
  }
  printf("     ");
  for (i=0; i<size; i++) {
    printf("  %c",y[i]);
  }
  printf("\n");

  MPI_Barrier(MPI_COMM_WORLD);

/* Perform an all-to-all operation */

  for (i=0; i<size;i++) {
    x[i] = alphabet+i+rank*size;
    y[i] = ' ';
  }

  MPI_Alltoall(x,1,MPI_CHAR,       /* send buf,count,type */
               y,1,MPI_CHAR,       /* recv buf,count,type */
               MPI_COMM_WORLD);    /* comm,flag           */

  printf(" MPI_Alltoall  :  %d ", rank);
  for (i=0; i<size; i++) {
    printf("  %c",x[i]);
  }
  printf("     ");
  for (i=0; i<size; i++) {
    printf("  %c",y[i]);
  }
  printf("\n");

  MPI_Barrier(MPI_COMM_WORLD);

/* Performs a broadcast operation */
  a = ' ';
  for (i=0; i<size; i++) {
    x[i] = ' ';
    y[i] = ' ';
  }
  if(rank == root) {
    a = 'b';
    x[0] = a;
  }
  MPI_Bcast(&a,1,MPI_CHAR,          /* buf,count,type */
            root,MPI_COMM_WORLD);  /* root,comm,flag */

  printf(" MPI_Bcast     :  %d ", rank);
  for (i=0; i<size; i++) {
    printf("  %c",x[i]);
  }
  printf("     ");
  printf("  %c",a);
  printf("\n");

  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();                     /* let MPI finish up ... */

}