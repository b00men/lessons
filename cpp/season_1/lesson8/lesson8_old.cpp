#include <string.h>
#include <iostream>
#include <fstream>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
using namespace std;
int outmat(int a[], int n, int m);
int inmat(int a[],int n,int m);
int edmat(int a[],int n,int m);
int proverka(int vecn[],int n, int N, unsigned int m, int k[], int size); 
int outvec(unsigned char a, int i);
int invec(unsigned char& a, int i);
int perebor(int vecn[],int n1, int n, int k[], int size);
int summat(int vecn[],int k[], int n, int size);

int main()
{
/*	int k[100],n,m,vecn[100];
	cout<<"Введите размеры матрицы: ";
	cin>>n>>m;
	cout<<"Введите матрицу:\n";
	for(int i=0;i<n;i++,cout<<'*');cout<<'\n'; // Чудесная линеечка
	inmat(k,n,m);
	//cout<<"Вывод:\n";
	//outmat(k,n,m);
	for(int i=1;i<m+1;i++) perebor(vecn,i,m,k,n);
	return 0; */


	int k[100],n,m;
	cout<<"Введите размеры матрицы: ";
	cin>>n>>m;
	cout<<"Введите матрицу:\n";
	for(int i=0;i<n;i++,cout<<'*');cout<<'\n';
	inmat(k,n,m);
	edmat(k,n,m);
	cout<<"Вывод:\n";
	outmat(k,n,m);
	return 0;	

}

int summat(int vecn[],int k[], int n, int size) // Суммирует полученные строки по номерам.
// Где vecn - вектор с номерами, k - бинарная матрица, n - кол-во ед.(кол-во номеров)
{
	int x=0;
	for(int i=0;i<n;i++)
	{
	x=x|k[vecn[i]];
	}
	//outvec(x,size);
	return x;
}

int outmat(int a[], int n, int m) // Вывод бинарной матрицы
{
	for(int j=0;j<m;j++)
	{
		for(int i=n-1;i>-1;i--)
		{
			cout<<((a[j]>>i)&1);
		}
		cout<<'\n';
	}
	return 0;
}

int inmat(int a[],int n,int m) // Ввод бинарной матрицы
{
	char c;
	
	for(int j=-1;j<m;j++)
	{
	a[j]=0;
		for(int i=n;i>-1;i--)
		{
			c=cin.get();
			if ((c=='0')||(c=='1')) 
			{
				if(c=='0') a[j]=a[j]&(~(1<<i));
				else a[j]=a[j]|(1<<i);
			}
			else
			{
			a[j]=a[j]>>(i+1);
			i=-1;
			}
		}
	}
	return 0;
}

int edmat(int a[],int n,int m) // На полученную матрицу примеяет функцию
// для создания еденичной (существующие еденицы остаются)
{
	for(int j=0;j<m;j++)
	{
		for(int i=0;i<n+1;i++)
		{
			a[j]=((i-1)==j)?(a[j]|(1<<(n-i))):(a[j]);
		}
	}
	return a[100];
}

int proverka(int vecn[], int n, int N, unsigned int m, int k[], int size)
{
	// Перевод бинарного вектора в числовой с номерами едениц.
	int b, a=0;
	for(int i=N-1;a!=n;i--)
	{
		if ((m>>i)&1) 
		{
		vecn[a]=(N-1-i);
		a++;
		}
	}
	// Сложение
	a=summat(vecn,k,n,size);
	b=0;
	for (int i=size-1;i>-1;i--){b=b|(1<<i);} // Шаблон покрытия
	// Условие успеха
	if (a==b)
	{
		/*cout<<"Успех при "<<n<<"х строк. Это строки: ";
		for(int i=0;i<n;i++)
			{		
			cout<<vecn[i]<<' ';
			}
		cout<<'\n'; */
		return 1;
	}
	//outvec(a,size);
	//outvec(b,size);
	return 0;
}

int outvec(unsigned char a, int i) // Вывод бинарного вектора
{
	for(i=i-1;i>-1;i--)
	{
		cout<<((a>>i)&1);
	}
	cout<<'\n';
	return 0;
}

int invec(unsigned char& a, int i) // Ввод бинарного вектора
{
	char c;
	for(i=i-1;i>-1;i--)
	{
		c=cin.get();
		if ((c=='0')||(c=='1')) 
		{
			if(c=='0') a=a&(~(1<<i));
			else a=a|(1<<i);
		}
		else
		{
		a=a>>(i+1);
		i=-1;
		}
	}
	return 0;
}

int perebor(int vecn[],int n1, int n, int k[], int size) // Перебрать все варианты с данным кол-вом 1-чек
// Где n1 - текущее кол-во 1-ек (Попытка на такое кол-во строк в покрытии)
// n - Общее кол-во возможных элементов (Общее кол-во строк)
{
	int sum,a,stop,n2,p;
	unsigned int z,m;
	z=0;
	sum=1;
	m=0;
	n2=n1;
	// Защита от дурака.
	if ((n1>n)||(n1<0)) {cout<<"n1 не входит в рамки, оно равно "<<n1; return 0;}
	// Генерируем вектор с 1 ками в начале. С него мы начинаем движение.
	for (int i=n-1;n1>0;n1--,i--){m=m|(1<<i);}
	n1=n2;
	// Генерируем вектор с 1 ками в конце. Он прерывает основной цикл.
	for (int i=0;n1>0;n1--,i++){z=z|(1<<i);}
	n1=n2;
	// Проверка для начального вектора
	if (proverka(vecn,n1,n,m,k,size))
	{
		cout<<"Успех при "<<n1<<"х строк. Это строки: ";
		for(int i=0;i<n1;i++)
			{		
			cout<<vecn[i]<<' ';
			}
		cout<<'\n';
	}
	//outvec(m);
	// Основной цикл. Повторяет цикл перемещения, запускает проверку.
	for(int j=0; m!=z; j++, sum++)
	{
		// Цикл перемещения еденичек по заданым условиям.
		// Что-то типа:
		// 11100
		// 11010
		// 11001
		// 10110
		// 10101
		// 10011
		// 01110
		// 01101
		// 01011 ... и т.д.
		p=0; a=1; stop=0;
		for(int i=0;((stop==0)&&(i<n));)
		{
			if((m>>i)&1) // Текущий эл.==1?
			{	
				if (a!=1) // До него были нули?
				{
				m=m|(1<<i-1);	// Cдвигаем 1-ку вправо
				m=m&(~(1<<i));
				for(;p!=0;i--,m=m|(1<<i-1),p--); // Если стирали 1-ки, возвращаем.
				stop=1; // Передых, для выдачи вектора.
				}
				else {p++;m=m&(~(1<<i));i++;} // Ставим 0, запоминаем это.
			}
			else {a=0;i++;} // Запомнили, что посетили нуль.
		}
		// Проверка для текущего вектора.
		if (proverka(vecn,n1,n,m,k,size))
		{
			cout<<"Успех при "<<n1<<"х строк. Это строки: ";
			for(int i=0;i<n1;i++)
				{		
				cout<<vecn[i]<<' ';
				}
			cout<<'\n';
		}
		//outvec(m);
	}
	
	//cout<<"Всего вариантов: "<<sum<<'\n';
	return 0;
}
