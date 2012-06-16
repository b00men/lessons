#include <iostream>
#include <cmath>
using namespace std;
int main()	// Logarithm biger on base small
{
	double a,b;
	cout<<"Please input two numbers: ";
	cin>>a>>b;
	if ((a==0)||(b==0)||((a/b)<0))
	cout<<"Incorect data. You can't use zero or nombers with different sign.";
	else
		if (a>b)
			if (a==1)
			cout<<'0';
			else
				if (b==1)
				cout<<"Sorry, 1 in any degree always 1";
				else
				cout<<"Log("<<a<<" on base "<<b<<")="<<(log(a)/log(b));
		else
			if (b==1)
			cout<<'0';
			else
				if (a==1)
				cout<<"Sorry, 1 in any degree always 1";
				else
				cout<<"Log("<<b<<" on base "<<a<<")="<<(log(b)/log(a));
	cout<<"\n";
	//system("pause");
	return 0;
}
