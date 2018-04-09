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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2000,O=64123;
int k,lim=-1;
int pval[N];
lint ans=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int f[N][N],g[N];
	int tmp[N];
	void dfs(int x,int fa){
		g[x]=0;
		int *F=f[x];
		F[0]=1,memset(F+1,0,k*sizeof(F[0]));
		int &sz=g[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				memset(tmp,0,(min(sz+g[v],k)+1)*sizeof(tmp[0]));
				for(int a=0;a<=sz;a++){
					for(int b=0;b<=g[v];b++){
						int &T=tmp[min(a+b,k)];
						T=(T+(lint)F[a]*f[v][b])%O;
					}
				}
				sz=min(sz+g[v],k);
				memcpy(F,tmp,(sz+1)*sizeof(F[0]));
			}
		}
		if(pval[x]>=lim){
			F[k]=(F[k]+F[k-1])%O;
			sz=min(sz+1,k);
			for(int i=min(k-1,sz);i>=1;i--){
				F[i]=F[i-1];
			}
			F[0]=1;
		}else{
			F[0]++;
		}
		ans+=f[x][k];
	}
}
int lstval[N];
int f[N];
inline bool lcmp(int a,int b){
	return a>b;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("coat.in","r",stdin);
	freopen("coat.out","w",stdout);
#endif
	int n=ni;
	k=ni,ni;
	for(int i=1;i<=n;i++){
		pval[i]=lstval[i]=ni;
	}
	sort(lstval+1,lstval+n+1,lcmp);
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	int ans=0;
	memset(f,0,sizeof(f));
	for(int i=k;i<=n;i++){
		if(lstval[i]==lim){
			f[i]=f[i-1];
		}else{
			lim=lstval[i];
			::ans=0;
			T::dfs(1,0);
			f[i]=::ans%O;
			ans=(ans+(lint)lstval[i]*(f[i]+O-f[i-1]))%O;
		}
	}
	printf("%d\n",ans);
	return 0;
}
