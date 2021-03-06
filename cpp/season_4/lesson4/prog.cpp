/*
Класс дроби с доступными над ним операциями.
	Сравнение дробей
	Сокращение - расширение
	Деление - умножение
*	Сложение - вычитание
	Перевод в десятичную
	Сделать доступным для преобразования в const char

Вопросы:
	fraction fraction::min (fraction &f2)
*/
#include <iostream>
#include "prog.h"
using namespace std;

int main()
{
	int f1_n,f1_d,f2_n,f2_d, aliq;
	cout<<"aliq f1_n,   f1_d,   f2_n,   f2_d"<<'\n';
	cin >>aliq>> f1_n >> f1_d >> f2_n >> f2_d;
	/*fraction f1(f1_n, f1_d), f2(f2_n, f2_d);
	f1.print();
	f2.print();
	f3(f1-f2).print();*/
	fraction_with_int f1(f1_n,f1_d,aliq), f2(f2_n,f2_d);
	//f1.print();
	//f2.print();
	(f1-f2).print();
}

fraction::fraction(int n, int d)
{
	if (d<0) {n*=-1; d*=-1;}
	den = d;
	num = n;
}

void fraction::print()
{
	cout << num << '/' << den << '\n';
}


fraction fraction::operator -(const fraction &f2) const
{
	fraction f3;
	f3.num=num*f2.den - f2.num*den;
	f3.den=den*f2.den;
	f3.nod();
	return f3;
}

fraction_with_int fraction_with_int::operator -(const fraction_with_int &f2) const
{
	fraction_with_int f3( normal()-f2.normal() );
	f3.nod();
	return f3;
}

fraction_with_int fraction_with_int::operator -(const fraction &f2) const
{
	fraction_with_int f3(normal()-f2);
	f3.nod();
	return f3;
}

int fraction::comp (fraction &f2)
{
	if (num*f2.num<0) return (num<0)?-1:1;
	if (den==f2.den) return (num==f2.num)?0:(num>f2.num)?1:-1;
	if (num==f2.num) return (den>f2.den)?-1:1;
	int tmp1, tmp2;
	tmp1=num*f2.den;
	tmp2=f2.num*den;
	return (tmp1==tmp2)?0:(tmp1>tmp2)?1:-1;
}

void fraction::nod ()
{
	int r[3];
	if (num!=0 && (den%num)==0) { den/=num; num=1;}
	r[0]=den; r[1]=num;
	int i=2;
	while (r[(i+2)%3]!=0)
	{
		r[i] = r[(i+1)%3]%r[(i+2)%3];
		i=(i+1)%3;						// лол (3++)%3 = 3;
	}
	num/=r[(i+1)%3];
	den/=r[(i+1)%3];
	if (den<0) {num*=-1; den*=-1;}
}

void fraction_with_int::nod()
{
	fraction::nod();
	aliq+=num/den;
	num%=den;
}

fraction fraction_with_int::normal() const
{
	int n=aliq*den+num;
	fraction f2(n,den);
	return f2;
}

void fraction_with_int::print()
{
	cout << aliq << ' ' <<  num << '/' << den << '\n';
}