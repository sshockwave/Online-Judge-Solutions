#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=1e6+10,E=1e6+10;
int flag;
int lst[N],ls=0;
namespace G2{
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n),e=0;
	}
	inline void ae(int u,int v){
		assert(u!=v);
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int stat[N];
	inline void work(int n,bool ok[]){
		mset(stat+1,0,n);
		int rcnt=0;
		for(int t=1;t<=ls;t++){
			const int x=lst[t];
			for(int i=head[x],v;~i;i=bro[i]){
				if(stat[v=to[i]]==1){
					stat[v]=2,--rcnt;
				}
			}
			if(rcnt==0){
				ok[x]=true;
			}
			stat[x]=1,++rcnt;
		}
	}
}
namespace G{
	int fr[E],to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		fr[e]=u,to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfn[N],low[N],tim=0;
	int nstk[N],nss=0;
	int stk[N],ss=0;
	bool instk[N];
	int bln[N];
	inline void pshstk(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		nstk[++nss]=x;
	}
	void tarjan(const int n){
		mset(dfn+1,0,n);
		mset(instk+1,0,n);
		for(int t=1;t<=n;t++){
			if(dfn[t])continue;
			pshstk(t);
			bool bakw=false;
			for(;nss;){
				const int x=nstk[nss];
				if(bakw){
					apmin(low[x],low[nstk[nss+1]]);
					bakw=false;
				}
				for(int &i=head[x],v;~i;i=bro[i]){
					if(dfn[v=to[i]]==0){
						pshstk(v);
						break;
					}else if(instk[v]){
						apmin(low[x],dfn[v]);
					}
				}
				if(nstk[nss]==x){
					if(dfn[x]==low[x]){
						int v;
						do{
							v=stk[--ss],instk[v]=false;
							bln[v]=x;
						}while(v!=x);
						lst[++ls]=x;
					}
					--nss,bakw=true;
				}
			}
		}
	}
}
bool ok1[N],ok2[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("wtmsb.in","r",stdin);
	freopen("wtmsb.out","w",stdout);
#endif
	const int n=ni;
	G::init(n);
	for(int tot=ni;tot--;){
		const int u=ni,v=ni;
		G::ae(u,v);
	}
	G::tarjan(n);
	{
		G2::init(n);
		for(int i=0;i<G::e;i++){
			const int u=G::bln[G::fr[i]],v=G::bln[G::to[i]];
			if(u!=v){
				G2::ae(u,v);
			}
		}
		G2::work(n,ok1);
	}
	reverse(lst+1,lst+ls+1);
	{
		G2::init(n);
		for(int i=0;i<G::e;i++){
			const int u=G::bln[G::fr[i]],v=G::bln[G::to[i]];
			if(u!=v){
				G2::ae(v,u);
			}
		}
		G2::work(n,ok2);
	}
	using G::bln;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=ok1[bln[i]]&&ok2[bln[i]];
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(ok1[bln[i]]&&ok2[bln[i]]){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
