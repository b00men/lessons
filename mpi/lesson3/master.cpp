#include <iostream>
#include <iomanip>

using namespace std;
 
int main(){
    
    int n=0,m=0,w=1;
    cout << "Inpunt space for format out, n and m for size of matrix: ";
    cin >> w >> n >> m;
    int M1[m][n], M2[n], M3[m];

    cout << "Input M1:\n";
    for(int i=0; i<m; i++){
        for(int k=0; k<n; k++){
            
            cout << "M1[" << i << "][" << k << "] = ";
            //cin >> M1[i][k];
            M1[i][k]=i-k;
        }
    }
 
    cout << "\nInput M2:\n";
    for(int i=0; i<n; i++){
        cout << "M2[" << i << "] = ";
        //cin >> M2[i];
        M2[i]=(i%2);
    }
    
    cout << "\nM1:\n";
    for(int i=0; i<m; i++){ 
        cout << "[";
        for(int k=0; k<n; k++) cout << setw(w) << M1[i][k] << ' ';        
        cout << "]\n";
    }
    
    cout << "\nM2:\n";
    cout << "[";
    for(int i=0; i<n; i++) cout << setw(w) << M2[i] << "\n ";        
    cout << "]\n";

    cout << "\nM3:\n";
    cout << "[";
    for(int i=0; i<m; i++){
        M3[i]=0;
        for(int j=0; j<n; j++) M3[i]+=M1[i][j]*M2[j];        
        cout << setw(w) << M3[i] << ' ';
    }
    cout << "]\n";
}