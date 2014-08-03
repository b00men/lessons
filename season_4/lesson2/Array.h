using namespace std;
class Array 
{
 int *a; 
 int size_a;
 public:
 Array() { a = NULL; size_a = 0; }	// конструктор по умолчанию
 Array(int *a1, int size_a1);		// конструктор с аргументами //  создает массив размера size_a1, копиру€ в него элементы массива a1  
 void Print();						// функци€ вывода
 int & a_i(int i);					// возвращает адрес i-го элемента массива
 Array(Array & ar);					// конструктор копировани€
 ~Array(){ delete []a; }			// деструктор
 Array Union(Array &ar);			// объединение массивов

 Array operator +=(Array &ar);		//операторы
 int & operator [](int i);			//
 int   operator ==(Array &ar2);		//
 Array operator ++();				//
 Array operator =(Array &ar);		//
 Array operator +(Array &ar);		//
 
 friend ostream & operator << (ostream & strm, Array &ar); //потоковый вывод
 friend istream & operator >> (istream & strm, Array &ar); //потоковый ввод
 friend void friend_Print(Array &ar);
 operator int();
 operator int*();

 Array (char * filename);			//конструктор по имени файла
 Array from_keyboard(int size);		//ручной ввод
 Array random(int size);			//заполнение случайными числами
 Array anti (int size);				//антиупор€доченный
 Array partly (int size);			//частично упор€доченный
 void bubble();
 void Shell();
};
