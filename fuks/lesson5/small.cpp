#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

char buf[900];
int c=0, w=0, s=0, i=1;

void read (char *name){
	ifstream f(name);
	if(!f) return;
	for(; f.getline(buf,900); s++) c+=strlen(buf);
	for(f.clear(), f.seekg(0); f>>buf; w++);
}

int main(int argc, char *argv[]){
	if(argc<2) while(cin>>buf) read(buf);
	else for (; i<argc; i++) read(argv[i]);
	cout<<c<<' '<<w<<' '<<s<<'\n';
	return 0;
}