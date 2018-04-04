#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=500010,INF=0x7f7f7f7f;
namespace BIT{
	int c[N],tag[N],n,tim=0;
	inline void init(int _n){
		n=_n;
	}
	inline void can(int x){
		if(tag[x]<tim){
			c[x]=0;
			tag[x]=tim;
		}
	}
	inline void add(int x,int v){
		for(;x<=n;can(x),c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int a=0;
		for(;x;can(x),a+=c[x],x^=x&-x);
		return a;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
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
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],dfe[N],tim=0;
	void dfs1(int x){
		dep[x]=dep[fa[x]]+1;
		dfn[x]=++tim;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
		dfe[x]=tim;
	}
	void dfs2(int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				dfs2(v);
			}
		}
	}
	inline int lca(int u,int v){
		for(;top[u]!=top[v];dep[top[u]]>dep[top[v]]?(u=fa[top[u]]):(v=fa[top[v]]));
		return dep[u]<dep[v]?u:v;
	}
	inline void addv(int u,int v,int w){
		BIT::add(dfn[u],w),BIT::add(dfn[v],w);
		int t=lca(u,v);
		BIT::add(dfn[t],-w);
		if(fa[t]){
			BIT::add(dfn[fa[t]],-w);
		}
	}
	inline int pval(int x){
		return BIT::ask(dfn[x],dfe[x]);
	}
}
struct Query{
	int tp,x,y,v,rnk;//ans in v
}qry[N];
void solve(Query *q[],int n){
	int mn=INF,mx=-INF,mxv=-INF,qcnt=0;
	for(int i=1;i<=n;i++){
		if(q[i]->tp==1){
			apmin(mn,q[i]->rnk);
			apmax(mx,q[i]->rnk);
			apmax(mxv,q[i]->v);
		}else if(q[i]->tp==3){
			qcnt++;
		}
	}
	if(qcnt==0)return;
	if(mn==mx){
		for(int i=1;i<=n;i++){
			if(q[i]->tp==3){
				q[i]->v=mxv;
			}
		}
		return;
	}
	int m=(mx+mn)>>1;//>m okay
	assert(mx>m);
	static Query *lst1[N],*lst2[N];
	int ls1=0,ls2=0;
	BIT::tim++;
	int curcnt=0;
	for(int i=1;i<=n;i++){
		if(q[i]->tp==3){
			if(T::pval(q[i]->x)==curcnt){
				lst1[++ls1]=q[i];
			}else{
				lst2[++ls2]=q[i];
			}
		}else if(q[i]->rnk<=m){
			lst1[++ls1]=q[i];
		}else{
			int dt=3-q[i]->tp*2;
			T::addv(q[i]->x,q[i]->y,dt);
			curcnt+=dt;
			lst2[++ls2]=q[i];
		}
	}
	assert(ls1+ls2==n);
	memcpy(q+1,lst1+1,ls1*sizeof(q[0]));
	memcpy(q+ls1+1,lst2+1,ls2*sizeof(q[0]));
	solve(q,ls1);
	solve(q+ls1,ls2);
}
int *num[N];
inline bool ncmp(int *a,int *b){
	return *a<*b;
}
Query *q[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("company.in","r",stdin);
	freopen("company.out","w",stdout);
#endif
	int n=ni,m=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2(1);
	BIT::init(T::tim);
	int ns=0;
	qry[0]=(Query){1,1,1,-1,-1},num[++ns]=&qry[0].rnk;
	for(int i=1;i<=m;i++){
		qry[i].tp=ni;
		if(qry[i].tp==1){
			qry[i].x=ni;
			qry[i].y=ni;
			qry[i].v=qry[i].rnk=ni;
			num[++ns]=&qry[i].rnk;
		}else if(qry[i].tp==2){
			qry[i]=qry[ni];
			qry[i].tp=2;
			num[++ns]=&qry[i].rnk;
		}else{
			qry[i].x=ni;
		}
	}
	sort(num+1,num+ns+1,ncmp);
	for(int i=1,ti=ns,&j=ns=0,v=-INF;i<=ti;i++){
		*num[i]=*num[i]!=v?v=*num[i],++j:j;
	}
	for(int i=0;i<=m;i++){
		q[i]=qry+i;
	}
	solve(q-1,m+1);
	for(int i=1;i<=m;i++){
		if(qry[i].tp==3){
			printf("%d\n",qry[i].v);
		}
	}
	return 0;
}
