#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
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
const int N=100010,E=200010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace lct{
	const int N=::N+::E;
	struct Node;
	typedef Node* node;
	node null;
	void draw(node);
	struct Node{
		//Variables
		node fa;
		union{
			struct{node lson,rson;};
			node son[2];
		};
		node lpt,rpt;
		node ldg,rdg;
		bool rev;
		vi _prod,_invprod;
		map<node,int>idx;
		int mxsize;
		int val;
		//Functions
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void putrev(){
			if(this==null)return;
			rev^=1,swap(lson,rson);
		}
		inline int qry(node _u,node _v){
			assert(_u!=_v);
			assert(idx.find(_u)!=idx.end());
			assert(idx.find(_v)!=idx.end());
			int u=idx[_u],v=idx[_v];
			if(u>v)swap(u,v);
			const static int inv2=inv(2);
			int ans=(lint)_prod[_prod.size()-1]*_invprod[v]%O*_prod[u];
			ans=(ans+(lint)_prod[v]*_invprod[u])%O;
			return (lint)ans*inv2%O;
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
		inline void up(){
			bool ispt=_prod.empty(),isdg=!ispt;
			lpt=lson->lpt!=null?lson->lpt:ispt?this:rson->lpt;
			rpt=rson->rpt!=null?rson->rpt:ispt?this:lson->rpt;
			ldg=lson->ldg!=null?lson->ldg:isdg?this:rson->ldg;
			rdg=rson->rdg!=null?rson->rdg:isdg?this:lson->rdg;
			assert(!rev);
			mxsize=max((int)(idx.size()),max(lson->mxsize,rson->mxsize));
			val=(lint)lson->val*rson->val%O;
			if(ispt){
				if(lson->rpt!=null&&lson->rdg!=null){
					val=(lint)val*lson->rdg->qry(lson->rpt,this)%O;
				}
				if(rson->lpt!=null&&rson->ldg!=null){
					val=(lint)val*rson->ldg->qry(rson->lpt,this)%O;
				}
			}else if(lson->rpt!=null&&rson->lpt!=null){
				val=(lint)val*qry(lson->rpt,rson->lpt)%O;
			}
		}
		inline void rot(){
			assert(sd()!=-1);
			bool d=!sd();
			if(son[d]!=null){
				son[d]->fa=fa;
			}
			fa->son[!d]=son[d],son[d]=fa;
			int g=fa->sd();
			fa=fa->fa,son[d]->fa=this;
			if(g!=-1){
				fa->son[g]=this;
			}
			son[d]->up(),up();
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
		}
	}pool[N],Null;
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void init(){
		null=&Null;
		null->fa=null->lson=null->rson=null;
		null->lpt=null->rpt=null;
		null->ldg=null->rdg=null;
		null->rev=false;
		null->mxsize=0,null->val=1;
	}
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
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
	void putall(node x,vi &prod,map<node,int>&idx,node nfa){
		if(x==null)return;
		x->dn();
		putall(x->lson,prod,idx,nfa);
		bool ispt=x->_prod.empty();
		if(ispt){
			idx[x]=prod.size()-1;//cout
		}else{
			assert(x->_prod.size()==2);
			prod.push_back(x->_prod[0]);
		}
		putall(x->rson,prod,idx,nfa);
		if(ispt){
			x->fa=nfa;
			x->lson=x->rson=null;
			x->up();
		}
	}
}
inline void getprod(vi &prod,vi &invprod){
	invprod.reserve(prod.size());
	lint pw=1;
	for(vi::iterator it=prod.begin(),ti=prod.end();it!=ti;it++){
		pw=pw**it%O,*it=pw,invprod.push_back(inv(pw));
	}
}
lct::node nd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
#endif
	int n=ni,tot=ni,tp=ni;
	lct::init();
	for(int i=1;i<=n;i++){
		nd[i]=lct::nn();
	}
	for(int ans=0;tot--;){
		int op=ni;
		lct::node u,v;
		{
			int x=ni,y=ni;
			if(tp){
				x=(x+ans)%n+1,y=(y+ans)%n+1;
			}
			u=nd[x],v=nd[y];
		}
		if(op==1){//add edge
			int w=ni;
			assert(u!=v);
			lct::chr(u),lct::acc(v),v->spa();
			bool flag;
			if(u->sd()==-1){//create new edge
				flag=true;
				lct::node e=lct::nn();
				e->idx[u]=0,e->idx[v]=1;
				e->_prod.push_back(w);
				e->_prod.push_back(w);
				getprod(e->_prod,e->_invprod);
				u->fa=e,e->fa=v;
			}else if(v->mxsize==2){//create new ring
				flag=true;
				lct::node e=lct::nn();
				e->_prod.push_back(w);
				lct::putall(v,e->_prod,e->idx,e);
				assert(e->_prod.size()==e->idx.size());
				getprod(e->_prod,e->_invprod);
			}else{
				flag=false;
				assert(v->mxsize>2);
			}
			putchar('0'+flag),putchar('\n');
		}else{//query
			lct::chr(u),lct::acc(v),v->spa();
			ans=u->sd()==-1?0:v->val;
			printf("%d\n",ans);
		}
	}
	return 0;
}
