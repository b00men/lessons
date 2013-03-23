// 2x способа реализации частотного словаря:
// 1й - За единственный проход по тексту состовлять сразу готовый список.
//      Значит на каждое слово из текста проход по текущемму списку и либо
//      запись нового слова в нужном месте либо увиличение счетчика.
// 2й - Перевод текста в список "как есть" (т.е. без порядка и с повторами),
//      с последующим упорядочиваннием списка и "суммированием" рядом находящихся
//      одинаковых элементов в один учитывая счетчик.
//
// Сперва попробуем первый способ.
//
// Вообще задача требует более конкретных требований (нужен ли todo, нужно ли пол-лимона, ныжны ли числа и т.д.)
// TODO:    [x] парсить не буквы
//          [x] все буквы в один регистр
//          [ ] создание коректного размера массива char* tmp (без переполнения при длинном слове и без лишних размеров)
//          [x] православное сравнение многознаковых констант
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

struct element
{
        char *word = new char[80];  // Слово
        int score = 1;          // Частота
        element *prev = NULL;   // указатель на предыдущий элемент
        element *next = NULL;   // указатель на следующий элемент
};

struct deque
{
        element *head = NULL;   // указатель на начало списка
        element *tail = NULL;   // указатель на конец списка
        int size = 0;
};

void print_List(deque &l, const char* file);
void push(deque &l, char* k); 
void push_back(deque &l, char* k);
void push_in(deque &dic, char* tmp, element* &tmpslct) ;
void adapt(char* &tmp);

int main( )
{
    deque dic;
    char *tmp = new char[80];
    ifstream in;
    in.open( "text" );
    while ((!in.eof()) && (in >> tmp))
    {
        adapt(tmp); 
        push(dic,tmp);
    } 
    delete tmp;
    in.close();
    print_List(dic,"dic");
    return 0;
}

void adapt(char* &c)
{
    int i=0,j=0;
    char *tmp = new char[80];
    while (c[i])
    {
        if ((c[i]>=0xFFFFFFE1)&&(c[i]<=0xFFFFFFEF)) i=i+2; // исключения для 3-6 байтных символов
        if ((c[i]>=0xFFFFFFF1)&&(c[i]<=0xFFFFFFF7)) i=i+3;
        if ((c[i]>=0xFFFFFFF9)&&(c[i]<=0xFFFFFFFB)) i=i+4;
        if (c[i]==0xFFFFFFFD) i=i+5;

        // русские буквы [А-п] + [р-я]
        if (((c[i]==0xFFFFFFD0)&&(c[i+1]>=0xFFFFFF90)&&(c[i+1]<=0xFFFFFFBF))||((c[i]==0xFFFFFFD1)&&(c[i+1]<=0xFFFFFF8F)&&(c[i+1]>=0xFFFFFF80))) {
            if ((c[i]==0xFFFFFFD0)&&(c[i+1]>=0xFFFFFF09)&&(c[i+1]<=0xFFFFFF9F)) // А-П -> а-п
            {
                c[i+1]=c[i+1]+32;
            }
            if ((c[i]==0xFFFFFFD0)&&(c[i+1]>0xFFFFFF9F)&&(c[i+1]<0xFFFFFFB0)) // Р-Я -> р-я
            {
                c[i]++;
                c[i+1]=c[i+1]-32;
            }
            tmp[j]=c[i];
            tmp[j+1]=c[i+1];
            j=j+2; i++;
        }
        if (isalpha(c[i])) // английские буквы
        {
            tmp[i]=tolower(c[i]);
            j++;
        }
        i++;
    }
    strcpy(c , tmp);
    delete tmp;
}

void print_List(deque &l, const char* file)
{
    ofstream out;
    out.open( file ); 
    element *tmp = l.head; // устанавливаем tmp на голову
    if(tmp == NULL) {cout << "Dictinory is empty\n"; return;}    // список пуст
    while (tmp != NULL)
    {
        out << tmp -> word << ' ' << tmp -> score <<  "\n";   // выводим ключ эл.
        tmp = tmp -> next; // двигаем tmp от головы к хвосту
    }
    out.close();
}

void push(deque &dic, char* tmp)
{
    if (tmp[0]==0) return;
    if(dic.head==NULL) push_back(dic,tmp);
    else 
    {   
        element *tmpel = new element;
        element *tmpslct = dic.head;
        while ((tmpslct -> next != NULL)&&(strcmp(tmpslct -> word,tmp)<0)) tmpslct = tmpslct -> next;
        //cout << "check " << strcmp(tmpslct -> word,tmp) << '\n';
        if (!(strcmp(tmpslct -> word,tmp))) {
            tmpslct -> score++; 
        //    cout << "if1" << '\n'; 
        }
        else if (strcmp(tmpslct -> word,tmp)>0) { 
        //    cout << "if2" << '\n'; 
            push_in(dic, tmp, tmpslct); 
        }
        else { 
        //    cout << "if3" << '\n';
            push_back(dic,tmp);
        }
        //cout << "checkout" << '\n';
        delete tmpel;
    }
}

void push_in(deque &dic, char* tmp, element* &tmpslct) 
{
    //cout << "!!!1" << '\n'; 
    element *tmpel = new element;
    tmpel -> prev = tmpslct -> prev;
    tmpel -> next = tmpslct;
    //cout << "!!!2" << '\n';  
    //cout << tmpslct << '\n';  
    //cout << tmpslct -> prev << '\n';
    //cout << tmpslct -> prev -> next << '\n';
    //cout << tmpel << '\n';
    if (tmpslct -> prev != NULL)tmpslct -> prev -> next = tmpel;  /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    else dic.head = tmpel;
    //cout << "!!!3" << '\n'; 
    tmpslct -> prev = tmpel; 
    //cout << "!!!4" << '\n';  
    strcpy(tmpel -> word , tmp);
    //cout << "!!!5" << '\n';  
    dic.size++;
}

void push_back(deque &l, char* k)
{
    element *tmp = new element;
    if(l.head == NULL) l.head = tmp;        // добавляем в голову
    else {
            l.tail -> next = tmp;              // добавляем в хвост
    }
    tmp -> prev = l.tail;
    strcpy(tmp -> word , k);
    l.tail = tmp;
    l.size++;
}