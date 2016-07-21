#include <iostream>
#include <stdlib.h> 
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
	/*int rank, size, sometag=12, buf=10;
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
	MPI_Finalize();*/




    int procs_rank, procs_count; 
    int i, j, n = 1000, local_n; 
    double *local_a, *b, *local_c, *a, *c; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &procs_count); 
    MPI_Comm_rank(MPI_COMM_WORLD, &procs_rank); 
    local_n = n / procs_count; 
    local_a = (double *) malloc((local_n * n) * sizeof(double)); 
    b       = (double *) malloc(n * sizeof(double)); 
    local_c = (double *) malloc(local_n * sizeof(double)); 
    c       = (double *) malloc(n * sizeof(double)); 
    a       = (double *) malloc((n * n) * sizeof(double)); 
    //инициализируем матрицу в нулевом процессе 
    // и рассылаем его части по процессам 
    if (procs_rank == 0) 
    { 
    //матрицу удобнее рассматривать как одномерный массив но с индексами i*n+j 
        for (i=0; i<n; i++) 
            for (j=0; j<n; j++) 
                a[i*n+j]=rand(); 
        for (i=0; i<n; i++) 
            b[i] = rand(); 
    } 
    //рассылаем вектор b 
    MPI_Bcast(b, n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
    //разделяем матрицу на горизонтальные полосы 
    //шириной local_a и отпраляем процессам 
    MPI_Scatter(a, n * local_n, MPI_DOUBLE, local_a, n * local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
 
    for (i = 0; i < local_n; i++) 
        for (j = 0; j < n; j++) 
        local_c[i] += local_a[i*n+j] * b[j]; 
    //собираем результат в нулевом процессе 
    MPI_Gather(local_c, local_n, MPI_DOUBLE, c, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
    if (procs_rank == 0) 
    { 
        for (i=0; i<n; i++) 
            printf("%f3.3 \n",c[i]); 
    } 
    MPI_Finalize(); 
    return 0;


}
