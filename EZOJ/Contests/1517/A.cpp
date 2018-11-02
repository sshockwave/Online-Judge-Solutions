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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=500010;
int fa[N],f[N],hei[N];
int tag[N],tim=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
#endif
	const int n=ni;
	mset(fa+1,0,n);
	mset(tag+1,0,n);
	mset(hei+1,0,n);
	int es=0;
	for(int tot=ni,ans=0;tot--;){
		const int tp=ni;
		int u=ni^ans,v=ni^ans;
		++tim;
		for(int x=u;x!=0;x=fa[x]){
			tag[x]=tim;
		}
		int w=v;
		for(;w&&tag[w]<tim;w=fa[w]);
		if(tp==0){
			++es;
			if(w==0){
				for(;fa[u];u=fa[u]);
				for(;fa[v];v=fa[v]);
				if(hei[u]>hei[v]){
					swap(u,v);
				}
				fa[u]=v,f[u]=es;
				if(hei[u]==hei[v]){
					++hei[v];
				}
			}
		}else{
			ans=0;
			if(w){
				for(int x=u;x!=w;x=fa[x]){
					apmax(ans,f[x]);
				}
				for(int x=v;x!=w;x=fa[x]){
					apmax(ans,f[x]);
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
