/*
	Ex.: Longbool vector
	For non-static data member initializers compile with -std=c++11 or -std=gnu++11

	TODO:
	Поптыка принять бесконечный вектор.
	ДЕЙСТВИТЕЛЬНО длинные вектора (swap).
	Есть ли возможность перегружать функции "на лету" (что выгодне gen\sort или др. метод) ?
	Некоректна перегрузка `+`. `=` должно получать в аргументе Array& а не Array
.*/
class longbool 						// Sic! Non-static data member initializers
{
	unsigned char* a=NULL; 
	int size_tail=0, size_vec=0;

	public:
	~longbool() {delete []a;}
	longbool()	{}					// {a=NULL; size_tail=0; size_vec=0;}
	longbool (longbool& ar);		// I could not merge this constructor with operator= ):
	longbool (const char* file) {std::ifstream in; in.open(file); in>>*this; in.close();}
	longbool (unsigned char* a1, int size_bool1);
	
	int length() {return this->size_vec*sizeof(a[0])*8+this->size_tail;}	// in bits
	int weight() {int j=0; for(int i=0;i!=length()+1;j+=get(i),i++); return j;}
	int popcount();					// POPCNT from SSE4.2
	void print() {std::cout<<*this<<'\n';}
	void rawprint();				// 4 debug (print longbool 'as is' in memory)
	void hand() {std::cin>>*this; std::cout<<'\n';}
	void rand (int size);
	void false_vec(int size_bool1);
	void true_vec(int size_bool1);
	void invert() {for (int i=0; i<size_vec; this->a[i]=~this->a[i], i++);}
	// buffoon!
	bool get (int k) { return ((this->a[this->size_vec-(k/(sizeof(this->a[0])*8))-1]>>k%(sizeof(this->a[0])*8))&1); }
	void set (int k) { this->a[this->size_vec-(k/(sizeof(this->a[0])*8))-1]|=(1<<k%(sizeof(this->a[0])*8)); }
	// is better
	void unset (int k) {
		unsigned char *b=this->a;
		int sv=this->size_vec, sp=sizeof(b[0])*8;
		b[sv-(k/sp)-1]&=(~(1<<k%sp));
	}

	operator int() {return size_vec;}
	operator unsigned char*() {return a;}	// Зачем я это сделал
	bool operator [](int k) {return get(k);}
	longbool operator |(longbool ar);
	longbool operator &(longbool ar);
	longbool operator =(longbool&)	;
	friend std::ostream& operator << (std::ostream& strm, const longbool &ar);
	friend std::istream& operator >> (std::istream& strm, longbool &ar);
									// Представление: побитовый ввод, где только символ с кодом 48 задает биту значение 'ложь',
									// иначе 'истина', положение символа соответствует положению задаваемого бита. 
									// EOF, пробел или разрыв строки сведетельствуют об окончании вектора.
									// Why with deque? Потому что с ним можно вручную регулировать размер буфера и подкачки.
									// Хотя вообще-то есть ifstream::swap,rdbuf,filebuf ... whatever  ~_~"
};

struct element						// Sic! Non-static data member initializers
{
	bool key = 0;
	element *next = NULL;
};

struct deque						// Really is not deque (no *prev element) but nobody cares.
{									// Sic! Non-static data member initializers
	element *head = NULL;
	element *tail = NULL;
	int size = 0;
};

void push_back(deque &l, bool k);
bool dell_front(deque &l);
void print_List(deque &l);			// 4 debug (print deque in stdout)
