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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=2510;
char buf[N],*tal=buf;
inline void op(int c){
	c+='0';
	if(tal>buf&&((tal[-1]-'1')^(c-'1'))==1){
		tal--;
	}else{
		tal++[0]=c;
	}
}
inline void bu(){
	op(1),op(4);
}
inline void inv(){
	op(6),bu(),op(5);
}
inline void addone(){
	op(6),op(3),inv();
}
void solve(int p,int q){
	if(p%q){
		solve(q,p%q);
		inv();
	}
	for(int tot=p/q;tot--;addone());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("maths.in","r",stdin);
	freopen("maths.out","w",stdout);
#endif
	{
		char s[10];
		scanf("%s",s);
	}
	int p=ni,q=ni,d=gcd(p,q);
	solve(sqr(p/d),sqr(q/d));
	tal[0]=0;
	puts(buf);
	return 0;
}
