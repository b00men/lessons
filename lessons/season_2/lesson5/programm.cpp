#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readvec (int &mass_size, int *&mass);			// Read vector of int from file. Length in first el.
void genvec_rand (int &mass_size, int *&mass);		// Generating rand vec.
void genvec_anti (int &mass_size, int *&mass);		// Generating anti vec.
void genvec_half (int &mass_size, int *&mass);		// Generating half rand vec.
void swap (int &a, int &b);							// Swap two int el
void sort (int &mass_size, int *&mass, int &no);	// Sort vecor. Use 'VSTAVKA' method. Depend on swap.

int main( )
{
	int mass_size, *mass, no=0; // 'no' for calculate system resource usage.
	genvec_rand(mass_size,mass);
	for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n'; // while wthout out
	genvec_anti(mass_size,mass);
	for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n'; // while wthout out
	sort(mass_size,mass,no);
	// for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n'; // while wthout out
	delete [] mass;
	return 0;
}

void sort (int &mass_size, int *&mass, int &no)
{
	for (int i=1; i<mass_size; i++)
	{
		for (int j=i-1; ((j>-1)&&(mass[j]>mass[j+1])); swap(mass[j],mass[j+1]), j--);
	}
}

void readvec (int &mass_size, int *&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>mass_size;
	mass = new int [mass_size];
	for (int i=0;i<mass_size;in>>mass[i], i++);
	in.close();
	return;
}

void genvec_rand (int &mass_size, int *&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>mass_size;
	in.close();
	mass = new int [mass_size];
	for (int i=0;i<mass_size;mass[i]=(rand() % (mass_size * 3) ), i++);
	return;
}


void genvec_anti (int &mass_size, int *&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>mass_size;
	in.close();
	mass = new int [mass_size];
	for (int i=mass_size-1;i>-1;mass[i]=i, i++);
	return;
}


void genvec_half (int &mass_size, int *&mass)
{
	ifstream in;
	in.open( "massin" );
	in>>mass_size;
	in.close();
	mass = new int [mass_size];
	for (int i=0;i<mass_size;mass[i]=(rand() % (mass_size * 3) ), i++);
	return;
}
void swap (int &a, int &b)
{
	int c;
	c=a; a=b; b=c;
	return;
}
