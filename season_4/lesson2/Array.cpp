#include <time.h>
#include <iostream>
#include <fstream>
#include "Array.h"
#include <string.h>
using namespace std;
Array::Array(int *a1, int size_a1)
{
	size_a=size_a1;
	a = new int [size_a];
	for (int i=0; i < size_a; a[i]=a1[i], i++);
}
void Array::Print()
{
	for (int i = 0; i < size_a; cout << a[i] << ' ', i++);
	cout<<endl;
}
void friend_Print(Array &ar) //это определение //функции
 {
 cout << "array is: ";
 for(int i = 0;i < ar.size_a;i++)
	 cout << ar.a[i] << " ";
 cout<<"\n";
 }

int & Array:: a_i(int i)
{
	return a[i];
}
Array::Array(Array & ar)		// строим копию ar //не спасает если инициализация идет до копирования //спасает только при Array ar1 = ar2;
{
 size_a = ar.size_a;			// скопировали размерность
 a = new int [size_a];			// взяли память
 for (int i = 0; i < size_a; i++)
   a[i] = ar.a[i];				// копируем элементы
}
Array Array:: Union(Array &ar)
{				// на вход пришел объект по указателю this
 int *tmp = new int[size_a];
 int i;
 for(i = 0; i < size_a; tmp[i] = a[i], i++);
 delete []a;
 a = new int [size_a + ar.size_a];
 for(i = 0; i < size_a; a[i] = tmp[i], i++);
 for(i = size_a; i < size_a + ar.size_a; a[i] = ar.a[i - size_a], i++);
 size_a += ar.size_a;
 return *this;
}
Array Array:: operator +=(Array &ar)
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
int & Array:: operator [](int i)
{
	return a[i];
}

int Array::   operator ==(Array &ar2)
{
 if(size_a != ar2.size_a) return 0;
 int i;
 for(i = 0; (i < size_a) && (a[i] == ar2.a[i]); i++);
 if(i == size_a) return 1;
 return 0;
}

Array Array:: operator =(Array &ar)//при работе без кк не спасает никак, но при Array ar1 = ar2 не появляется грязь в ar1
{
 if(this != &ar) //не нужно копировать объект сам в себя 
 {
  size_a = ar.size_a;
  a = new int [size_a];
  for (int i = 0; i < size_a; i++)
    a[i] = ar.a[i];
 }
 return *this;
}
Array Array:: operator ++()
{
	for(int i = 0; i < size_a; a[i]++, i++);
	return *this;
}
Array Array ::operator +(Array &ar)
{
 int *tmp = new int[size_a];
 int i;
 for(i = 0; i < size_a; tmp[i] = a[i], i++);
 delete []a;
 a = new int [size_a + ar.size_a];
 for(i = 0; i < size_a; a[i] = tmp[i], i++);
 for(i = size_a; i < size_a + ar.size_a; a[i] = ar.a[i - size_a], i++);
 size_a += ar.size_a;
 return *this;

}
ostream & operator << (ostream & strm, Array &ar)
{	
	cout<<"Array is: ";
	for (int i = 0; i < ar.size_a; cout<<ar.a[i]<<' ', i++);
	cout<<endl;
	return strm;
}

istream & operator >> (istream & strm, Array &ar)
{
	cout << "enter array size ";
 int size;
 cin >> size;
 int *tmp = new int[size];
 cout << "\nenter array itemes ";
 for(int i = 0;i < size; i++)
	 cin >> tmp[i];
 Array ar1(tmp,size); // работает конструктор с аргументами
 ar = ar1;
 return strm;
}

Array:: operator int()
{return size_a;}
Array:: operator int*()
{return a;}
Array:: Array(char *filename)
{
	ifstream fin (filename);
	fin>>size_a;
	a = new int [size_a];
	for(int i=0; i < size_a; fin>>a[i], i++);
	fin.close();
}
Array Array:: from_keyboard(int size)
{
	size_a=size;
	a = new int[size_a];
	for(int i = 0; i < size_a; cout<<"a["<<i<<"]=", cin>>a[i], i++);
	return *this;
}
Array Array:: random(int size)
{
	srand ((int)time (NULL));
	size_a=size;
	a = new int[size_a];
	for(int i = 0; i < size_a; a[i]=rand()%100000, i++);
	return *this;
}

Array Array:: anti (int size)		
{
	size_a=size;
	a = new int[size_a];
	for (int i = 0; i < size_a ; a[i] = size_a - i, i++);
	return *this;
}
Array Array:: partly (int size)
{
	srand ((int)time (NULL));
	size_a=size;
	a = new int[size_a];
	for (int i = 0; i < (size_a/2); a[i] = i, i++);
	for(int i=size_a / 2; i < size_a; a[i]=rand()%100000, i++);
	return *this;
}
void Array:: bubble()
	{bool fl=0;
		for(int j=0;j<size_a;j++)
		{	
			for (int i=0;i<size_a - 1;i++)
			{
				if (a[i]>a[i+1])
					{
						swap(a[i],a[i+1]);
						fl=1;
					}
			}
			if (fl==0) break;
		}

	}
void Array:: Shell()
	{
		int step = size_a / 2;
		while (step > 0)
			{
				 for (int i = 0; i < (size_a - step); i++)
					{
						int j = i;
						while (j >= 0 && a[j] > a[j + step])
							{
								swap(a[j],a[j+step]);
								j--;
							}
					}
				step = step / 2;
			}    

	}

int experiment (Array &ar, int size,  int num, char *sort)
 {
	clock_t t;
	int *times=new int [num];

	if (!(strcmp(sort,"fast")))
	{
		for(int i = 0; i < num; i++)
		{	
			srand((int)time(NULL));
			ar.random(size);
			t=clock();
			ar.Shell();
			t=clock()-t;
			times[i]=t;
		}
	}

	else
		if (!(strcmp(sort,"slow")))
		{
			for(int i = 0; i < num; i++)
			{
				srand((int)time(NULL));
				ar.random(size);
				t=clock();
				ar.bubble();
				t=clock()-t;
				times[i]=t;
			}
		}
		
	int av_time=0;
		for(int i = 0; i < num; i++)
		{
			av_time+=times[i];
		}
	return av_time/=num;
}
void provide_experiment(int iter)
{
 Array ar;

int size = 400000;
int average_time  = experiment(ar,size,iter,"slow");
 cout<<"average time in sec for " << size << " elments massive is:"<<(float)average_time/CLOCKS_PER_SEC<<endl;
 size = 500000;
 average_time  = experiment(ar,size,iter,"slow");
 cout<<"average time in sec for " << size << " elments massive is:"<<(float)average_time/CLOCKS_PER_SEC<<endl<<endl;

 
 size = 400000;
 average_time  = experiment(ar,size,iter,"fast");
 cout<<"average time in sec for " << size << " elments massive is:"<<(float)average_time/CLOCKS_PER_SEC<<endl;
 size = 500000;
 average_time  = experiment(ar,size,iter,"fast");
 cout<<"average time in sec for " << size << " elments massive is:"<<(float)average_time/CLOCKS_PER_SEC<<endl;
}

void main()
{
 Array ar("input.txt");

 cout<<ar<<endl;
 

 system("pause");

}