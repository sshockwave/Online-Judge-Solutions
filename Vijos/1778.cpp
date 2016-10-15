#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char key[110],s[1010];
int main(){
	freopen("vigenere.in","r",stdin);
	freopen("vigenere.out","w",stdout);
	cin>>key>>s;
	bool small;
	for(int i=0,j=0;s[i];i++,j++){
		if(key[j]==0){
			j=0;
		}else if(key[j]>'Z'){
			key[j]-=32;
		}
		small=false;
		if(s[i]>'Z'){
			small=true;
			s[i]-=32;
		}
		s[i]=((int)s[i]-(int)key[j]+26)%26+65;
		if(small){
			s[i]+=32;
		}
	}
	cout<<s;
}
