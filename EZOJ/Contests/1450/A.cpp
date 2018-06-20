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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int O=998244353;
const int N=110;
inline lint fpow(lint x,int n){
	lint a=1;
	for(;n;n>>=1,x*=x){
		if(n&1){
			a*=x;
		}
	}
	return a;
}
lint f[N];
lint a,b,c;
lint cnt;
inline bool check(){
	lint t=0;
	for(int i=100;i>=0;i--){
		t=t*b+f[i];
		if(t>c)return false;
	}
	return t==c;
}
void dfs(int e,lint rest){
	if(e==0){
		f[0]=rest;
		cnt+=check();
		return;
	}
	lint t=fpow(a,e);
	for(lint &i=f[e]=0;i*t<=rest;i++){
		dfs(e-1,rest-i*t);
	}
}
inline int Main(){
	memset(f,0,sizeof(f));
	cnt=0;
	int mxe=0;
	{
		lint pw=1;
		for(;pw<b;pw*=a,mxe++);
	}
	dfs(mxe,b);
	return cnt%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("polynomial.in","r",stdin);
	freopen("polynomial.out","w",stdout);
#endif
	for(;scanf("%lld%lld%lld",&a,&b,&c)!=EOF;){
		if(a==1&&b==1){
			puts("infinity");
		}else{
			printf("%d\n",Main());
		}
	}
	return 0;
}
