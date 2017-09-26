#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
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
inline int sgn(int x){
	return x>0?1:x<0?-1:0;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7f;
const double EPS=1e-4;
struct Point{
	int x,y;
	inline friend Point operator - (const Point &a,const Point &b){
		return (Point){a.x-b.x,a.y-b.y};
	}
	inline friend lint crs(const Point &a,const Point &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
}pt[N];
namespace revG{
	const int N=400010,E=200010;
	int to[E],bro[E],val[E],head[N],e=0;
	int fa[N],n=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(fa,0,sizeof(fa));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline int nn(){
		return ++n;
	}
	int root(int x){
		return fa[x]?(fa[x]=root(fa[x])):x;
	}
	inline void uni(int u,int v){
		if(root(u)!=root(v)){
			fa[root(u)]=root(v);
		}
	}
	int nlst[N],ns=0;
	lint f[N][100];
	int contri[100];
	inline void work(){
		for(int i=1;i<=n;i++){
			if(fa[i]==0){
				nlst[++ns]=i;
			}
		}
		contri[0]=1;
		for(int i=1,c=1;contri[i-1];i++){
			c=4263ll*c%1632899;
			contri[i]=(lint)contri[i-1]*(c-1)%1632899;
		}
		assert(contri[96]&&contri[97]==0);
		memset(f,0,sizeof(f));
		for(int i=96;i>=1;i--){
			for(int j=1;j<=ns;j++){
				int x=nlst[j];
				lint mn=LINF;
				for(int t=head[x];~t;t=bro[t]){
					apmin(mn,f[to[t]][i+1]+(lint)val[t]*contri[i]);
				}
				f[x][i]=mn;
			}
		}
	}
}
namespace G{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	bool vis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	inline bool solarcmp(int a,int b){
		assert(to[a^1]==to[b^1]);
		Point base=pt[to[a^1]],pa=pt[to[a]]-base,pb=pt[to[b]]-base;
		if(sgn(pa.y)*sgn(pb.y)<0){
			return pa.y>0;
		}
		if(pa.y==0||pb.y==0){
			if(pa.y==0){
				return pb.y>=0?pa.x>0:true;
			}else{
				return pa.y>0?pb.x<0:false;
			}
		}
		return crs(pa,pb)>0;
	}
	int lnode[N],rnode[N];
	int out[N],ids[N];
	void dfs(int x){
		vis[x]=true;
		int os=0;
		for(int i=head[x];~i;i=bro[i]){
			out[os++]=i;
		}
		sort(out,out+os,solarcmp);
		for(int i=0;i<os;i++){
			ids[i]=revG::nn();
		}
		for(int i=0;i<os;i++){
			lnode[out[i]]=ids[(i+1)%os];
			rnode[out[i]]=ids[i];
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]]){
				revG::uni(lnode[i],rnode[i^1]);
				revG::uni(rnode[i],lnode[i^1]);
			}else{
				dfs(v);
			}
		}
	}
	inline void pushnodes(){
		for(int i=0;i<e;i++){
			lnode[i]=revG::root(lnode[i]);
			rnode[i]=revG::root(rnode[i]);
			revG::ae(lnode[i],rnode[i],val[i]);
		}
	}
}
inline double caly(int e,int x){
	Point el=pt[G::to[e<<1]],er=pt[G::to[(e<<1)|1]];
	return (double)(er.y-el.y)/(er.x-el.x)*(x-el.x)+el.y;
}
int lst[N];
int global;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{//[lst[x->l],lst[x->r+1])
		int l,m,r;
		node lson,rson;
		vector<int>e;
	}*rt;
	struct Info{
		int n;
		double low;
	};
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->e.clear();
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void cover(node x,int e){
		int xl=pt[G::to[e<<1]].x,xr=pt[G::to[(e<<1)|1]].x;
		if(xl>xr){
			swap(xl,xr);
		}
		if(xl<=lst[x->l]&&xr>=lst[x->r+1]){
			x->e.push_back(e);
			return;
		}
		if(x->l==x->r){
			return;
		}
		if(xl<lst[x->m+1]){
			cover(x->lson,e);
		}
		if(xr>=lst[x->m+1]){
			cover(x->rson,e);
		}
	}
	double yval[G::E];
	inline bool ecmp(int a,int b){
		return yval[a]<yval[b];
	}
	void sortvec(node x){
		for(int i=0,ti=x->e.size();i<ti;i++){
			yval[x->e[i]]=caly(x->e[i],lst[x->l]);
		}
		sort(x->e.begin(),x->e.end(),ecmp);
		if(x->l!=x->r){
			sortvec(x->lson),sortvec(x->rson);
		}
	}
	inline Info ginfo(node x,double a,double b){
		if(x->e.size()==0){
			return (Info){global,-1e30};
		}
		int l=0,r=x->e.size()-1;
		while(l<r){
			int m=((l+r)>>1)+1;
			if(caly(x->e[m],a)<b){
				l=m;
			}else{
				r=m-1;
			}
		}
		int e=x->e[l]<<1;
		if(pt[G::to[e]].x<pt[G::to[e^1]].x){//todo
			e^=1;
		}
		double tmp=caly(e>>1,a);
		if(tmp<b){
			return (Info){G::lnode[e],tmp};
		}else{
			return (Info){G::rnode[e],-1e30};
		}
	}
	Info ask(node x,double a,double b){
		Info here=ginfo(x,a,b);
		if(x->l==x->r){
			return here;
		}
		Info sons=ask(a+EPS<lst[x->m+1]?x->lson:x->rson,a,b);
		return here.low>sons.low?here:sons;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dis.in","r",stdin);
	freopen("dis.out","w",stdout);
#endif
	int n=ni,tot=ni,ls=0,mnx=INF,mxx=0;
	for(int i=1;i<=n;i++){
		pt[i]=(Point){ni,ni};
		lst[++ls]=pt[i].x;
		apmin(mnx,pt[i].x);
		apmax(mxx,pt[i].x);
	}
	G::init(),revG::init();
	while(tot--){
		int u=ni,v=ni;
		G::add(u,v,ni);
	}
	G::dfs(1);
	G::pushnodes();
	revG::work();
	sort(lst+1,lst+ls+1);
	ls=unique(lst+1,lst+ls+1)-lst-1;
	lst[ls+1]=INF;
	seg::rt=seg::build(1,ls);
	for(int i=0;i<G::e;i+=2){
		if(pt[G::to[i]].x!=pt[G::to[i^1]].x){
			seg::cover(seg::rt,i>>1);
		}
	}
	seg::sortvec(seg::rt);
	global=seg::ask(seg::rt,mnx,-1).n;
	for(int tot=ni;tot--;){
		double a,b,c,d;
		int t;
		scanf("%lf%lf%lf%lf%d",&a,&b,&c,&d,&t);
		if(a<mnx||a>mxx){
			printf("%lld\n",revG::f[global][1]);
		}else{
			printf("%lld\n",revG::f[seg::ask(seg::rt,a,b).n][1]);
		}
	}
	return 0;
}
