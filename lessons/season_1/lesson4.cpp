#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	// Ex.1 расчет формулы n!/(n-k)!
	int n,k,i;
	cout<<"Please input n and k: ";
	cin>>n>>k;
	for (i=n-k+1,k=1;i<n+1;k=k*i,i++);
	cout<<"n!/(n-k)! = "<<k<<"\n\n";
	
	// Ex.2 Таблица умножения
	for(i=1;i<10;i++)
	{
	for(k=1;k<10;k++)
		{
		if (i*k<10) cout<<(i*k)<<"  "; // Запантентованная Система Форматированного Вывода Числел (0-99)
		else cout<<(i*k)<<" ";
		}
	cout<<'\n';
	}
	cout<<'\n';
	
	// Ex.3 Ввод массива. Определение кол-ва чет/нечет
	int size,massive[100];
	cout<<"Please input size of massive and all elements: ";
	cin>>size;
	for (i=0;i<size;cin>>massive[i],i++);
	for (i=0,n=0,k=0;i<size;i++)
	{
	if (massive[i]%2==0) k++;
	else n++;
	}
	cout<<"In massive "<<k<<" even numbers and "<<n<<" odd numbers. \n\n";
	
	//Ex.4 Ввод массива. Определение Max
	cout<<"Please input size of massive and all elements: ";
	cin>>size;
	for (i=0;i<size;cin>>massive[i],i++);
	for (i=0,n=massive[0];i<size;(massive[i]>n)?(n=massive[i]):(n=n),i++);
	cout<<"Maximum of massive is "<<n<<"\n\n";
	
	//Ex.5 Ввод массива. Цикличное смещение элементов на 1 влево
	cout<<"Please input size of massive and all elements: ";
	cin>>size;
	for (i=0;i<size;cin>>massive[i],i++);
	massive[size]=massive[0];
	for (i=0,n=1;i<size;massive[i]=massive[i+1],i++);
	for (i=0;i<size;cout<<massive[i]<<' ',i++);
	
	//system("pause");
	return 0;
}
