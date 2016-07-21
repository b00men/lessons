#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, sometag=12, buf=10;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//cout << "Process №" << rank << " of total count " << size << endl;
	for (int i=1; i<size; i++) 
{
cout<<"send to "<<i<<'\n';
buf++;
MPI_Send (&buf, 1, MPI_INT, i, sometag, MPI_COMM_WORLD);
}
	MPI_Finalize();
}
