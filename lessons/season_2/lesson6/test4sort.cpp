#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readvec (int &mass_size, int *&mass);              // Read vector of int from file. Length in first el.
void genvec_rand (int &mass_size, int *&mass);          // Generating rand vec.
void genvec_anti (int &mass_size, int *&mass);          // Generating anti vec.
void genvec_half (int &mass_size, int *&mass);          // Generating half rand vec.
void swap (int &a, int &b);                                                     // Swap two int el
void sort (int l, int r, int cent, int *&mass);             // Sort part of vecor. Use 'HOAR' method. Depend on swap.
int find (int l, int r, int *&mass);                        // Find median.
void wrap (int mass_size, int *&mass);

int main( )
{
        int mass_size=10, *mass;
        srand(time(NULL));
        genvec_rand(mass_size,mass);
        wrap(mass_size,mass);
        for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n';
        return 0;
}

void wrap (int mass_size, int *&mass)
{
        sort(0,mass_size-1,find(0,mass_size-1,mass),mass);
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

void genvec_rand (int &mass_size, int *&mass)
{
        mass = new int [mass_size];
        for (int i=0;i<mass_size;mass[i]=(rand() % (mass_size * 10) ), i++);
        for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n';
        return;
}

void genvec_anti (int &mass_size, int *&mass)
{
        mass = new int [mass_size];
        for (int i=0;i<mass_size;mass[i]=mass_size-i, i++);
        for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n';
        return;
}

void genvec_half (int &mass_size, int *&mass)
{
        mass = new int [mass_size];
        for (int i=0;i<mass_size/2;mass[i]=i, i++);
        for (int i=mass_size/2;i<mass_size;mass[i]=(rand() % (mass_size * 9) + mass_size/2), i++);
        for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n';
        return;
}

void swap (int &a, int &b)
{
        int c;
        c=a; a=b; b=c;
        return;
}