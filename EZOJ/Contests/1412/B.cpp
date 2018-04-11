#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=200010,INF=0x7f7f7f7f;
namespace lct{
	struct Info{
		int f[2][2];
		inline friend Info operator + (const Info &a,const Info &b){
			Info c;
			c.f[0][0]=max(max((lint)a.f[0][1]+b.f[1][0],(lint)a.f[0][0]+b.f[0][0]+1),-(lint)INF);
			c.f[0][1]=max(max((lint)a.f[0][1]+b.f[1][1],(lint)a.f[0][0]+b.f[0][1]+1),-(lint)INF);
			c.f[1][0]=max(max((lint)a.f[1][1]+b.f[1][0],(lint)a.f[1][0]+b.f[0][0]+1),-(lint)INF);
			c.f[1][1]=max(max((lint)a.f[1][1]+b.f[1][1],(lint)a.f[1][0]+b.f[0][1]+1),-(lint)INF);
			return c;
		}
	};
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
		bool rev;
		Info val,sum;
		int tcnt;
		node unifa;
		int unisize,unival;
		inline void addv(Info v){
			assert(this!=null);
			val.f[0][1]+=v.f[1][1];
			val.f[1][0]+=v.f[1][1];
			val.f[1][1]+=v.f[1][1];
			bool flag=v.f[0][1]==v.f[1][1];
			val.f[1][1]+=tcnt==0&&flag;
			tcnt+=flag;
		}
		inline void delv(Info v){
			assert(this!=null);
			bool flag=v.f[0][1]==v.f[1][1];
			tcnt-=flag;
			val.f[1][1]-=tcnt==0&&flag;
			val.f[1][1]-=v.f[1][1];
			val.f[1][0]-=v.f[1][1];
			val.f[0][1]-=v.f[1][1];
		}
		inline void putrev(){
			if(this==null)return;
			rev^=1;
			swap(lson,rson);
			swap(val.f[0][1],val.f[1][0]);
			swap(sum.f[0][1],sum.f[1][0]);
		}
		inline void up(){
			assert(!rev);
			sum=val;
			if(lson!=null){
				sum=lson->sum+sum;
			}
			if(rson!=null){
				sum=sum+rson->sum;
			}
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
		inline int sd(){return fa->lson==this?0:fa->rson==this?1:-1;}
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
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		null->val=null->sum=(Info){-INF,-INF,-INF,0};
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n->unifa=n,n->unisize=1,n->unival=1,n->val=(Info){-INF,0,0,0},n->up(),n++;
	}
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
	}
	node grt(node x){
		return x->unifa!=x?x->unifa=grt(x->unifa):x;
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			x->addv(x->rson->sum);
			x->delv(s->sum);
			x->rson=s;
			x->up();
		}
	}
	inline void chr(node x){
		acc(x),x->spa(),x->putrev();
	}
}
lct::node nd[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
#endif
	int n=ni;
	lct::init();
	for(int i=1;i<=n;i++){
		nd[i]=lct::nn();
	}
	for(int tot=ni;tot--;){
		if(ni){
			lct::node u=nd[ni],v=nd[ni];
			lct::chr(u),lct::acc(v),v->spa();
			u->fa=v,v->rson=u,v->up();
			lct::grt(u),lct::grt(v);
			v->unifa->unisize+=u->unifa->unisize;
			u->unifa->unifa=v->unifa;
			v->unifa->unival=v->unifa->unisize-v->sum.f[1][1];
		}else{
			printf("%d\n",lct::grt(nd[ni])->unival);
		}
	}
	return 0;
}
