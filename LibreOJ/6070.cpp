#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
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
const int N=100010,D=26,INF=0x7f7f7f7f;
namespace B{
	struct state{
		int tag,v;
		inline friend bool operator < (const state &a,const state &b){
			return a.tag<b.tag;
		}
	};
	vector<state>vec[N];
	int n,tim=0;
	inline void init(int _n){
		n=_n;
		for(int i=1;i<=n;i++){
			vec[i].push_back((state){0,0});
		}
	}
	inline void add(int x,int v){
		for(;x<=n;x+=x&-x){
			if(vec[x].back().tag<tim){
				vec[x].push_back(vec[x].back());
				vec[x].back().tag=tim;
			}
			vec[x].back().v+=v;
		}
	}
	inline int ask(int tim,int x){
		int a=0;
		for(;x;x^=x&-x){
			a+=(upper_bound(vec[x].begin(),vec[x].end(),(state){tim,0})-1)->v;
		}
		return a;
	}
}
namespace cacher{
	int lstl[N],lstr[N],ls=0;
	inline void add(int l,int r){
		apmax(l,1),apmax(r,l-1);
		if(l>r)return;
		if(ls&&l<=lstr[ls]+1){
			lstr[ls]=r;
		}else{
			++ls,lstl[ls]=l,lstr[ls]=r;
		}
	}
	inline void flush(){
		for(int i=1;i<=ls;i++){
			B::add(lstl[i],1);
			B::add(lstr[i]+1,-1);
		}
		ls=0;
	}
}
namespace T{
	struct Node;
	typedef Node* node;
	node null;
	void draw(node x);
	struct Node{
		union{
			node son[2];
			struct{node lson,rson;};
		};
		node fa,lnk;
		node go[D];
		int len,pos;
		bool istag;
		int mnlen,mxlen;
		inline void setpos(int x){
			if(this==null)return;
			pos=x,istag=true;
		}
		inline void dn(){
			if(istag){
				lson->setpos(pos);
				rson->setpos(pos);
				istag=false;
			}
		}
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void up(){
			mnlen=lson!=null?lson->mnlen:len;
			mxlen=rson!=null?rson->mxlen:len;
		}
		inline void rot(){
			bool d=!sd();
			int g=fa->sd();
			son[d]->fa=fa,fa->son[!d]=son[d],son[d]=fa;
			fa=fa->fa,son[d]->fa=this;
			if(~g)fa->son[g]=this;
			son[d]->up(),up();
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot():fd==!d?rot():void(),rot());
		}
	}pool[N],Null;
	void draw(node x){
		if(~x->sd())draw(x->fa);
		x->dn();
	}
	node nd0,nd1;
	void acc(node x,int newpos){
		node s=null;
		for(;x!=nd0&&x!=nd1;s=x,x=x->fa){
			x->spa();
			x->rson=null,x->up();
			cacher::add((x->pos-x->mxlen+1)+1,newpos-x->mnlen+1);
			x->rson=s,x->up();
		}
		s->setpos(newpos);
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lnk=null->lson=null->rson=null;
		for(int i=0;i<D;i++){
			null->go[i]=pool;
		}
		null->mnlen=INF,null->mxlen=-INF;
		nd0=nn(),nd1=nn();
		nd0->fa=nd0->lnk=nd1,nd0->up();
		nd1->len=-1,nd1->lnk=nd1,nd1->up();
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
#endif
	const int tp=ni;
	const int n=ni;
	int tot=ni;
	scanf("%s",s+1);
	T::init();
	B::init(n);
	T::node x=T::nd0;
	for(int i=1;i<=n;i++){
		for(;i-x->len-1<1||s[i]!=s[i-x->len-1];x=x->lnk);
		const int c=s[i]-'a';
		if(x->go[c]==T::nd0){
			T::node fa=x;
			for(;fa=fa->lnk,s[i]!=s[i-fa->len-1];);
			const T::node y=T::nn();
			y->len=x->len+2,y->fa=y->lnk=fa->go[c],y->up();
			x->go[c]=y;
		}
		x=x->go[c];
		B::tim=i;
		T::acc(x,i);
		cacher::flush();
	}
	for(int ans=0;tot--;){
		const int l=ni^(tp*ans),r=ni^(tp*ans);
		printf("%d\n",ans=B::ask(r,l));
	}
	return 0;
}
