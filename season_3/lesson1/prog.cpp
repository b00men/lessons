/*
Реализация дека целых чисел.
Из-за не статических инициализаторов членов данных рекомендуется использовать стандарт с++11
	флаг для gcc: -std=c++11 или -std=gnu++11
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct element
{
	int key = 0;			// Информационное поле
	element *prev = NULL;	// Указатель на предыдущий элемент
	element *next = NULL;	// Указатель на следующий элемент
};

struct deque
{
	element *head = NULL;	// Указатель на начало списка
	element *tail = NULL;	// Указатель на конец списка
	int size = 0;
};

void push_back(deque &l, int k);			// Поместить `k` как новый элемент в конец дека
void push_front(deque &l, int k);			// Поместить `k` как новый элемент в начало дека
void push_in(int place, deque &l, int k);	// Поместить `k` как новый элемент в `place` позицию дека (где 0 - 1й элемент)
void dell_back(deque &l);					// Удалить последний элемент дека
void dell_front(deque &l);					// Удалить первый элемент дека
void delete_all_List(deque &l);				// Удалить все элементы дека
void print_List(deque &l);					// Дек в стандартный вывод с описаниями. (не raw_deque_out)
void readvec (deque &l);					// Добавить содержимое файла как новые элементы дека.

int main( )
{
    deque my_list;
    readvec (my_list);
    push_in(3,my_list,9);
    dell_back(my_list);
    dell_front(my_list);
    print_List(my_list);
    delete_all_List(my_list);
    print_List(my_list);
    return 0;
}

void push_back(deque &l, int k)			// Поместить `k` как новый элемент в конец дека
{
    element *tmp = new element;
    if(l.head == NULL) l.head = tmp;	// Если дек пуст, то в голову.
    else l.tail -> next = tmp;			// Иначе в хвост
    tmp -> prev = l.tail;				// Указатель `prev` нового эл. должен смотреть на бывший последний эл.
    tmp -> key = k;						// Устанавливаем ключ
    l.tail = tmp;						// Указатель конца списка на новый эл
    l.size++;							// Увеличение счетчика размера
}

void push_front(deque &l, int k)		// Поместить `k` как новый элемент в начало дека
{
    element *tmp = new element;			
    if(l.tail == NULL) l.tail = tmp;	// Если дек пуст, то в конец.
    else l.head -> prev = tmp;			// Иначе в голову
    tmp -> next = l.head;				// Указатель `next` нового эл. должен смотреть на бывший первый эл.
    tmp -> key = k;						// Устанавливаем ключ
    l.head = tmp;						// Указатель начала списка на новый эл
    l.size++;							// Увеличение счетчика размера
}

void push_in(int place, deque &l, int k)			// Поместить `k` как новый элемент в `place` позицию дека (где 0 - 1й элемент)
{
	element *tmp = new element;
    if((l.head==NULL)||(place<1)||(place>l.size-1))	// Исключения
    {
    	if(place < 1) push_front(l,k);				// Если вставка в начало, то вызываем готовую ф-ю
    	else push_back(l,k);						// Если вставка в конец или дек пуст, то вызываем готовую ф-ю
    }
    else 
    {
        element *tmpslct = l.head;					// Инициализация счетчика от головы
        while (place != 1)							// Ждем конца счетчика
        {
        	place--;
            tmpslct = tmpslct -> next;
        }
        tmp -> prev = tmpslct;						// Указатель `prev` нового эл. должен смотреть на `place-1` эл.
        tmp -> next = tmpslct -> next;				// Указатель `next` нового эл. должен смотреть на бывший `place` эл. (ныне `place+1`)
        tmpslct -> next -> prev = tmp;				// Указатель `prev` `plcae+1` эл. должен смотреть на новый эл.
        tmpslct -> next = tmp;						// Указатель `next` `place-1` эл. должен смотреть на новый эл.
	    tmp -> key = k;								// Устанавливаем ключ
	    l.size++;									// Увеличение счетчика размера
    }
}


void dell_back(deque &l)						// Удалить последний элемент дека
{
    if(l.head == NULL) return;					// Если дек пуст - выход
    element *tmp = l.tail;
    if (tmp -> prev == NULL) l.head = NULL;		// Если эл. последний - заNULLяем голову
    else tmp -> prev -> next = NULL;			// Иначе заNULLяем указатель с предыдущего эл.
    l.tail = tmp -> prev;						// Конец - на предыдущий (если последний - пойдет null)
    delete tmp;									// Удаляем tmp
    l.size--;									// Счетчик размера
}

void dell_front(deque &l)
{
    if(l.tail == NULL) return;					// Если дек пуст - выход
    element *tmp = l.head;
    if (tmp -> next == NULL) l.tail = NULL;		// Если эл. последний - заNULLяем хвост
    else tmp -> next -> prev = NULL;			// Иначе заNULLяем указатель со следующего эл.
    l.head = tmp -> next;						// Голову - на следующий (если последний - пойдет null)
    delete tmp;									// Удаляем tmp
    l.size--;									// Счетчик размера
}

void delete_all_List(deque &l)			// Удалить все элементы дека (взято со слайда)
{
    while (l.head != NULL)
    {
        element *tmp = l.head;			// устанавливаем tmp на голову
        l.head = l.head -> next;		// двигаем голову
        delete tmp;						// удаляем tmp
    }
    l.tail = NULL;
    l.size = 0;
}

void print_List(deque &l)				// Дек в стандартный вывод с описаниями. (не raw_deque_out) (взято со слайда)
{
    element *tmp = l.head;									// устанавливаем tmp на голову
    if(tmp == NULL) {cout << "list is empty\n"; return;}	// список пуст
    cout << "list is:\n";
    cout << "size is: " << l.size << "\n";
    while (tmp != NULL)
    {
        cout << "element is: " << tmp -> key << "\n";		// выводим ключ эл.
        tmp = tmp -> next;									// двигаем tmp от головы к хвосту
    }
}

void readvec (deque &l)										// Добавить содержимое файла как новые элементы дека.
{
    ifstream in( "massin" );
    int tmp;
    while ((!in.eof()) && (in >> tmp)) push_back(l,tmp);	// Записывать слева на право
//	while ((!in.eof()) && (in >> tmp)) push_front(l,tmp);	// Записывать справо на лево
    in.close();
    return;
}