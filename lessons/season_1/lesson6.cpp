#include <string.h>
#include <iostream>
#include <fstream>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
using namespace std;

int groupcmp(char w1[100], char w2[100]) // Сравнение 2х строк. Альтернатива оффициальной функции.
{
	int cmp=0;
	for(int i=0,stop;stop==0;i++)
	{
	cmp=cmp+(w1[i]>w2[i]);
	cmp=cmp-(w1[i]<w2[i]);
	stop=cmp||((w1[i]==w2[i])&&(w1[i]==0));
	}
	return cmp;

}

int grouplen(char mas[]) // Нахождение длинны строки. Альтернатива оффициальной функции.
{
	int i;
	for(i=0;mas[i]!=0;i++);
	return i;
}

int main(int a, char* b[10])
{
	char w1[100],w2[100];
	int priv,off;
	cout<<"Введите первую строку \n";
	cin>>w1;
	cout<<"Введите вторую строку \n";
	cin>>w2;
	cout<<"Сравнение строк :\n";
	priv=groupcmp(w1,w2);
	off=strcmp(w1,w2);
	cout<<priv<<'\n'<<off<<'\n';
	
	cout<<"Длина строки: \n";
	priv=grouplen(w1);
	off=strlen(w1);
	cout<<priv<<'\n'<<off<<'\n';
		
	return 0;
}
