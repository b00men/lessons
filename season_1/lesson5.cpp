#include <iostream>
using namespace std;
int main() // Перемножение матриц
{
int i,j,r,size1,size2,size3,mass1[10][10],mass2[10][10],mass3[10][10];
cout<<"Enter row of A\n";
cin>>size1;
cout<<"Enter col of A (and this is row of B)\n"; 
cin>>size2;
cout<<"Enter col of B\n";
cin>>size3;

cout<<"Enter the first matrix \n";
for (i=0;i<size1;i++)
{
for (j=0;j<size2;cin>>mass1[i][j],j++);
}

cout<<"Enter the second matrix \n";
for (i=0;i<size2;i++)
{
for (j=0;j<size3;cin>>mass2[i][j],j++);
}

for (i=0;i<size1;i++)
{
for (j=0;j<size3;mass3[i][j]=0,j++);
}

for(i=0;i<size1;i++)
{
	for(j=0;j<size3;j++)//3
	{
		for(r=0;r<size2;r++)//2
		{
		mass3[i][j]=mass3[i][j]+mass1[i][r]*mass2[r][j];
		}
	}
}



cout<<"Your matrix: \n";
for (i=0;i<size1;i++)
{
for (j=0;j<size3;cout<<mass3[i][j]<<' ',j++);
cout<<'\n';
}	
return 0;
}
