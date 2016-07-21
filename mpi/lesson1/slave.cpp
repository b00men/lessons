#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, sometag=12,  buf;
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	cout << "Process №" << rank << " of total count " << size << 
endl;
	MPI_Recv (&buf, 1, MPI_INT, 0, sometag, MPI_COMM_WORLD, 
&Stat);
	//MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
	cout<<buf<<'\n';
	MPI_Finalize();
}
