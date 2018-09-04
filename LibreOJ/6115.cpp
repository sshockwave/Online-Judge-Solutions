#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
typedef long long lint;
typedef unsigned int uint;
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=900010,M=100000,DD=5,D=1<<5,K=350;
struct BS{
	int a[N/D];
	inline int operator [] (const int i){
		return (a[i>>DD]>>(i&31))&1;
	}
	inline void flip(const int i){
		a[i>>DD]^=1<<(i&31);
	}
}iskey,isdepk;
int fa[N];
int tfa[N/K],keylst[N/K],ks=0;
inline int getid(int x){
	assert(iskey[x]);
	int l=1,r=ks;
	for(;l<r;){
		const int m=(l+r)>>1;
		if(keylst[m]>x){
			r=m-1;
		}else if(keylst[m]<x){
			l=m+1;
		}else return m;
	}
	assert(keylst[l]==x);
	return l;
}
inline int getkey(int x){
	for(;!iskey[x];x=fa[x]);
	return getid(x);
}
inline int lca(int u,int v){
	int ukey=getkey(u),vkey=getkey(v);
	for(;ukey!=vkey;){
		if(keylst[ukey]>keylst[vkey]){
			u=keylst[ukey],ukey=tfa[ukey];
		}else{
			v=keylst[vkey],vkey=tfa[vkey];
		}
	}
	for(;u!=v;u>v?(u=fa[u]):(v=fa[v]));
	return u;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("lca.in","r",stdin);
	freopen("lca.out","w",stdout);
#endif
	int n=ni,m=ni;
	isdepk.flip(1);
	iskey.flip(1),keylst[++ks]=1;
	for(int i=2;i<=n;i++){
		fa[i]=ni;
		int j=1;
		int firx=0;
		for(int x=fa[i];;x=fa[x],++j){
			if(isdepk[x]){
				if(j==K){
					isdepk.flip(i);
				}
				if(firx==0){
					firx=x;
				}
			}
			if(iskey[x])break;
		}
		if(j>=K*2){
			assert(firx);
			iskey.flip(firx),keylst[++ks]=firx;
			assert(iskey[firx]);
		}
	}
	std::sort(keylst+2,keylst+ks+1);
	for(int i=2;i<=ks;i++){
		tfa[i]=getkey(fa[keylst[i]]);
	}
	for(;m--;){
		printf("%d\n",lca(ni,ni));
	}
	return 0;
}
