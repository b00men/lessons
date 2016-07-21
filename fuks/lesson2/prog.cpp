#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

bool sptrcmp (char s, char sptr []); // compare symbol with separators vector

int main( )
{
    char str[80], sptr[80];
    int nw; // number of words
    bool w; // this is word?
    cout<<"please, input a separators vector\n";
    gets(sptr);
    cout<<"please, input a strings\n(input empty string if you wont exit)\n";
    for (;;)
    {
        gets(str);
        if (!strlen(str)) break;
        nw=0;
        w=0;
        for(int i=0; i<=strlen(str); i++)
        {
            if ((!sptrcmp(str[i],sptr))&&(str[i]!=0)) w=1;
            else if (w) {nw++; w=0;}
        }
        cout<<nw<<'\n';
    }
    return 0;
}

bool sptrcmp (char s, char sptr []) // compare symbol with separators vector
{
    for (int i=0;i<strlen(sptr);i++) if (s==sptr[i]) return 1;
    return 0;
}