class fraction
{
protected:
	int num;
	int den;

public:
	//fraction () {num=0; den=1;}
	fraction(int n=0, int d=1);
	void copy(fraction f) {num=f.num; den=f.den;}
	void print();
	fraction operator -(const fraction &f2) const;
	int comp(fraction &f2);
	void nod();
};

class fraction_with_int: public fraction 
{
	int aliq;
public:
	fraction_with_int() {aliq=num;}
	fraction_with_int(int a): fraction(), aliq(a) {}
	fraction_with_int(int n, int d): fraction(n, d) {aliq=num/den; num%=den;}
	fraction_with_int(int n, int d, int a): fraction(n, d), aliq(a) {}
	fraction_with_int(fraction f): fraction(f) {aliq=num/den; num%=den;}
	fraction_with_int(fraction_with_int &f2) {num = f2.num; den = f2.den; aliq = f2.aliq;}
	void nod();
	void print();
	fraction normal() const;
	fraction_with_int operator -(const fraction_with_int&) const;
	fraction_with_int operator -(const fraction&) const;
};

