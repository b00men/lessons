class fraction
{
	int num;
	int den;

	public:
	//fraction () {num=0; den=1;}
	fraction(int n=0, int d=1);
	void print();
	fraction min(fraction f2);
	fraction operator -(fraction &f2);
	int comp(fraction &f2);
	void nod();
};

