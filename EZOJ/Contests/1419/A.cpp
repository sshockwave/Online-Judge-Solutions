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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace T{
	const int E=::N;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	lint f[N],g[N];
	void dfs(int x){
		f[x]=0;
		lint mx=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			f[x]+=f[v]+val[i];
			apmax(mx,val[i]);
		}
		g[x]=f[x],f[x]-=mx;
	}
}
int pv[N];
namespace G{
	int vis[N],tim=0;
	bool isrt[N];
	inline void main(int a[],int c[],int n){
		mset(vis+1,0,n);
		mset(isrt+1,0,n);
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			int j=i;
			++tim;
			int lstval;
			for(;!vis[j];j=a[j]){
				vis[j]=tim;
				lstval=c[j];
			}
			if(vis[j]<tim)continue;
			for(;!isrt[j];j=a[j]){
				isrt[j]=true;
				pv[j]=lstval,lstval=c[j];
			}
		}
		T::init();
		for(int i=1;i<=n;i++){
			if(!isrt[i]){
				T::ae(a[i],i,c[i]);
			}
		}
	}
}
int a[N],c[N];
bool vis[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("telegraph.in","r",stdin);
	freopen("telegraph.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni,c[i]=ni;
	}
	G::main(a,c,n);
	using G::isrt;
	mset(vis+1,0,n);
	lint ans=0;
	int ringcnt=0;
	lint f[2];
	bool hastree=false;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		if(!isrt[i])continue;
		++ringcnt;
		int j=i;
		lint mnval=LINF;
		f[0]=0,f[1]=LINF;
		for(;!vis[j];j=a[j]){
			vis[j]=true;
			T::dfs(j);
			lint f1=f[1];
			f[1]=f[0]+pv[j]+T::f[j];
			if(f1<LINF){
				apmin(f[1],f1+min(pv[j]+T::f[j],T::g[j]));
			}
			f[0]+=T::g[j];
			apmin(mnval,c[j]);
			hastree|=T::head[j]!=-1;
		}
		assert(f[1]<=f[0]+mnval);
		ans+=f[1];
	}
	if(ringcnt==1&&!hastree){
		puts("0");
	}else{
		printf("%lld\n",ans);
	}
	return 0;
}
