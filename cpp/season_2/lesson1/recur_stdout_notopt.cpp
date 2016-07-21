#include <iostream>
#include <fstream>

using namespace std;

void readvec (int &mass_size, int *&mass);	// Read vector of int from file. Length in first el.
void permut (int &mass_size, int *&mass);	// Generating all permutation (without recursion - next) in GL sequence. Depend on swap.
void swap (int &a, int &b);					// Swap two int el.

int main( )
{
	int mass_size, *mass;
	readvec(mass_size,mass);
	permut(mass_size,mass);
	return 0;
}

void readvec (int &mass_size, int *&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>mass_size;
	mass = new int [mass_size];
	for(int i=0;i<mass_size;in>>mass[i],i++);
	in.close();
	return;
}

void swap (int &a, int &b)
{
	int c;
	c=a; a=b; b=c;
	return;
}

void permut (int &mass_size, int *&mass)
{
	int i,j;
	for (int a=0;a<mass_size;cout<<mass[a],a++); cout<<'\n';				// Out
	for (i=mass_size-2; ((i>-1)&&(mass[i]>mass[i+1])); i--);				// Find I ( Max & a(i)<a(i+1) )
	if (i<0) return;														// We have last permutation! Exit.
	for (j=mass_size-1; ((j>i)&&(mass[i]>mass[j])); j--);					// Find J ( Max & j{i+1,n} & a(i)<a(j) )
	swap(mass[i],mass[j]);													// Swap a(i) & a(j)
	for (int n=mass_size-1, m=i+1;swap(mass[n],mass[m]), n<m; n--, m++);	// Revers of end ( after a(i) )
	permut(mass_size,mass);													// Recursion. For find _all_ next
}