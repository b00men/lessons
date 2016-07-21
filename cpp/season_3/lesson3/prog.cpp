//
// Первостепенная задача не создание сбалансированного бинарного дерева,
// а обзор уже существующего дерева рекурсией для вывода на экран.
//
// push не доделан. он некоректно обрабатывает второй возврат.
// первое решение - учет флагов в самой структуре дерева
// второе - почитать теорию о сбалансированных деревьях
//
// хорошо бы не использовать up и флаги
//
/*
           0
         /    \
        0      0
       / |    | \
      0  0    0  0
    / |  |\  /|  | \
   0  0  00  xx  x  x
  /| /| /||\/||\ |\ |\
  xx xx xxxxxxxx xx xx 

*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

struct el
{
        int key = 0;  // Слово !!! Очень грубая работа. Каждое слово в 80х байт.
        el *up = NULL;   // указатель на предыдущий элемент
        el *l = NULL;   // указатель на следующий элемент
        el *r = NULL;   // указатель на следующий элемент
};

struct tree
{
        el *root = NULL;   // указатель на начало списка
        int size = 0;
};

void push_back(tree &bin);
void create(bool r,el* &slct);
void push(el* &slct, bool &flag);

void push(el* &slct, bool &flag)
{
    //cout<<"push! \n";
    if (slct->l==NULL)
    {
        cout<<"crt_l \n";
        create(0,slct);
        return;
    }
    else
    {
        if (slct->r==NULL)
        {
            cout<<"crt_r \n";
            create(1,slct);
            return;
        }
        else
        {
            if (!flag)
            {
                cout<<"go to l \n";
                flag=1;
                slct=slct -> l;
                push(slct,flag);
            }
            else
            {
                cout<<"go to up to r \n";
                flag=0;
                slct=slct -> up -> r;
                push(slct,flag);
            }
        }
    }
}

int main( )
{
    tree bin;
    push_back(bin);
    push_back(bin);
    push_back(bin);
    push_back(bin);
    push_back(bin);
    push_back(bin);
    push_back(bin);
    
// делаем обзор
    return 0;
}

void push_back(tree &bin)
{
    if(bin.root == NULL)
    {
        el *tmp = new el;
        bin.root = tmp;        // добавляем в голову
        tmp->key=12;
    }
    else
    {
        el *slct=bin.root;
        bool flag=0; // надо ли возвращаться
        push(slct,flag);
    }
}

void create(bool r,el* &slct)
{
    el *tmp = new el;
    tmp->up=slct;
    tmp->key=12;
    if (r) slct->r=tmp;
    else slct->l=tmp;
}