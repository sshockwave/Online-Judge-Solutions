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
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=3010,N2=N*N,INF=0x7f7f7f7f,Q=100010;
namespace lct{
	const int N=(::N<<1)+(Q<<1);
	struct Node;
	typedef Node* node;
	node null;
	void draw(node);
	struct Node{
		node fa;
		union{
			struct{node lson,rson;};
			node son[2];
		};
		int val,mn;
		bool rev;
		int u,v;//if is edge
		inline void putrev(){
			if(this!=null){
				swap(lson,rson);
				rev=!rev;
			}
		}
		inline void up(){
			mn=min(val,min(lson->mn,rson->mn));
		}
		inline void dn(){
			if(rev){
				rev=false;
				lson->putrev();
				rson->putrev();
			}
		}
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void rot(){
			bool d=!sd();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->sd();
			fa=fa->fa,son[d]->fa=this;
			if(~g){
				fa->son[g]=this;
			}
			son[d]->up(),up();
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}Null,pool[N];
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null->fa=null;
		null->val=null->mn=INF;
	}
	inline node nn(node x=null){
		static node n=pool;
		assert(n<pool+N);
		return *n=*x,n++;
	}
	void draw(node x){
		if(x!=null){
			draw(x->fa),x->dn();
		}
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			x->rson=s;
			x->up();
		}
	}
	inline void chr(node x){
		acc(x),x->spa(),x->putrev();
	}
}
int n,m,ecnt=0;
lct::node edg[N][N];
namespace unifind{
	int fa[N<<1];
	lct::node pt[N<<1];
	inline void init(int n){
		for(int i=1;i<=n;i++){
			fa[i]=i;
		}
	}
	int root(int x){
		return fa[x]!=x?fa[x]=root(fa[x]):x;
	}
	inline void mg(int u,int v){
		fa[root(v)]=root(u);
	}
	inline lct::node& gpt(int x){
		return pt[root(x)];
	}
}
using unifind::gpt;
inline void tcut(int u,int v){
	using namespace lct;
	node x=gpt(u),y=gpt(v+n),&e=edg[u][v];
	if(x==y||e==0)return;
	chr(x),acc(y),e->spa();
	x->fa=y->fa=null,e=0,ecnt++;
}
inline void rlnk(int u,int v,int w){
	using namespace lct;
	node x=gpt(u),y=gpt(v+n),&e=edg[u][v]=nn();
	if(x==y)return;
	e->u=u,e->v=v,e->val=w,e->mn=w;
	chr(x),x->spa(),x->fa=e;
	chr(y),y->spa(),y->fa=e;
	ecnt--;
}
inline void tlnk(int u,int v,int w){
	using namespace lct;
	node x=gpt(u),y=gpt(v+n);
	if(x==y)return;
	chr(x),acc(y),y->spa();
	if(x->sd()==-1)return rlnk(u,v,w);
	if(w<=y->mn)return;
	node t=y;
	for(;t->val!=t->mn;t->lson->mn==t->mn?(t=t->lson):(t=t->rson));
	t->spa();
	tcut(t->u,t->v);
	rlnk(u,v,w);
}
char s[N][N];
int tag[N][N];
struct Query{
	int x,y,val;
}qry[Q];
int main(){
#ifndef ONLINE_JUDGE
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
#endif
	n=ni,m=ni;
	int q=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	memset(tag,127,sizeof(tag));
	for(int i=1;i<=q;i++){
		qry[i]=(Query){ni,ni};
		s[qry[i].x][qry[i].y]^='x'^'.';
	}
	for(int i=q;i>=1;i--){
		int x=qry[i].x,y=qry[i].y;
		if(s[x][y]=='x'){//add
			qry[i].val=tag[x][y];
		}else{//del
			tag[x][y]=i;
		}
		s[x][y]^='x'^'.';
	}
	unifind::init(n+m);
	lct::init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='x'&&tag[i][j]==INF){
				unifind::mg(i,j+n);
			}
		}
	}
	for(int i=1;i<=n+m;i++){
		if(unifind::fa[i]==i){
			unifind::pt[i]=lct::nn();
			ecnt++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='x'&&tag[i][j]<INF){
				tlnk(i,j,tag[i][j]);
			}
		}
	}
	for(int i=1;puts(ecnt==1?"S":"U"),i<=q;i++){
		int x=qry[i].x,y=qry[i].y;
		if(s[x][y]=='.'){//add
			tlnk(x,y,qry[i].val);
		}else{//del
			tcut(x,y);
		}
		s[x][y]^='x'^'.';
	}
	return 0;
}
