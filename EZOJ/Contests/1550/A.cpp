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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
struct Fenwick{
	int *c,n;
	inline void init(int _n){
		c=new int[n=_n]-1;
		mset(c+1,0,n);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x)const{
		apmin(x,n);
		int a=0;
		for(;x;a+=c[x],x&=x-1);
		return a;
	}
};
bool ison[N];
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
}
namespace pdiv{
	const int logN=18;
	using namespace T;
	bool vis[N];
	int lev[N];
	struct Info{
		int rt,rt2;//rt2:tofa con
		int fa,dep;
		int sonligcnt;
	}tr[N][logN];
	Fenwick val[N],val2[N];//val2:tofa
	int siz[N],hei[N],g;
	void gcen(int x,int n){
		vis[x]=true;
		int bal=0;
		siz[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			gcen(v,n);
			apmax(bal,siz[v]);
			siz[x]+=siz[v];
		}
		apmax(bal,n-siz[x]);
		if(bal*2<=n){
			g=x;
		}
		vis[x]=false;
	}
	void dfs_data(int x){
		vis[x]=true,hei[x]=0,siz[x]=1;
		const int d=++lev[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			tr[v][d]=(Info){tr[x][d].rt,tr[x][d].rt2,x,tr[x][d].dep+1,0};
			dfs_data(v);
			siz[x]+=siz[v];
			apmax(hei[x],hei[v]+1);
		}
		vis[x]=false;
	}
	int solve(int x,int n){
		gcen(x,n),x=g;
		vis[x]=true,hei[x]=0,siz[x]=1;
		const int d=++lev[x];
		tr[x][d]=(Info){x,0,0,0,0};
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			tr[v][d]=(Info){x,v,x,1,0};
			dfs_data(v);
			siz[x]+=siz[v];
			apmax(hei[x],hei[v]+1);
		}
		val[x].init(hei[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			const int h=hei[v]+1;
			v=solve(v,siz[v]);
			val2[v].init(h);
		}
		return x;
	}
	inline void main(int n){
		mset(vis+1,0,n);
		mset(lev+1,0,n);
		solve(1,n);
	}
	inline int ask_tr(const int v,int len,int d){
		assert(d<lev[v]);
		if(len<0)return 0;
		const int x=tr[v][d].rt,y=tr[v][d].rt2;
		int ans=0;
		if(len){
			ans+=val[x].sum(len);
			ans-=val2[tr[v][d+1].rt].sum(len);
			if(ison[x]){
				ans-=tr[x][d].sonligcnt-ison[y];
			}
		}
		ans+=!ison[y]&&ison[x];
		return ans;
	}
	inline int ask(int x,int len){
		int ans=val[x].sum(len);
		for(int i=1;i<lev[x];i++){
			ans+=ask_tr(x,len-tr[x][i].dep,i);
		}
		return ans;
	}
	inline void alt(const int x){
		const int dt=!ison[x]?1:-1;
		ison[x]^=1;
		for(int i=1;i<lev[x];i++){
			const int fa=tr[x][i].fa;
			const int dep=tr[x][i].dep;
			Fenwick &b=val[tr[x][i].rt],&b2=val2[tr[x][i+1].rt];
			if(dep==1||!ison[fa]){
				b.add(dep,dt),b2.add(dep,dt);
			}
			tr[fa][i].sonligcnt+=dt;
			{
				int v=tr[x][i].sonligcnt;
				if(dt>0){
					v=-v;
				}
				b.add(dep+1,v),b2.add(dep+1,v);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("lights.in","r",stdin);
	freopen("lights.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	pdiv::main(n);
	{
		static char s[N];
		scanf("%s",s+1);
		for(int i=1;i<=n;i++){
			if(s[i]=='1'){
				pdiv::alt(i);
			}
		}
	}
	for(;tot--;){
		const int op=ni,x=ni;
		if(op==1){
			pdiv::alt(x);
		}else{
			bool v=ison[x];
			if(v){
				pdiv::alt(x);
			}
			printf("%d\n",pdiv::ask(x,ni));
			if(v){
				pdiv::alt(x);
			}
		}
	}
	return 0;
}
