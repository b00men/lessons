#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readmat (int &mass_size, int **&mass);					// Read square matrix of int from file. Length in first el.
void swap (int &a, int &b);									// Swap two int el.
int assign (int *&vec, int **&mass, int &mass_size);		// Assignment vector on matrix and return sum of cross.
int permut (int &mass_size, int *&mass, int &i, int &j);	// Generating next permutation in GL sequence. Depend on swap.
int test_diag (int &mass_size, int *&vec, int *&min_vec, int &min_sum);	// Find min summ and make min_vec on iteration.

int main( )
{
	int mass_size, **tabl, *vec, *min_vec, min_sum, i, j;
	readmat(mass_size,tabl);
	min_sum = 0x7FFFFFFF;
		vec = new int [mass_size];
	min_vec = new int [mass_size];
	for (int i=0; i<mass_size;vec[i]=i,i++); // Gen first vec
	while (true)
	{
		test_diag (mass_size,vec,min_vec,min_sum);
		if (permut (mass_size,vec,i,j)) break;
	}
	cout<<"min_sum = "<<min_sum<<"\nwith assignment: ";
	for (int a=0; a<mass_size;cout<<min_vec[a], a++);
	cout<<'\n';
	return 0;
}

int test_diag (int &mass_size, int *&vec, int *&min_vec, int &min_sum)
{
	for (int i=0; i<mass_size-2; i++)
	{
		for (int j=i+1; j<mass_size-1; j++)
		{
			if (abs(vec[i]-vec[j])==abs(i-j))
			{
				return 1;
			}
		}
	}
	
	return 0;
}

int assign (int *&vec, int **&mass, int &mass_size)
{
	int sum=0;
	for (int i=0; i<mass_size; sum+=mass[vec[i]][i], i++);
	return sum;
}

void readmat (int &mass_size, int **&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>mass_size;
	mass = new int* [mass_size];
    for (int i=0;i<mass_size;mass[i] = new int [mass_size],i++);
	for (int i=0;i<mass_size;i++) {	for (int j=0; j<mass_size;in>>mass[i][j], j++); }
	in.close();
	for (int i=0;i<mass_size;i++) {	for (int j=0; j<mass_size;cout<<mass[i][j]<<' ', j++); cout<<'\n'; }	// Debug
	return;
}

void swap (int &a, int &b)
{
	int c;
	c=a; a=b; b=c;
	return;
}

int permut (int &mass_size, int *&mass, int &i, int &j)
{
	for (i=mass_size-2; ((i>-1)&&(mass[i]>mass[i+1])); i--);				// Find I ( Max & a(i)<a(i+1) )
	if (i<0) return 1;														// We have last permutation! Exit.
	for (j=mass_size-1; ((j>i)&&(mass[i]>mass[j])); j--);					// Find J ( Max & j{i+1,n} & a(i)<a(j) )
	swap(mass[i],mass[j]);													// Swap a(i) & a(j)
	for (int n=mass_size-1, m=i+1; n>m; swap(mass[n],mass[m]), n--, m++);	// Revers of end ( after a(i) )
	return 0;
}