/*
	Ex.: Longbool vector
	For non-static data member initializers compile with -std=c++11 or -std=gnu++11

	TODO:
	Поптыка принять бесконечный вектор.
	ДЕЙСТВИТЕЛЬНО длинные вектора (swap).
	Есть ли возможность перегружать функции "на лету" (что выгодне gen\sort или др. метод) ?
	Некоректна перегрузка `+`. `=` должно получать в аргументе Array& а не Array
.*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "prog.h"
#include <string.h>

using namespace std;

int main()
{ 	
	/*unsigned char m[3] = {0xFF, 0x02, 0x01};
	longbool ar1(m,sizeof(m)*8); // создали массив 1, 2, 3
	//int m1[5] = {-7, 5, 0};
	//longbool ar2(m1,5,5); // создали массив -7, 5, 0, 0, 0*/
	//unsigned char m1[3] = {0xF0, 0xF0, 0xF0};
	longbool ar1,ar2;
	cin>>ar1>>ar2;
	cout<<'\n'<< ar1<<'\n'<<ar2 <<'\n';
	cout<< (ar1&ar2) <<'\n';
	//(ar1&ar2).rawprint();
	//ar1.rawprint();
	//ar2.rawprint();
	/*clock_t start=clock();
	cout<<((clock()-start)/CLOCKS_PER_SEC)<<'\n';//*/
	//longbool ar2(m1,sizeof(m1)*8); // создали массив -7, 5, 0, 0, 0
	//ar2.~longbool(); // Явный вызов деструктора - ошибка при повторном очищении в конце программы.
	return 0;
}

longbool::longbool(unsigned char *a1, int size_bool1)
{
	if (a!=NULL) delete []a;
	size_tail=size_bool1%(sizeof(a1[0])*8);
	size_vec=size_bool1/(sizeof(a1[0])*8)+((size_bool1%(sizeof(a1[0])*8))?(1):(0));	
	a = new unsigned char [size_vec];
	for (int i=0; i<size_vec; a[size_vec-i-1]=a1[i], i++);
}

longbool::longbool (longbool& ar)
{
	if (this==&ar) return;
	if (a!=NULL) delete []a;
	size_vec = ar.size_vec;
	size_tail = ar.size_tail;
	a=new unsigned char [size_vec];
	for (int i=0; i<size_vec; a[i]=ar.a[i], i++);
	return;
}

void longbool::false_vec(int size_bool1)
{
	size_tail=size_bool1%(sizeof(this->a[0])*8);
	size_vec=size_bool1/(sizeof(this->a[0])*8)+((bool)size_tail);
	a = new unsigned char [size_vec];
	for (int i=0; i<size_vec; a[size_vec-i-1]=0, i++);
}

void longbool::true_vec(int size_bool1)
{
	size_tail=size_bool1%(sizeof(this->a[0])*8);
	size_vec=size_bool1/(sizeof(this->a[0])*8)+((bool)size_tail);
	a = new unsigned char [size_vec];
	for (int i=0; i<size_vec; a[size_vec-i-1]=0xFF, i++);
	if (size_tail) for(int i=sizeof(this->a[0])*8; i>size_tail-1; a[0]&=~(1<<i), i--);
}

void longbool::rand(int size_bool1)
{
	srand ((int)time(NULL));
	size_tail=size_bool1%(sizeof(this->a[0])*8);
	size_vec=size_bool1/(sizeof(this->a[0])*8)+((bool)size_tail);
	a = new unsigned char [size_vec];
	for (int i=0; i<size_vec; a[size_vec-i-1]=std::rand()%255, srand ((int)(time(NULL)+i)), i++);
	if (size_tail) for(int i=sizeof(this->a[0])*8; i>size_tail-1; a[0]&=~(1<<i), i--);
}

void longbool::rawprint()
{
	cout<<"Print RAWlongbool:\n";
	int i=0;
	for (; i < size_vec; i++)
	{
		for(int j=sizeof(a[i])*8-1;j>-1;j--) cout<<((a[i]>>j)&1);
		cout<<'\n';
	}
}

/* FREEZE
operator unsigned int*()
{
	int ilb_size=size_vec/4+(bool)(size_vec%4);
	unsigned int* int_lb;
	int_lb = new unsigned int [ilb_size];
	for (int i=0; i<ilb_size; int_lb[i]=0, i++);
	for (int i=size_vec%4; i<size_vec%4; i++) int_lb[0]|=(a[i]<<8*(i%4));
	for (int i=(bool)(size_vec%4)*4; i<size_vec; i+=4) int_lb[i/4]=a[i]|(a[i+1]<<8)|(a[i+2]<<16)|(a[i+3]<<24);
	return int_lb;
}///*/
int longbool::popcount()
{
	int sum=0;
	if(sizeof(a[0])<=sizeof(sum))
	{
		for(int i=0;i<size_vec;i++)
		{
			sum+=__builtin_popcount((int)a[i]);
		}
		return sum;
	}
	else return -1;
}//*/

longbool longbool::operator =(longbool &ar)
{
	if (this==&ar) return *this;
	if (a!=NULL) delete []a;
	size_vec = ar.size_vec;
	size_tail = ar.size_tail;
	a=new unsigned char [size_vec];
	for (int i=0; i<size_vec; a[i]=ar.a[i], i++);
	return *this;
}

