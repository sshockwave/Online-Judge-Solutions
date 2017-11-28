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
const int N=100010;
int lim;
int r[N];
int lb,hb;
int tim=0;
lint mn=0,cur=0,mx=0;
inline int go(int x,int d,int t){
	return max(0ll,min((lint)lim,(lint)d*t+x));
}
inline void workto(int d,int t){
	int del=t-tim;
	tim=t;
	lb=go(lb,d,del),hb=go(hb,d,del);
	cur+=(lint)d*del;
	apmin(mn,cur);
	apmax(mx,cur);
}
inline int ask(int x){
	if(x<=-mn)return lb;
	else if(x>=lim-mx)return hb;
	else return x+cur;
}
int main(){
	lb=0,lim=hb=ni;
	int n=ni;
	r[0]=0;
	for(int i=1;i<=n;i++){
		r[i]=ni;
	}
	int d=-1;
	for(int i=1,tot=ni;tot--;){
		int tim=ni;
		for(;i<=n&&r[i]<=tim;workto(d,r[i]),d=-d,i++);
		workto(d,tim);
		printf("%d\n",ask(ni));
	}
	return 0;
}
