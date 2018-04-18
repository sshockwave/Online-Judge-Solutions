#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=100010,S=1<<11,logN=20,O=998244353;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
namespace T{
	const int E=(::N+10)<<1;
	int to[E],bro[E],head[N],e=0;
	int pool[logN][2][S],(*poolpt[logN])[S],ps=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		for(int i=0;i<logN;i++){
			poolpt[i]=pool[i];
		}
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool vis[N],ontr[E];
	int dep[N],size[N];
	void dfs1(int x,int fa){
		vis[x]=true;
		dep[x]=dep[fa]+1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				ontr[i]=true;
				dfs1(v,x);
			}
		}
	}
	int (*f[N])[S];
	int mask[N],ban[N],summask[N];
	inline void join(int x,int v){
		for(int s=summask[x];s>=0;s=s?(s-1)&summask[x]:-1){
			int f0=f[x][0][s],f1=f[x][1][s];
			f[x][0][s]=f[x][1][s]=0;
			for(int t=summask[v];t>=0;t=t?(t-1)&summask[v]:-1){
				int g0=f[v][0][t],g1=f[v][1][t];
				apadd(f[x][0][s|t],(lint)f0*(g0+g1));
				apadd(f[x][1][s|t],(lint)f1*g0);
			}
		}
		summask[x]|=summask[v];
	}
	int g;
	void gcen(int x,int n){
		int bal=0;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(ontr[i]&&!vis[v=to[i]]){
				gcen(v,n);
				size[x]+=size[v];
				apmax(bal,size[v]);
			}
		}
		apmax(bal,n-size[x]);
		if((bal<<1)<=n){
			g=x;
		}
	}
	void dfs2(int rt,int n){
		gcen(rt,n);
		int x=g;
		f[x]=poolpt[ps++];
		memset(f[x],0,sizeof(pool[0]));
		f[x][0][0]=1;
		f[x][1][0]=1;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(ontr[i]){
				if(!vis[v=to[i]]){
					dfs2(v,size[v]);
				}
				join(x,v);
				poolpt[--ps]=f[v];
			}
		}
		int *nf=f[x][1];
		for(int s=summask[x];s>=0;s=s?(s-1)&summask[x]:-1){
			int t=nf[s];
			nf[s]=0;
			if((ban[x]&s)==0){
				apadd(nf[s|mask[x]],t);
			}
		}
		summask[x]|=mask[x];
		if(x!=rt){
			dfs2(rt,n-size[x]);
		}
	}
}
inline int Main(){
	int n=ni,m=ni;
	T::init();
	for(int i=1;i<=m;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,0);
	int banid=0;
	for(int i=0;i<T::e;i+=2){
		if(T::ontr[i]||T::ontr[i^1])continue;
		int u=T::to[i],v=T::to[i^1];
		if(T::dep[u]<T::dep[v]){
			swap(u,v);
		}
		T::mask[u]|=1<<banid,T::ban[v]|=1<<banid,banid++;
	}
	memset(T::vis,0,sizeof(T::vis));
	T::dfs2(1,n);
	lint ans=0;
	for(int s=T::summask[1];s>=0;s=s?(s-1)&T::summask[1]:-1){
		ans+=T::f[1][0][s]+T::f[1][1][s];
	}
	return ans%O;
}
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("duliu.in","r",stdin);
	freopen("duliu.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
