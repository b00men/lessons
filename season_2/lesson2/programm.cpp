#include <iostream>
#include <fstream>

using namespace std;

void genvec (int &mass_size, int &comb_size, int *&mass);			// Generating vec of first combination of int from file.
																	// Number of el in first el, combination in second.
void combin (int &mass_size, int &comb_size, int *&mass, int &no);	// Generating all combination in GL sequence.

int main( )
{
	int mass_size, comb_size, *mass, no=0, no_test=0;
	genvec(mass_size,comb_size,mass);
	combin(mass_size,comb_size,mass,no);
	int ch=1, zn1=1, zn2=1;
	for (int i=0; i<comb_size; ch*=(i+1), i++);
	for (int i=0; i<mass_size; zn1*=(i+1), i++);
	for (int i=0; i<(comb_size-mass_size); zn2*=(i+1), i++);
	no_test=ch/(zn1*zn2);
	cout<<"Number of combination for "<<comb_size<<" by "<<mass_size<<" eq "<<no_test<<'\n';
	cout<<"Number of combination in real: "<<no<<'\n';
	return 0;
}

void genvec (int &mass_size, int &comb_size, int *&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>comb_size>>mass_size;
	mass = new int [mass_size];
	for (int i=0;i<mass_size;mass[i]=i+1,i++);
	in.close();
	return;
}

void swap (int &a, int &b)
{
	int c;
	c=a; a=b; b=c;
	return;
}

void combin (int &mass_size, int &comb_size, int *&mass, int &no)
{
	ofstream out;
	out.open( "massout" );
	while (true)
	{
		int i,j;
		no++;
		for (int a=0;a<mass_size;out<<mass[a],a++); out<<'\n';				// Out
		for (i=mass_size-1; mass[i]==comb_size-mass_size+i+1; i--);			// Find (by right) I ( a(i)<n-i )
		if (i<0) break;														// We have last combination! Exit.
		mass[i]++; 
		for (j=i+1; j<mass_size;mass[j]=mass[j-1]+1, j++);					// Sort a(j) after I ( a(j)=a(j-1)+1 )
	}
	out.close();
	return;
}