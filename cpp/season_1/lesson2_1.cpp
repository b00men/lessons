#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int a,b,c;
	double a2,b2,c2;
	//Ex.1 Find max(a,b,c)
	cout<<"Please input a,b and c: ";
	cin>>a>>b>>c;
	cout<<"Maximum is ";
	if(a>b&&a>c)cout<<"a="<<a;
	else if(b>c) if(a==b)cout<<"... Oh sorry! No Max"; else cout<<"b="<<b;
	else if(a==c||c==b)cout<<"... Oh sorry! No Max"; else cout<<"c="<<c;
	cout<<'\n';

	//Ex.2 Find of logic func "B or C"
	cout<<"Please input B and C (logic): ";
	cin>>b>>c;
	cout<<"F="<<(b||c);
	cout<<'\n';

	//Ex.3 Day of the week. Base of the case
	cout<<"Please input nomber day of the week: ";
	cin>>a;
	cout<<"Your day is ";
	switch(a)
	{
	case (1): cout<<"monday"; break;
	case (2): cout<<"tuesday"; break;
	case (3): cout<<"wednesday"; break;
	case (4): cout<<"thursday"; break;
	case (5): cout<<"friday"; break;
	case (6): cout<<"satuday"; break;
	case (7): cout<<"sunday"; break;
	default: cout<<"no one day of the week"; break;
	}
	cout<<'\n';
	
	//system("pause");
	return 0;
}
