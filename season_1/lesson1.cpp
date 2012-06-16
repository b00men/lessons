#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n;
	float Pi,d,s,a,b;
	Pi=3.14159;
	
	// helloworld
	cout<<"I like C++!"<<'\n';
	
	// Base of cout & cin
	cout<<"Write number of your room: ";
	cin>>n;
	cout<<'\n'<<"The number of my apartament is "<<n<<'\n';
	
	// Find S of circuite by D
	cout<<"Write D of circule: ";
	cin>>d;
	d=d/2;
	s=Pi*d*d;
	cout<<'\n'<<"S of circuite is "<<s<<'\n';
	
	// Find S of "triugolnig" ~_~
	cout<<"Write katets: ";
	cin>>a>>b;
	d=sqrt(a*a+b*b)+a+b;
	s=a*b/2;
	cout<<'\n'<<"S of \"triugolnig\" is "<<s<<". P of triugolnig is "<<d<<'\n';
	
	//system("pause");
	return 0;
}
