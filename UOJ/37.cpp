#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=15,SN=1<<N,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int pw2[N*N],bcnt[SN];
int out[SN],inner[SN];
int f[SN],g[SN],h[SN],v[SN];
int main(){
#ifndef ONLINE_JUDGE
	freopen("scon.in","r",stdin);
	freopen("scon.out","w",stdout);
#endif
	int n=ni,sn=1<<n;
	pw2[0]=1;
	for(int i=1,tot=ni;i<=tot;i++){
		int u=ni-1,v=ni-1;
		out[1<<u]|=1<<v;
		pw2[i]=mul(pw2[i-1],2);
	}
	for(int s=1,b;s<sn;s++){
		b=s&-s;
		out[s]=out[s^b]|out[b];
		bcnt[s]=bcnt[s^b]+1;
	}
	for(int s=1;s<sn;s++){
		for(int i=0;i<n;i++){
			if((s>>i)&1){
				inner[s]+=bcnt[out[1<<i]&s];
			}
		}
		int x=s&-s,ns=s^x;
		for(int t=ns;t;t=(t-1)&ns){
			apadd(h[s],mul(f[s^t],h[t]));
		}
		h[s]=(MOD-h[s])%MOD;
		for(int t=ns,b;t;t=(t-1)&s){
			b=s^t;
			v[b]=v[b^(b&-b)]+bcnt[out[b&-b]&s];
		}
		v[s]=inner[s];
		for(int t=s;t;t=(t-1)&s){
			apadd(g[s],mul(h[t],pw2[v[t]-inner[t]+inner[s^t]]));
		}
		apadd(h[s],f[s]=sub(pw2[inner[s]],g[s]));
	}
	printf("%d\n",f[sn-1]);
	return 0;
}
