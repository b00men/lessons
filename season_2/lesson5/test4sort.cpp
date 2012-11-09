#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void readvec (int &mass_size, int *&mass);                      // Read vector of int from file. Length in first el.
void genvec_rand (int &mass_size, int *&mass);          // Generating rand vec.
void genvec_anti (int &mass_size, int *&mass);          // Generating anti vec.
void genvec_half (int &mass_size, int *&mass);          // Generating half rand vec.
void swap (int &a, int &b);                                                     // Swap two int el
void sort (int &mass_size, int *&mass);        // Sort vecor. Use 'VSTAVKA' method. Depend on swap.

int main( )
{
        int mass_size=10, *mass;
        srand(time(NULL));
        genvec_rand(mass_size,mass);
        sort(mass_size,mass);
        genvec_anti(mass_size,mass);
        sort(mass_size,mass);
        genvec_half(mass_size,mass);
        sort(mass_size,mass);
        return 0;
}

void sort (int &mass_size, int *&mass)
{
        for (int i=1; i<mass_size; i++)
        {
                for (int j=i-1; ((j>-1)&&(mass[j]>mass[j+1])); swap(mass[j],mass[j+1]), j--);
        }
        for (int i=0;i<mass_size;cout<<mass[i]<<' ',i++); cout<<'\n';
        delete [] mass;
        return;
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