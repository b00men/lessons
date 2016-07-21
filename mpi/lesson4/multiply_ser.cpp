#include <iostream>
#include <iomanip>
#include <stdlib.h> 
#include <omp.h>

using namespace std;
 
int main(){
    
    int n=0,m=0,w=3,j;
    cout << "Inpunt n and m for size of matrix: ";
    cin >> n >> m;
    long M1[m*n], M2[n], M3[m];
    srand (time(NULL));

    //cout << "M1:\n";
    for(int i=0; i<m; i++){
        for(int k=0; k<n; k++){
            
            //cout << "M1[" << i << "][" << k << "] = ";
            //cin >> M1[i][k];
            M1[i*n+k]=rand()%10;
        }
    }
 
    //cout << "\nM2:\n";
    for(int i=0; i<n; i++){
        //cout << "M2[" << i << "] = ";
        //cin >> M2[i];
        M2[i]=(i%2);
    }
    /*
    cout << "\nM1:\n";
    for(int i=0; i<m; i++){ 
        cout << "[";
        for(int k=0; k<n; k++) cout << setw(w) << M1[i*n+k] << ' ';        
        cout << "]\n";
    }*/
    
    //cout << "\nM2:\n";
    //cout << "[";
    //for(int i=0; i<n; i++) cout << setw(w) << M2[i] << "\n ";        
    //cout << "]\n";

    //cout << "\nPar M3:\n";
    //cout << "[";
    clock_t start=clock();
    double par, ser;
    //int proc;
    #pragma omp parallel private(j)
    {
        //proc=omp_get_num_procs();
        #pragma omp for
        for(int i=0; i<m; i++){
            M3[i]=0;
            for(j=0; j<n; j++) M3[i]+=M1[i*n+j]*M2[j];        
            //cout << setw(w) << M3[i] << ' ';
        }
    }
    //cout<<"NUM proc: "<<proc<<"\n";
    par=clock()-start;
    //cout << "]\n";
    
    //cout << "\nPar M3:\n";
    //cout << "[";
    start=clock();  
    for(int i=0; i<m; i++){
        M3[i]=0;
        for(int j=0; j<n; j++) M3[i]+=M1[i*n+j]*M2[j];        
        //cout << setw(w) << M3[i] << ' ';
    }
    ser=clock()-start;
    //cout << "]\n";
    //CLOCKS_PER_SEC
    cout<<"time of par: "<<par<<"s\ntime of ser: "<<ser<<"s\n";
}
