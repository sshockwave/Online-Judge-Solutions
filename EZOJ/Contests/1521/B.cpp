#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <utility>
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
const int N=500010;
namespace H{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		int hei;
		int val,dt;
		int fr,to;
		inline void addv(int v){
			if(this==null)return;
			val+=v,dt+=v;
		}
		inline void dn(){
			lson->addv(dt);
			rson->addv(dt);
			dt=0;
		}
	}pool[N],Null;
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->val>v->val){
			swap(u,v);
		}
		u->dn();
		u->rson=mg(u->rson,v);
		if(u->rson->hei>u->lson->hei){
			swap(u->lson,u->rson);
		}
		u->hei=u->rson->hei+1;
		return u;
	}
	void mg_inp(node &u,node v){
		u=mg(u,v);
	}
	inline node pop(node &x){
		node t=x;
		x->dn();
		x=mg(x->lson,x->rson);
		return t;
	}
}
inline H::node getnode(int u,int v,int c){
	H::node p=H::nn();
	p->hei=1;
	p->val=c;
	p->fr=u;
	p->to=v;
	return p;
}
H::node nd[N];
namespace ban{
	set<pair<int,int> >s;
	inline bool has(int u,int v){
		if(u>v){
			swap(u,v);
		}
		return s.find(make_pair(u,v))!=s.end();
	}
	inline void ins(int u,int v){
		if(u>v){
			swap(u,v);
		}
		s.insert(make_pair(u,v));
	}
}
int fa[N];
inline int grt(int x){
	return fa[x]!=x?fa[x]=grt(fa[x]):x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
#endif
	const int n=ni;
	H::init();
	for(int i=1;i<=n;i++){
		nd[i]=H::null;
	}
	for(int tot=ni;tot--;){
		const int u=ni,v=ni,c=ni;
		H::mg_inp(nd[u],getnode(v,u,c));
		H::mg_inp(nd[v],getnode(u,v,c));
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		int fr=0;
		for(;fr==0;){
			if(nd[i]==H::null){
				puts("No");
				return 0;
			}
			H::node v=H::pop(nd[i]);
			if(ban::has(v->fr,v->to))continue;
			fr=v->fr;
			ans+=v->val;
			ban::ins(v->fr,v->to);
			break;
		}
		fa[i]=grt(fr);
		H::mg_inp(nd[fa[i]],nd[i]);
		nd[i]=H::null;
	}
	printf("%lld\n",ans);
	return 0;
}
