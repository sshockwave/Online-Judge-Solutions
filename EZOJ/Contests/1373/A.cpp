#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=5010,V=32768,logN=14;
int fa[N],v[N],w[N];
struct Query{
	int v,id;
};
vector<Query>q[N];
int mx=0,ans[N];
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	int size[N],bal[N];
	int pool[logN][V],(*ps)[V]=pool,*f[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(size,0,sizeof(size));
		memset(f,0,sizeof(f));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void gcenter(int x,int &g,int n){
		size[x]=1,bal[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(f[v=to[i]]==0){
				gcenter(v,g,n);
				size[x]+=size[v];
				apmax(bal[x],size[v]);
			}
		}
		apmax(bal[x],n-size[x]);
		if(g==0||bal[x]<bal[g]){
			g=x;
		}
	}
	inline void dp(int f[],int nf[],int v,int w){
		memcpy(nf,f,(mx+1)<<2);
		assert(v);
		for(int i=v;i<=mx;i++){
			apmax(nf[i],max(nf[i-1],nf[i-v]+w));
		}
	}
	void pdiv(int rt,int n){
		int x=0;
		gcenter(rt,x,n);
		f[x]=*ps++;
		if(x==rt){
			dp(f[fa[x]],f[x],v[x],w[x]);
		}else{
			pdiv(rt,size[rt]-size[x]);
		}
		for(vector<Query>::iterator it=q[x].begin();it!=q[x].end();it++){
			ans[it->id]=f[x][it->v];
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(f[v=to[i]]){
				dp(f[x],f[v],::v[v],w[v]);
			}else{
				pdiv(v,size[v]);
			}
		}
		ps--;
	}
}
int c[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("shop.in","r",stdin);
	freopen("shop.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		v[i]=ni,w[i]=ni;
	}
	T::init();
	fa[1]=0;
	for(int i=2;i<=n;i++){
		T::ae(fa[i]=ni,i);
	}
	for(int i=1;i<=m;i++){
		c[i]=ni;
		apmax(mx,c[i]);
	}
	for(int i=1;i<=m;i++){
		q[ni].push_back((Query){c[i],i});
	}
	T::f[0]=*T::ps++;
	memset(T::f[0],0,mx<<2);
	T::pdiv(1,n);
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
}
