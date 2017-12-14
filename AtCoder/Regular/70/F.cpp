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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2010;
inline bool ask(int a,int b){
	printf("? %d %d\n",a,b);
	fflush(stdout);
	char c;
	while(!isalpha(c=getchar()));
	return c=='Y';
}
int stk[N],ss=0;
char s[N];
int main(){
	int n;
	{
		int a=ni,b=ni;
		if(a<=b){
			puts("Impossible");
			return 0;
		}
		n=a+b;
	}
	for(int i=0;i<n;i++){
		if(ss==0||ask(stk[ss-1],i)){
			stk[ss++]=i;
		}else if(ss){
			ss--;
		}
	}
	int t=stk[ss-1];
	for(int i=0;i<n;i++){
		s[i]=i==t||ask(t,i)?'1':'0';
	}
	s[n]=0;
	printf("! %s\n",s);
	return 0;
}
