#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, procs_count; 
    int n, local_n; 
    int *a, *b, *c, *local_a, *local_c; 

    if (argc>1) n=atoi(argv[1]);

    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &procs_count); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

     
    a = new int [n * n];
    b = new int [n];
 

    if (rank == 0) {
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) a[i*n+j]=rank; 
        for (int i=0; i<n; i++) b[i] = rank;
    } 
    cout << rank << ' ' << b[0]<<'\n';
    MPI_Bcast(b, n, MPI_INT, 0, MPI_COMM_WORLD);
    cout << rank << ' ' << b[0]<<'\n';

	MPI_Finalize();
}
