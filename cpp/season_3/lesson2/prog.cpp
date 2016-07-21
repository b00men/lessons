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
//          [ ] сортировка словоря по частоте кпотребления (ждем второй реализации)
//          [ ] запихать все в оболочку
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

struct element
{
        char *word = new char[80];  // Слово !!! Очень грубая работа. Каждое слово в 80х байт.
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

void print_List(deque &l, const char* file);    // вывод словоря
void push(deque &l, char* k);                   // общая функция добовления слова в словарь
void push_back(deque &l, char* k);              // добавить слово в конец
void push_in(deque &dic, char* tmp, element* &tmpslct) ;    // вставить слово перед элементом tmpslct
void adapt(char* &tmp);                         // обработка слов (парсинг и регистр). Работает с русским и английским (utf8-16)

int main( )
{
    deque dic;
    char *tmp = new char[80];       // !!! Переработать
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

void adapt(char* &c) // !!! Хорошо бы грамотно разделить парсинг не букв, и регистры разных алфавитов
{
    int i=0,j=0;
    char *tmp = new char[80];
    while (c[i])
    {
        if ((c[i]>=0xFFFFFFE1)&&(c[i]<=0xFFFFFFEF)) i=i+2;      // исключения для 3-6 байтных символов
        if ((c[i]>=0xFFFFFFF1)&&(c[i]<=0xFFFFFFF7)) i=i+3;      // такие символы просто пропускаем
        if ((c[i]>=0xFFFFFFF9)&&(c[i]<=0xFFFFFFFB)) i=i+4;
        if (c[i]==0xFFFFFFFD) i=i+5;

        // обработка русских букв [А-п] + [р-я]
        if (((c[i]==0xFFFFFFD0)&&(c[i+1]>=0xFFFFFF90)&&(c[i+1]<=0xFFFFFFBF))||((c[i]==0xFFFFFFD1)&&(c[i+1]<=0xFFFFFF8F)&&(c[i+1]>=0xFFFFFF80))) 
        {
            if ((c[i]==0xFFFFFFD0)&&(c[i+1]>=0xFFFFFF09)&&(c[i+1]<=0xFFFFFF9F)) c[i+1]=c[i+1]+32;   // Регистр А-П -> а-п
            if ((c[i]==0xFFFFFFD0)&&(c[i+1]>0xFFFFFF9F)&&(c[i+1]<0xFFFFFFB0))   // Регистр Р-Я -> р-я
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
    if(tmp == NULL) {cout << "Dictionary is empty\n"; return;}    // список пуст
    while (tmp != NULL)
    {
        out << tmp -> word << ' ' << tmp -> score <<  "\n";   // выводим ключ эл.
        tmp = tmp -> next; // двигаем tmp от головы к хвосту
    }
    out.close();
}

void push(deque &dic, char* tmp)
{
    if (tmp[0]==0) return;          // пустые слова не вставляем
    if(dic.head==NULL) push_back(dic,tmp);      // Первое слово в словаре
    else 
    {   
        element *tmpel = new element; // Новый элемент
        element *tmpslct = dic.head;  // Указатель-счетчик для поиска и сравнения
        while ((tmpslct -> next != NULL)&&(strcmp(tmpslct -> word,tmp)<0)) tmpslct = tmpslct -> next; // Нахождение нужного места
        if (!(strcmp(tmpslct -> word,tmp))) tmpslct -> score++;     // при существовании лишь увеличим счетчик
        else if (strcmp(tmpslct -> word,tmp)>0) push_in(dic, tmp, tmpslct); // Если слово нужно вставить гдето от начала или в середине
        else push_back(dic,tmp);    // Иначе ему самое место в конце
        delete tmpel;
    }
}

void push_in(deque &dic, char* tmp, element* &tmpslct) 
{
    element *tmpel = new element;
    tmpel -> prev = tmpslct -> prev; // рулим новые связи
    tmpel -> next = tmpslct;
    if (tmpslct -> prev != NULL)tmpslct -> prev -> next = tmpel;
    else dic.head = tmpel;
    tmpslct -> prev = tmpel; 
    strcpy(tmpel -> word , tmp); 
    dic.size++;
}

void push_back(deque &l, char* k)
{
    element *tmp = new element;
    if(l.head == NULL) l.head = tmp;        // добавляем в голову
    else l.tail -> next = tmp;              // добавляем в хвост
    tmp -> prev = l.tail;
    strcpy(tmp -> word , k);
    l.tail = tmp;
    l.size++;
}