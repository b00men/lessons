#include <iostream>
#include <cmath>
using namespace std;
int main() // Заполнение произвольной матрицы числами "вертикальной змейкой"
{
	int a,n,i,j,maxi,maxj,mass[40][40];
	cout<<"Enter dimension (axb): ";
	cin>>maxi>>maxj;


	for (i=0;i<maxi;i++)
	{
	for (j=0;j<maxj;mass[i][j]=0,j++);
	}

		a=1;
	i=0;
	j=0;
	for (n=1;n<(maxi*maxj+1);n++)
	{
	mass[i][j]=n;
	
	if (a==1) i++; else i--;
	if (i==-1) {a=1; j++;i=0;}
	if (i==maxi) {a=0; j++; i=maxi-1;}

		


	}
	
	cout<<"Your matrix: \n";
	for (i=0;i<maxi;i++)
	{
	for (j=0;j<maxj;cout<<mass[i][j]<<' ',j++);
	cout<<'\n';
	}
	
	//system("pause");
	return 0;
}
