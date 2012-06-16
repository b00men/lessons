#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	// Ex.1 Stupid Ex for while. This is degree of 2? If yes - how mach?
	int n,a,b;
	double d;
	cout<<"Please input n: ";
	cin>>n;
	a=0;
	while((n!=1)&&(n!=0))
	{
	if (n%2==0)			
		{
		n/=2;
		a+=1;
		}
	else
	n=0;
	}
	if (n==1)
	cout<<"yes "<<a<<"\n";
	else
	cout<<"no \n";
	
	// Ex.2 Truth table for "A and B"
	cout<<"\nTable of a^b: \n";
	n=0;
	do
	{
	a=n%10;
	b=n/10;
	cout<<a<<" ^ "<<b<<" = "<<(a&&b)<<'\n';
	if(a==1)
	n+=9;
	else
	n+=1;
	}
	while(n!=20);
	
	// Ex.3 We input many chars and "$", next we summ code of this chars
	char c;
	n=0;
	c=0;
	cout<<'\n';
	while(c!='$')
	{
	cout<<"Input any synbol: ";
	cin>>c;
	n+=c;
	}
	cout<<"Summary is "<<n<<'\n';
	
	//Ex.4 Results of 1! , 2! , 3! ... n!
	cout<<"\nInput n!: ";
	cin>>n;
	a=0;
	b=1;
	do
	{
	a+=1;
	b*=a;
	cout<<a<<"! ="<<b<<'\n';
	}
	while(a!=n);
	
	//Ex.5 in n days, out hours
	cout<<"\nInput n days: ";
	cin>>n;
	d=0;
	do
	{
	d+=1;
	cout<<d<<" days = "<<d*24<<" hours\n";
	}
	while(d!=n);
	
	//system("pause");
	return 0;
}
