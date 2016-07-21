#include <iostream>
#include <cmath>
using namespace std;
int main()	// ax^4+bx^2+c find roots
{
	double a,b,c,d,x1,x2,dstat;
	cout<<"Please input a,b and c: ";
	cin>>a>>b>>c;
	d=b*b-4*a*c;
	if (a==0)
	{
		x1=(-c/b);
		if (x1<0)
		cout<<"Sorry, x<0, we can't work with imaginary numbers, we lose 2x roots.\n";
		else
		cout<<"We find next roots:\n"<<sqrt(x1)<<" and "<<-sqrt(x1)<<"\n";
	}
	else
	{
			if (d<0)
			cout<<"Sorry, D<0, we can't work with imaginary numbers, we lose all roots.\n";
			else
			{
				x1=(b-sqrt(d))/(2*a);
				x2=(b+sqrt(d))/(2*a);		
				cout<<"We find next roots:\n";
				if (x1<0)
				cout<<"Sorry, x1<0, we can't work with imaginary numbers, we lose 2x roots.\n";
				else
				cout<<sqrt(x1)<<" and "<<-sqrt(x1)<<"\n";
				if (x2<0)
				cout<<"Sorry, x2<0, we can't work with imaginary numbers, we lose 2x roots.\n";
				else
				cout<<sqrt(x2)<<" and "<<-sqrt(x2)<<"\n";
			}
	}
	//system("pause");
	return 0;
}
