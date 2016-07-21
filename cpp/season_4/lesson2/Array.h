using namespace std;
class Array 
{
 int *a; 
 int size_a;
 public:
 Array() { a = NULL; size_a = 0; }	// ����������� �� ���������
 Array(int *a1, int size_a1);		// ����������� � ����������� //  ������� ������ ������� size_a1, ������� � ���� �������� ������� a1  
 void Print();						// ������� ������
 int & a_i(int i);					// ���������� ����� i-�� �������� �������
 Array(Array & ar);					// ����������� �����������
 ~Array(){ delete []a; }			// ����������
 Array Union(Array &ar);			// ����������� ��������

 Array operator +=(Array &ar);		//���������
 int & operator [](int i);			//
 int   operator ==(Array &ar2);		//
 Array operator ++();				//
 Array operator =(Array &ar);		//
 Array operator +(Array &ar);		//
 
 friend ostream & operator << (ostream & strm, Array &ar); //��������� �����
 friend istream & operator >> (istream & strm, Array &ar); //��������� ����
 friend void friend_Print(Array &ar);
 operator int();
 operator int*();

 Array (char * filename);			//����������� �� ����� �����
 Array from_keyboard(int size);		//������ ����
 Array random(int size);			//���������� ���������� �������
 Array anti (int size);				//�����������������
 Array partly (int size);			//�������� �������������
 void bubble();
 void Shell();
};
