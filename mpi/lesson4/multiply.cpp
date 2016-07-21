#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
    int procs_rank, procs_count; 
    int n=1, m=1, local_n, real_size; 
    int *a, *b, *c, *local_a, *local_c;
    double time_mpi, time_ser; 
	MPI_Group g1, g2;

    MPI_Init(0, 0);
    MPI_Comm_group( MPI_COMM_WORLD, &g1 );
    MPI_Comm_size(MPI_COMM_WORLD, &procs_count); 
    MPI_Comm_rank(MPI_COMM_WORLD, &procs_rank); 
    srand (time(NULL));

    if (argc>2) {
    	n=atoi(argv[1]);
    	m=atoi(argv[2])	
    } 

    while(n%procs_count!=0) procs_count--;
    local_n = n / procs_count;
    local_a = new int [local_n*m];
    //local_a = new int *[local_n];
    //for(int i=0;i<local_n;i++) local_a[i] = new int [n];
    local_c = new int [local_n];
    a = new int [n*m];
    //a = new int *[n];
    //for(int i=0;i<n;i++) a[i] = new int [n];
    b = new int [m];
    c = new int [m];

    int ranks[procs_count];
    for (int i=0; i<procs_count; i++) ranks[i]=i;
    MPI_Group_incl( g1, procs_count, ranks, &g2 );

    if (procs_rank == 0) {
        for (int i=0; i<n; i++) for (int j=0; j<m; j++) a[i*n+j] = rand()%10; 
        for (int i=0; i<m; i++) b[i] = rand()%10; 
    } 

    time_mpi = MPI_Wtime();
    MPI_Bcast(b, m, MPI_INT, 0, g2); 
    MPI_Scatter(a, m * local_n, MPI_INT, local_a, m * local_n, MPI_INT, 0, g2); 
    
    for (int i = 0; i < local_n; i++){
        local_c[i]=0;
        for (int j = 0; j < m; j++) local_c[i] += local_a[i*n+j] * b[j];
    } 
        
    
    MPI_Gather(local_c, local_n, MPI_INT, c, local_n, MPI_INT, 0, g2); 
    time_mpi = MPI_Wtime()-time_mpi;

    if (procs_rank == 0) 
    { 
        for (int i=0; i<m; i++) 
            cout<<c[i]<<' ';
        cout<<"\n";

        time_ser=MPI_Wtime();
        int *test_c = new int [n];
        for(int i=0; i<n; i++){
            test_c[i]=0;
            for(int j=0; j<m; j++) test_c[i]+=a[i*n+j]*b[j];        
        //cout << test_c[i] << ' ';
        }
        //cout<<"\n\n";
        time_ser=MPI_Wtime()-time_ser;
        cout.flags(std::ios::fixed);
        cout<<setprecision(10)<<"MPI time = "<<time_mpi<<" serial time = "<<time_ser<<'\n';
        for(int i=0; i<m; i++) if (test_c[i]!=c[i]) {cout<<"error!\n"; break;}
    } 
    MPI_Finalize(); 
    return 0;
}