longbool longbool::operator |(longbool ar)
{
	if (this->length()>ar.length()) {
		ar.size_vec=this->size_vec;
		ar.size_tail=this->size_tail;
	}
	for (int i=0; i<=ar.size_vec; ar.a[ar.size_vec-i]|=this->a[this->size_vec-i], i++);
	return ar;
}

longbool longbool::operator &(longbool ar)
{
	longbool res;
	if (this->length()<ar.length())	res.false_vec(this->length());
	else res.false_vec(ar.length());

		/*ar.size_vec=this->size_vec;
		ar.size_tail=this->size_tail;*/
	for (int i=0; i<=ar.size_vec; res.a[res.size_vec-i]=ar.a[ar.size_vec-i]&this->a[this->size_vec-i], i++);
	return res;
}

istream& operator >> (istream& strm, longbool &ar)
{
	deque my_list; char tmp; int i=0, num_of_deque=1, sizeofa=sizeof(ar.a[0])*8;
	ifstream tmpin;
	ofstream outtmp;
	while(((tmp=strm.get())!=EOF)&&(tmp!=32)&&(tmp!=10)) push_back(my_list,(tmp-48)); 						// stdin -> deque
	ar.size_tail=my_list.size%sizeofa;
	ar.size_vec=(my_list.size+((num_of_deque-1)*sizeofa*10))/sizeofa+(bool)ar.size_tail;
	if (ar.a!=NULL) delete []ar.a;
	ar.a = new unsigned char [ar.size_vec];
	for (i=0; i<ar.size_vec; ar.a[i]=0, i++);
	if(ar.size_tail) for(i=0;i<ar.size_tail; i++) if(dell_front(my_list)) ar.a[0]|=(1<<ar.size_tail-i-1);	// deque -> tail (if need)
	i=0;
	while(my_list.size!=0)																					// deque -> longbool
	{
		if(dell_front(my_list)) ar.a[(i/sizeofa)+(bool)ar.size_tail]|=(1<<sizeofa-i%sizeofa-1);
		i++;
	}
 	return strm;
}

ostream& operator << (ostream& strm, const longbool &ar)
{	

	int i=0; bool tmp, trigger=0;
	if(ar.size_tail)
	{
		for(int j=ar.size_tail-1;j>-1;j--)
		{
			tmp=((ar.a[0]>>j)&1);
			if (!trigger&&tmp)trigger=1;
			if (trigger) strm<<tmp;
		}
	i++;
	}
	for (; i < ar.size_vec; i++)
	{
		for(int j=sizeof(ar.a[i])*8-1;j>-1;j--)
		{
			tmp=((ar.a[i]>>j)&1);
			if (!trigger&&tmp)trigger=1;
			if (trigger) strm<<tmp;
		}
	}
	return strm;
}

void push_back(deque &l, bool k)
{
    element *tmp = new element;
    if(l.head == NULL) l.head = tmp;
    else l.tail -> next = tmp;
    tmp -> key = k;
    l.tail = tmp;
    l.size++;
}

bool dell_front(deque &l)
{
	bool out=l.head->key;
    if(l.tail == NULL) return 0;
    element *tmp = l.head;
    if (tmp -> next == NULL) l.tail = NULL;	
    l.head = tmp -> next;
    delete tmp;
    l.size--;
    return out;
}

void print_List(deque &l)
{
    element *tmp = l.head;
    if(tmp == NULL) {cout << "list is empty\n"; return;}
    cout << "list is:\n";
    cout << "size is: " << l.size << "\n";
    while (tmp != NULL)
    {
        cout << "element is: " << tmp -> key << "\n";
        tmp = tmp -> next;
    }
}

/*longbool::longbool(const char* file) // w/o overload stream
{
	ifstream in;
	in.open(file);
	int i=0, sizeofa=sizeof(a[0])*8; char tmp;
	while(in.get()!=EOF) i++;
	in.close();
	in.open(file);
	size_tail=i%sizeofa;
	size_vec=i/sizeofa+((bool)size_tail);
	a = new unsigned char [size_vec];
	for (i=0; i<size_vec; a[i]=0, i++);
	i=0;
	if(size_tail) for(;i<size_tail; i++) if((tmp=in.get())-48) a[0]=a[0]|(1<<size_tail-i-1);
	i=0;
	while((tmp=in.get())!=EOF)
	{
		if(tmp-48) a[(i/sizeofa)+(bool)size_tail]=a[(i/sizeofa)+(bool)size_tail]|(1<<sizeofa-i%sizeofa-1);
		i++;
	}
	in.close();
}*/

/*int pop(unsigned A[], int n)
{
	int i,j,lim;
	unsigned s,s8, x;
	s=0;
	for (i=0; i<n; i=i+31)
	{
		lim=std::min(n,i+31);
		s8=0;
		for (int j=i; j<lim; j++)
		{
			x=a[j];
			x=x-((x>>1)&0x55555555);
			x=(x&0x33333333)+((x>>2)&0x33333333);
			x=(x+(x>>4))&0x0F0F0F0F;
			s8=s8+x;
		}
		x=(s8&0x00FF00FF)+((s8>>8)&0x00FF00FF);
		x=(x&0x0000FFFF)+(x>>16);
		s=s+x;
	}
	return s;
}*/