#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readvec (int &mass_size, int *&mass);			// Read vector of int from file. Length in first el.
void genvec_rand (int &mass_size, int *&mass);		// Generating rand vec.
void genvec_anti (int &mass_size, int *&mass);		// Generating anti vec.
void genvec_half (int &mass_size, int *&mass);		// Generating half rand vec.
void swap (int &a, int &b);							// Swap two int el
void math (int &MofMS_size, int *&MofMS, int *&mass, int &type, int &no);
								// Count middle score of sort some(mass,type) vector some(MofMS) size in some(no) iterration in second.
								// Type of genvec: 1 - rand, 2 - anti, 3 - halfrand.
void sort (int l, int r, int cent, int *&mass);             // Sort part of vecor. Use 'HOAR' method. Depend on swap.
int find (int l, int r, int *&mass);                        // Find median.
double wrap (int mass_size, int *&mass);

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
		for (int j=0; j<no; (type==1)?(genvec_rand(MofMS[i],mass)):((type==2)?(genvec_anti(MofMS[i],mass)):(genvec_half(MofMS[i],mass))), t=t+wrap(MofMS[i],mass)/CLOCKS_PER_SEC, j++);
		t=t/no;
		cout<<t<<'\n';	
	}
	cout<<'\n';
	return;
}

double wrap (int mass_size, int *&mass)
{
	clock_t start=clock();
    sort(0,mass_size-1,find(0,mass_size-1,mass),mass);
    delete [] mass;
	return (clock()-start);
}

void sort (int l, int r, int cent, int *&mass)
{       
        int i=l,j=r;
        if ((l>r)||(l==r)) return;
        while(true)
        {       
                for (; (i<j)&&(mass[i]<=cent); i++);
                for (; (j>i)&&(mass[j]>cent); j--);
                swap(mass[i],mass[j]);
                if ((i+1==j)||(i==j)) break;
        }
        sort(l,j-1,find(l,j-1,mass),mass);
        sort(j,r,find(j,r,mass),mass);        
}

int find (int l, int r, int *&mass)
{
        int min=mass[l], max=mass[l], median;
        for (int i=l; i<r+1; i++)
        {
                if (min>mass[i]) min=mass[i];
                if (max<mass[i]) max=mass[i];
        }
        median=(min+max)/2;
        return median;
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
