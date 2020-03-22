// Danh sách thành viên :
//  Bùi Thị Liên
//  Ngô Quang Khải
//  Trình Xuân Hương
//  Lê Duy Hưng

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int  argc, char* argv[] )
{

    int rank, size;

    int n;

    double mb = 1e-6;

    double t_start, t_end;
   double rate = 0.0;


    MPI_Status status;

    // Khởi tạo môi trường MPI
    MPI_Init( &argc, &argv );

    // Lấy về số hiệu rank
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    // Lấy về kích thước communicator
    MPI_Comm_size( MPI_COMM_WORLD, &size );


    for ( n = 1; n < 100001; n *= 2)
    {
        //double *buffer = new double[n + 1];
        double *buffer = (double *) malloc( n * sizeof(double) );

        t_start =  MPI_Wtime();

        buffer[n] = t_start;

        if ( rank == 0)
        {
            MPI_Ssend(buffer, n, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        }
        else if ( rank == 1)
        {
            MPI_Recv(buffer, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

            t_end = MPI_Wtime();
 
            printf("Time on %d elements %lf \n", n, t_end -  buffer[n]);
            printf("Size of buffer %d \n", 8*n);
            rate =  (n*8*1e-6)/(t_end - buffer[n]);
            printf("Rate: %lf  MB/sec \n", rate);

            free(buffer);
        
    
	
        }

    }

    MPI_Finalize( ); // dọn dẹp dữ liệu MPI, hủy bỏ các hàm đang chạy
}
