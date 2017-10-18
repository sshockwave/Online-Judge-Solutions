#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <set>
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
int n,ans[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		bool full;
	};
	inline node nn(){
		static node n=(node)memset(new Node[N*50],0,sizeof(Node)*N*50);
		return n++;
	}
	node ins(int p,int l=1,int r=n){
		node x=nn();
		if(l==r){
			x->full=true;
			return x;
		}
		int m=(l+r)>>1;
		if(p<=m){
			x->lson=ins(p,l,m);
		}else{
			x->rson=ins(p,m+1,r);
		}
		return x;
	}
	node merge(node x,node y){
		if(!(x&&y)){
			return x?x:y;
		}
		if(x->full||y->full){
			return x->full?x:y;
		}
		node n=nn();
		n->lson=merge(x->lson,y->lson);
		n->rson=merge(x->rson,y->rson);
		n->full=n->lson&&n->rson&&n->lson->full&&n->rson->full;
		return n;
	}
	int gmore(node x,int v,int l=1,int r=n){
		if(x==0){
			return INF;
		}
		if(x->full){
			return max(l,v);
		}
		int m=(l+r)>>1,tmp=INF;
		if(v<=m){
			tmp=gmore(x->lson,v,l,m);
		}
		return tmp<INF?tmp:gmore(x->rson,v,m+1,r);
	}
	int gless(node x,int v,int l=1,int r=n){
		if(x==0){
			return 0;
		}
		if(x->full){
			return min(v,r);
		}
		int m=(l+r)>>1,tmp=0;
		if(v>m){
			tmp=gless(x->rson,v,m+1,r);
		}
		return tmp?tmp:gless(x->lson,v,l,m);
	}
}
multiset<int>sub;
vector<int>stk;
inline int gans(vector<int>&vec,int mn,int mx,int dt){
	if(vec.empty()){
		return INF;
	}
	int m1=(mx-mn)>>1,m2=m1+((mx-mn)&1);
	int l=0,r=vec.size()-1;
	while(l<r){
		int m=((l+r)>>1)+1;
		if(vec[m]-dt<m2){
			r=m-1;
		}else{
			l=m;
		}
	}
	return min(max(mn+(vec[l]-dt),mx-(vec[l]-dt)),l<(int)vec.size()?max(mn+(vec[l+1]-dt),mx-(vec[l+1]-dt)):INF);
}
inline int gans(multiset<int>&s,int mn,int mx){
	int m1=(mx-mn)>>1,m2=m1+((mx-mn)&1);
	assert(max(mn+m1,mx-m1)==max(mn+m2,mx-m2));
	multiset<int>::iterator it=s.lower_bound(m2);
	int val=it==s.end()?INF:max(mn+*it,mx-*it),tmp;
	if(it!=s.begin()&&(--it,(tmp=max(mn+*it,mx-*it))<val)){
		val=tmp;
	}
	return val;
}
inline int gans(seg::node rt,int mn,int mx){
	int m1=(mx-mn)>>1,m2=m1+((mx-mn)&1);
	lint v1=seg::gless(rt,m1),v2=seg::gmore(rt,m2);
	return min(max(mn+v1,mx-v1),max(mn+v2,mx-v2));
}
int rt;
namespace G{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	seg::node srt[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int size[N];
	void gsize(int x,int fa){
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				gsize(v,x);
				size[x]+=size[v];
			}
		}
	}
	seg::node currt=0;
	void dfs(int x){
		int son=rt,mx=size[rt]-size[x],mx2=0,mn=mx?mx:INF;
		seg::node tmprt=currt,sing=srt[x]=seg::ins(size[x]);
		sub.erase(sub.find(size[x])),stk.push_back(size[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			if(size[v=to[i]]<size[x]){
				dfs(v);
				srt[x]=seg::merge(srt[x],srt[v]);
				if(size[v]>mx){
					mx2=mx,son=v,mx=size[v];
				}else if(size[v]>mx2){
					mx2=size[v];
				}
				if(size[v]<mn){
					mn=size[v];
				}
			}
		}
		stk.pop_back();
		if(son==rt){
			ans[x]=min(gans(tmprt,mn,mx),min(gans(stk,mn,mx,size[x]),gans(sub,mn,mx)));
		}else{
			ans[x]=gans(srt[son],mn,mx);
		}
		apmax(ans[x],mx2);
		currt=seg::merge(currt,sing);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("wind.in","r",stdin);
	freopen("wind.out","w",stdout);
#endif
	n=ni;
	G::init();
	for(int i=1;i<=n;i++){
		int u=ni,v=ni;
		if(u&&v){
			G::add(u,v);
		}else{
			rt=u|v;
		}
	}
	G::gsize(rt,0);
	for(int i=1;i<=n;i++){
		sub.insert(G::size[i]);
	}
	G::dfs(rt);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
