#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

int main( )
{
    char num[10][15]={"нуль","один","два","три","четыре","пять","шесть","семь","восемь","девять"};
    unsigned int n;
    for(;;) {
        //cin>>n;
        scanf("%d",&n);
        if(n>9) break;
        printf("%s ",num[n]);
        //cout<<num[n]<<'\n';
    }
    return 0;
}