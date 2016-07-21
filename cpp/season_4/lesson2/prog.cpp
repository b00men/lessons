/*
	Как правильно обрабатывать логику поведения `>>` когда на вход идет мусор (нужна ли защита от EOF)?
	Есть ли возможность перегружать функции "на лету" (что выгодне gen\sort или др. метод) ?
	Некоректна перегрузка `+`. `=` должно получать в аргументе Array& а не Array
.*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "prog.h"
using namespace std;

int main()
{ 	
	/*int m[6] = {4, 25, 30};
	Array ar1(m,6); // создали массив 1, 2, 3, 0
	int m1[5] = {-7, 5, 0};
	Array ar2(m1,5); // создали массив -7, 5, 0, 0, 0
	Array ar3(ar1+ar2);
	 // сложили массивы
	
	//cout<<ar1<<'\n';
	//cout<<ar2<<'\n';
	//cout<<ar1<<'\n';
	cout<<ar3<<'\n'; // вывод 1, 2, 3, 0, -7, 5, 0, 0, 0*/
	
	int no=1, type=0; //'no' for numbers of iterations
	Array MofMS("MofMS"); //MofMS - mass of mass_size, 
	cout<<"Numbers of iterations: "<<no<<'\n';	
	for (int i=4; i<5; math(MofMS,i,no), i++);
	
	return 0;
}

Array Array::operator +(Array &ar)
{
	//delete []a;
	cout<<(size_a+ar.size_a)<<'\n';
	int *tmp = new int[size_a + ar.size_a];
	int i;
	for(i = 0;i < size_a; tmp[i] = a[i], i++);
	/*for(i = 0;i < size_a; cout<<tmp[i]<<", ", i++);
	cout<<'\n';
	for(i = 0;i < ar.size_a; cout<<ar.a[i]<<", ", i++);
	cout<<'\n';*/
	for(;i < size_a + ar.size_a;tmp[i] = ar.a[i - size_a], i++);
	Array result(tmp,size_a + ar.size_a);
	cout<<result<<'\n';
	return result;
}

void math (Array &MofMS, int &type, int &no)
{
	double t=0;
	Array mass;
	cout<<((type<3)?("Slow"):("Fast"))<<" sort:\n";
	switch(type%3)
	{
	case (0): cout<<"Rand vec:\n"; break;
	case (1): cout<<"Anti vec:\n"; break;
	case (2): cout<<"Half rand vec:\n"; break;
	default: cout<<"Select type of gen vector!\n"; return;
	}
	for (int i=0; i<(int)MofMS; i++)
	{
		cout<<"Mass_size: "<<MofMS[i]<<" Time in sec: ";
		// little ПОНТЫ
		for (int j=0; j<no; mass.gen(type,MofMS[i]), t=t+mass.sort(type<3)/CLOCKS_PER_SEC, j++);
		t=t/no;
		cout<<t<<'\n';	
	}
	cout<<'\n';
	return;
}

void swap (int &a, int &b)
{
    int c;
    c=a; a=b; b=c;
    return;
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

Array::Array(int *a1, int size_a1)
{
	size_a=size_a1;
	a = new int [size_a];
	for (int i=0; i<size_a; a[i]=a1[i], i++);
}

Array::Array(Array & ar)
{
	size_a = ar.size_a;
	a = new int [size_a];
	for (int i=0; i<size_a; a[i]=ar.a[i], i++);
}

Array::Array(const char* file)
{
	ifstream in;
	in.open(file);
	in>>size_a;
	a = new int [size_a];
	for (int i=0;i<size_a;in>>a[i],i++);
	in.close();
}

void Array::print()
{
	for (int i = 0; i < size_a; cout << a[i] << ' ', i++);
	cout<<endl;
}

void Array::hand()
{
	cout<<"Ввод масива:\n";
	cin>>size_a;
	a = new int[size_a];
	for(int i = 0; i < size_a;cin>>a[i], i++);
}

void Array::gen(int &type, int &size)
{
	switch(type%3)
	{
		case (0): this->rand(size); break;
		case (1): this->anti(size); break;
		case (2): this->half(size); break;
		default: cout<<"Select type of gen vector!\n"; return;
	}
}

void Array::half(int size)
{
	srand ((int)time(NULL));
	size_a=size;
	a = new int[size_a];
	for (int i=0;i<size_a/2;a[i]=i, i++);
	for (int i=size_a/2;i<size_a;a[i]=(std::rand() % (size_a * 9) + size_a/2), i++);
	return;
}

void Array::anti(int size)
{
	size_a=size;
	a = new int[size_a];
	for (int i=0;i<size_a;a[i]=size_a-i, i++);
	return;
}

void Array::rand(int size)
{
	srand ((int)time(NULL));
	size_a=size;
	a = new int[size_a];
	for(int i=0; i<size_a; a[i]=std::rand()%(size_a * 10), i++);
}

double Array::sort (bool type)
{
	clock_t start=clock();
	if (type) (*this).slow_sort();
	else (*this).fast_sort();
	return (clock()-start);
}

void Array::slow_sort ()	//(int &mass_size, int *&mass)
{
    for (int i=1; i<size_a; i++)
    {
            for (int j=i-1; ((j>-1)&&(a[j]>a[j+1])); swap(a[j],a[j+1]), j--);
    }
}

void Array::fast_sort_work (int l, int r, int cent, int *&mass)
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
    fast_sort_work(l,j-1,find(l,j-1,mass),mass);
    fast_sort_work(j,r,find(j,r,mass),mass);        
}

void Array::fast_sort ()
{
	//cout<<"hello\n";
	(*this).fast_sort_work(0,size_a-1,find(0,size_a-1,a),a);
}

Array Array::operator +=(Array &ar)
{
 int *tmp = new int[size_a];
 int i;
 for(i = 0;i < size_a;tmp[i] = a[i],i++);
 delete []a;
 a = new int [size_a + ar.size_a];
 for(i = 0;i < size_a; a[i] = tmp[i], i++);
 for(i = size_a; i < size_a + ar.size_a; a[i] = ar.a[i - size_a], i++);
 size_a += ar.size_a;
 return *this;
}

Array Array::operator =(Array &ar)
{
 if(this != &ar)
 {
  size_a = ar.size_a;
  a = new int [size_a];
  for (int i = 0; i < size_a; i++)
    a[i] = ar.a[i];
 }
 return *this;
}

Array Array::operator ++()
{
	for(int i = 0; i < size_a; a[i]++, i++);
	return *this;
}

ostream& operator << (ostream& strm, Array &ar)
{	
	for (int i = 0; i < ar.size_a; strm<<ar.a[i]<<' ', i++);
	return strm;
}

istream& operator >> (istream& strm, Array &ar)
{
 int size;

 strm >> size;
 int *tmp = new int[size];
 for(int i = 0;i < size; i++)
	 strm >> tmp[i];
 Array ar1(tmp,size);
 ar = ar1;
 return strm;
}