#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=200010;
char s[N],*t=s;
int main(){
#ifndef ONLINE_JUDGE
	freopen("machine.in","r",stdin);
	freopen("machine.out","w",stdout);
#endif
	int n=ni,tot=ni;
	scanf("%s",s);
	char inv=0,fir=0;
	while(*(t+(n&1))){
		char c=*t;
		c^=fir^inv;
		if(tot==0){
			putchar(c);
			int rest=t-s;
			for(;*++t;putchar((*t)^inv));
			for(int i=0;i<rest;i++){
				putchar('B'-((rest-i)&1));
			}
			putchar('\n');
			return 0;
		}
		tot--;
		if(c=='B'){
			t++;
			inv^='A'^'B';
			fir=0;
		}else{
			fir='A'^'B';
		}
	}
	if(n&1){
		putchar((*t)^fir^inv^((tot&1)?('A'^'B'):0));
		for(int i=1;s[i];i++){
			putchar('A'+(i&1));
		}
	}else{
		for(int i=0;s[i];i++){
			putchar('A'+((i&1)==0));
		}
	}
	putchar('\n');
	return 0;
}
