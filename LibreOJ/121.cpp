#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=5010,Q=500010,INF=0x7f7f7f7f;
namespace T{
	const int N=::N+::Q;
	struct Node;
	typedef Node* node;
	node null;
	void draw(node);
	struct Node{
		//splay
		node fa;
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		bool rev;
		//info
		int val;
		//subtree
		node mn;
		inline int side(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void putrev(){
			if(this!=null){
				swap(lson,rson),rev^=1;
			}
		}
		inline void down(){
			if(rev){
				lson->putrev(),rson->putrev(),rev=false;
			}
		}
		inline void up(){
			assert(!rev);
			mn=this;
			if(lson->mn->val<mn->val){
				mn=lson->mn;
			}
			if(rson->mn->val<mn->val){
				mn=rson->mn;
			}
		}
		inline void rot(){
			assert(~side());
			bool d=!side();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->side();
			if(~g){
				fa->fa->son[g]=this;
			}
			fa=fa->fa,son[d]->fa=this;
			son[d]->up(),up();
		}
		inline void splay(){
			draw(this);
			for(int d,fd;d=side(),~d;fd=fa->side(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}Null,pool[N];
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void init(){
		null=&Null;
		null->fa=null->lson=null->rson=null;
		null->mn=null;
		null->val=INF;
	}
	void draw(node x){
		if(x!=null){
			draw(x->fa),x->down();
		}
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->splay();
			x->rson=s;
			x->up();
		}
	}
	inline void chr(node x){
		acc(x),x->splay(),x->putrev();
	}
	inline void lnk(node u,node v){
		chr(v),v->fa=u;
	}
}
struct Edge{
	int u,v;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.u!=b.u?a.u<b.u:a.v<b.v;
	}
}e[Q];
map<Edge,int>m;
int op[Q];
T::node node[N],enode[Q];
bool del[Q];
int main(){
#ifndef ONLINE_JUDGE
	freopen("connect.in","r",stdin);
	freopen("connect.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	for(int i=1;i<=n;i++){
		node[i]=T::nn();
		node[i]->up();
	}
	for(int i=1;i<=tot;i++){
		op[i]=ni;
		e[i]=(Edge){ni,ni};
		if(e[i].u>e[i].v){
			swap(e[i].u,e[i].v);
		}
		if(op[i]==0){
			m[e[i]]=i;
			enode[i]=T::nn();
		}else if(op[i]==1){
			enode[i]=enode[m[e[i]]];
			enode[i]->val=i;
			enode[i]->up();
		}
	}
	memset(del,0,sizeof(del));
	for(int i=1;i<=tot;i++){
		using namespace T;
		T::node u=::node[e[i].u],v=::node[e[i].v];
		if(op[i]==0){
			chr(u),acc(v),v->splay();
			if(u->fa==null){
				lnk(u,enode[i]);
				lnk(v,enode[i]);
			}else if(v->mn->val<enode[i]->val){
				T::node x=v->mn;
				x->splay();
				x->lson->fa=x->rson->fa=null;
				del[x->val]=true;
				lnk(u,enode[i]);
				lnk(v,enode[i]);
			}else if(enode[i]->val<INF){
				del[enode[i]->val]=true;
			}
		}else if(op[i]==1){
			if(del[i])continue;
			chr(u),acc(v);
			enode[i]->splay();
			assert(u->fa==enode[i]&&v->fa==enode[i]);
			u->fa=v->fa=null;
		}else{
			chr(u),acc(v),v->splay();
			putchar(u==v||u->fa!=null?'Y':'N');
			putchar('\n');
		}
	}
	return 0;
}
