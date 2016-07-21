#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readvec (int &mass_size, int *&mass);			// Read vector of int from file. Length in first el.
void genvec_rand (int &mass_size, int *&mass);		// Generating rand vec.
void genvec_anti (int &mass_size, int *&mass);		// Generating anti vec.
void genvec_half (int &mass_size, int *&mass);		// Generating half rand vec.
void swap (int &a, int &b);							// Swap two int el
double sort (int &mass_size, int *&mass);			// Sort vecor. Use 'VSTAVKA' method. Return time of work (NO!) in sec. Depend on swap.
void math (int &MofMS_size, int *&MofMS, int *&mass, int &type, int &no);
								// Count middle score of sort some(mass,type) vector some(MofMS) size in some(no) iterration in second.
								// Type of genvec: 1 - rand, 2 - anti, 3 - halfrand.

int main( )
{
	int MofMS_size, no=10, *mass, *MofMS; // MofMS - mass of mass_size, 'no' for numbers of iterations
	srand(time(NULL));
	readvec(MofMS_size,MofMS);
	cout<<"Numbers of iterations: "<<no<<'\n';
	for (int i=1; i<4; math (MofMS_size,MofMS,mass,i,no), i++);
	return 0;
}

void math (int &MofMS_size, int *&MofMS, int *&mass, int &type, int &no)
{
	double t=0;
	switch(type)
	{
	case (1): cout<<"Rand vec:\n"; break;
	case (2): cout<<"Anti vec:\n"; break;
	case (3): cout<<"Half rand vec:\n"; break;
	default: cout<<"Select type of gen vector!\n"; return;
	}
	for (int i=0; i<MofMS_size; i++)
	{
		cout<<"Mass_size: "<<MofMS[i]<<" Time in sec: ";
		// little ПОНТЫ
		for (int j=0; j<no; (type==1)?(genvec_rand(MofMS[i],mass)):((type==2)?(genvec_anti(MofMS[i],mass)):(genvec_half(MofMS[i],mass))), t=t+sort(MofMS[i],mass)/CLOCKS_PER_SEC, j++);
		t=t/no;
		cout<<t<<'\n';	
	}
	cout<<'\n';
	return;
}

double sort (int &mass_size, int *&mass)
{
	clock_t start=clock();
	for (int i=1; i<mass_size; i++)
	{
		for (int j=i-1; ((j>-1)&&(mass[j]>mass[j+1])); swap(mass[j],mass[j+1]), j--);
	}
	//for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n'; // out to stdout
	delete [] mass;
	return (clock()-start);
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
	mass = new int [mass_size];
	for (int i=0;i<mass_size;mass[i]=(rand() % (mass_size * 10) ), i++);
	return;
}


void genvec_anti (int &mass_size, int *&mass)
{
	mass = new int [mass_size];
	for (int i=0;i<mass_size;mass[i]=mass_size-i, i++);
	return;
}

void genvec_half (int &mass_size, int *&mass)
{
	mass = new int [mass_size];
	for (int i=0;i<mass_size/2;mass[i]=i, i++);
	for (int i=mass_size/2;i<mass_size;mass[i]=(rand() % (mass_size * 9) + mass_size/2), i++);
	return;
}

void swap (int &a, int &b)
{
	int c;
	c=a; a=b; b=c;
	return;
}
