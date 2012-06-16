#include <string.h>
#include <iostream>
#include <fstream>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
using namespace std;

int outvec(unsigned short a) // Вывод бинарного вектора
{
	for(int i=15;i>-1;i--)
	{
		cout<<((a>>i)&1);
	}
	cout<<'\n';
	return 0;
}

unsigned char str2vec(char str[100]) // НИПАИГРАААТЬ! Перевод строки в вектор с защитой от дурака по шаблону [heap][vector][heap]
{	
	char c;
	unsigned char vec;
	for(int i=100, a=1, b=7;i>-1;i--)
	{
		c=str[i];
		if ((a==1)&&((c=='0')||(c=='1'))) a=0;
		if ((c==0)||((a==0)&&((c=='0')||(c=='1'))))
		{
			if(c=='0') vec=vec&(~(1<<b));
			if(c=='1') vec=vec|(1<<b);
		}
		else
		{
		vec=vec>>(b+1);
		b=-1;
		}
		b--;
	}
	return vec;
}

int invec(unsigned short& a) // Ввод бинарного вектора
{
	char c;
	for(int i=15;i>-1;i--)
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

int true2k(unsigned short& a,int k) // 1 в k-ую позицию
{
	a=a|(1<<k);
	return 0;
}

int false2k(unsigned short& a,int k) // 1 в k-ую позицию
{
	a=a&(~(1<<k));
	return 0;
}

int mask(unsigned short& a,int k) // Создание прямой маски с 1 в k-й позиции
{
	a=1;
	a=a<<k;
	return 0;
}

int invmask(unsigned short& a,int k)  // Создание обратной маски с 0 в k-й позиции
{
	a=1;
	a=a<<k;
	a=~a;
	return 0;
}

int main()
{
	unsigned short a,b;
	int k;
	char str[100];
	cin>>str;
	a=str2vec(str);
		cout<<"Ваш вектор: ";
	outvec(a);
	
	/*
	cout<<"Ввести число: ";
	cin>>k;
	a=k;
	cin.get(); // ?
	cout<<"Ваш вектор: ";
	outvec(a);
	mask(b,k);
	cout<<"Ваша маска: ";
	outvec(b);
	invmask(b,k);
	cout<<"Ваша инвертированная маска: ";
	outvec(b);
	cout<<"Ввести булев вектор: ";
	invec(a);
	false2k(a,k);
	cout<<"Ваш вектор: ";
	outvec(a);
	true2k(a,k);
	cout<<"Ваш вектор: ";
	outvec(a);
	
*/


/*	cout<<"Ввести булев вектор: ";
	invec(a);
	cout<<"Ваш вектор: ";
	outvec(a);
	cout<<"Ввести позицию, в которую поместить 1: ";
	cin>>k;
	true2k(a,k);
	cout<<"Ваш вектор: ";
	outvec(a);
	cout<<"Ввести позицию, в которую поместить 0: ";
	cin>>k;
	false2k(a,k);
	cout<<"Ваш вектор: ";
	outvec(a);
	cout<<"Ввести позицию для задания маски: ";
	cin>>k;
	mask(b,k);
	cout<<"Ваша маска: ";
	outvec(b);
	cout<<"Ввести позицию для задания инвертированной маски: ";
	cin>>k;
	invmask(b,k);
	cout<<"Ваша маска: ";
	outvec(b);
*/
	return 0;
}
