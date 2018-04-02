#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long double db;
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
const int N=300010;
const db DINF=1e100,EPS=1e-7;
struct Edge{
	int u,v,w;
}edg[N];
namespace G{
	const int E=::N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	bool vis[N];
	void dfs(int x){
		if(vis[x])return;
		vis[x]=true;
		for(int i=head[x];~i;i=bro[i]){
			dfs(to[i]);
		}
	}
}
namespace method5{
	db _x[N],_y[N];
	inline db main(int n,int m){
		for(int i=1;i<=m;i++){
			_x[i]=_x[i-1]+(db)edg[i].w/(n-1);
			_y[i]=_y[i-1]+(db)edg[i].w/(n-1)*edg[i].w;
		}
		db ans=1e100;
		for(int l=1,r=n-1;r<=m;l++,r++){
			db x=_x[r]-_x[l-1],y=_y[r]-_y[l-1];
			apmin(ans,y-x*x);
		}
		return ans;
	}
}
namespace method1{
	namespace kruskal{
		int fa[N];
		inline void init(int n){
			memset(fa+1,0,n<<2);
		}
		inline int root(int x){
			return fa[x]?fa[x]=root(fa[x]):x;
		}
		inline bool psh(int id){
			int u=root(edg[id].u),v=root(edg[id].v);
			return u!=v?fa[u]=v,true:false;
		}
	}
	int lst[N];
	db ans=DINF;
	inline bool work(int n,int m,int x,bool flag){
		kruskal::init(n);
		using kruskal::psh;
		psh(lst[x]);
		int l=x-1,r=x+1;
		db sumx=(db)edg[lst[x]].w/(n-1);
		db sumy=(db)edg[lst[x]].w/(n-1)*edg[lst[x]].w;
		bool retflag=false;
		for(int tot=n-2;tot;){
			int c;
			if(r>m){
				c=lst[l--];
			}else if(l<1){
				c=lst[r++];
			}else{
				lint a=lst[l],b=lst[r];
				a=(edg[a].w-2ll*edg[x].w)*edg[a].w;
				b=(edg[b].w-2ll*edg[x].w)*edg[b].w;
				if(a<b){
					c=lst[l--];
				}else if(b<a){
					c=lst[r++];
				}else if(flag){
					c=lst[l--];
				}else{
					c=lst[r++];
					retflag=true;
				}
			}
			if(psh(c)){
				tot--;
				sumx+=(db)edg[c].w/(n-1);
				sumy+=(db)edg[c].w/(n-1)*edg[c].w;
			}
		}
		apmin(ans,sumy-sumx*sumx);
		return retflag;
	}
	inline bool lcmp(int a,int b){
		return edg[a].w<edg[b].w;
	}
	inline db main(int n,int m){
		for(int i=1;i<=m;i++){
			lst[i]=i;
		}
		sort(lst+1,lst+m+1,lcmp);
		for(int i=1;i<=m;i++){
			if(work(n,m,i,false)){
				work(n,m,i,true);
			}
		}
		return ans;
	}
}
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("var.in","r",stdin);
	freopen("var.out","w",stdout);
#endif
	int n=ni,m=ni,tp=ni;
	bool task5=true;
	G::init();
	for(int i=1;i<=m;i++){
		edg[i]=(Edge){ni,ni,ni};
		G::add(edg[i].u,edg[i].v,edg[i].w);
		task5&=edg[i].u==(i%n)+1&&edg[i].v==((i+1)%n)+1;
	}
	if(task5){
		if(m<n-1){
			puts("-1");
		}else{
			printf("%.10lf\n",(double)method5::main(n,m));
		}
		return 0;
	}else{
		G::dfs(1);
		for(int i=1;i<=n;i++){
			if(!G::vis[i]){
				puts("-1");
				return 0;
			}
			lst[i]=i;
		}
		printf("%.10lf\n",(double)method1::main(n,m));
	}
	return 0;
}
