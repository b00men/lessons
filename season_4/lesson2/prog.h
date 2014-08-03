#include <iostream>
#include <fstream>
class Array 
{
	int* a; 
	int size_a;

	public:
	~Array() {delete []a;}
	//Array() {a=NULL; size_a=0;}
	Array (int* a1=NULL, int size_a1=0);
	Array (const char* file);
	Array (Array& ar);

	void print();
	void hand();
	void gen(int& type, int& size);	// rand|anti|half
	void rand (int size);
	void anti(int size);
	void half(int size);
	double sort (bool type);		// slow|fast; return time of sort
	void slow_sort();				// Вставкой
	void fast_sort();				// Хоара
	void fast_sort_work (int l, int r, int cent, int*& mass);
	
	operator int() {return size_a;}  
	operator int*() {return a;}

	int& operator [](int i) {return a[i];}
	Array operator =(Array& ar);
	Array operator +(Array &ar);
	Array operator +=(Array& ar);
	Array operator ++();				// Каждый элемент увеличили на 1

	friend std::ostream& operator << (std::ostream& strm, Array &ar);
	friend std::istream& operator >> (std::istream& strm, Array &ar);
};

// Комбайн эксперемнта.
//		MofMS	- Mass of Mass Size
//		type	- [0]rand|[1]anti|[2]half & [0-2]slow|[3-5]fast
//		no		- size of iterator
void math (Array &MofMS, int &type, int &no);
int find (int l, int r, int *&mass);
void swap (int &a, int &b);

	/*int *mass = new int [3];
	mass[0]=1;
	mass[1]=2;
	mass[2]=3;*/

	/*ofstream out;
	ifstream in;
	out.open("hello");
	in.open("massin");
	cout<<massive<<'\n';
	cin>>massive;
	
	out.close();
	in.close();*/