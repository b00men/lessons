#include <iostream>
#include <fstream>

using namespace std;

int read (const char *name, int &n_w, int &n_s){
	int n_c=0;
	ifstream f(name);
	if(!f) return 0;
	n_s++;
	for(char c, w=0; f.get(c); n_c++){
		if((c==32)||(c==9)||(c==10)){
			w=0;
			if(c==10){
				n_s++;
				n_c--;
			}
		}
		else {
			n_w+=!w;
			w=1;
		}
	}
	f.close();
	return n_c;
}

int main(int argc, char *argv[]){
	char buf[900];
	int n_c=0,n_w=0,n_s=0;		// total number of chars, words & strings
	if(argc<2) while(cin>>buf) n_c+=read(buf,n_w,n_s);
	else for (int i=1; i<argc; i++) n_c+=read(argv[i],n_w,n_s);
	cout<<n_c<<' '<<n_w<<' '<<n_s<<'\n';
	return 0;
}