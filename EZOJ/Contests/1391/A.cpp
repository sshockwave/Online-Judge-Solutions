#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
//#include <fstream>
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
const int N=6010,N2=20000010;
int pri[N2/10],ps=0;
bool np[N2];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			pri[ps++]=i;
		}
		for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
			np[t]=true;
			if(i%p==0)break;
		}
	}
}/*
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}*/
inline int _n(int n){
	return (n*(n+1))>>1;
}
int n,n2,bln[N],tag[N],tim=0;
bool fillnum(int x,int v,int i=::n){
	if(_n(i)<x)return false;
	while(x){
		for(apmin(i,x);i>=1&&tag[i]==tim;i--);
		if(i==0)return false;
		x-=i,bln[i]=v,tag[i]=tim;
	}
	return true;
}
inline bool solve2(int n2=::n2){
	assert((n2&1)==0);
	for(int j=1,i=2;j<ps&&(i=pri[j],i<=n2);j++){
		if(np[n2-i])continue;
		tim++;
		if(fillnum(i,1))return true;
	}
	return false;
}
inline bool solve3(){
	assert(n2>3);
	for(int j=1,i;j<ps;i++){
		i=pri[j];
		assert(i<=n2);
		if(solve2(n2-i)&&fillnum(i,3))return true;
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
#endif
	n=ni,n2=_n(n);
	if(n==1){
		puts("-1");
		return 0;
	}
	sieve(n2);
	if(!np[n2]){
		puts("1");
		for(int i=1;i<=n;i++){
			putchar('1'),putchar(' ');
		}
		putchar('\n');
		return 0;
	}
	memset(bln,0,sizeof(bln));
	if(n2&1?solve3():solve2()){
		puts(n2&1?"3":"2");
		for(int i=1;i<=n;i++){
			printf("%d ",tag[i]==tim?bln[i]:2);
		}
		putchar('\n');
		return 0;
	}
	puts("-1");
	return 0;
}
