#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=200010,D=26,INF=0x7f7f7f7f;
namespace sam{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	node null,st,tail;
	void draw(node);
	struct Node{
		/* SAM */
		node lnk,go[26];
		int /* const */len;
		int pos,/* const */lev;
		bool istag;
		int mnlen,mxlef;
		inline void putpos(int x){
			if(this==null)return;
			pos=x,istag=true,mxlef=pos-mnlen+1;
		}
		/* LCT */
		node fa;
		union{
			struct{node lson,rson;};
			node son[2];
		};
		inline void dn(){
			if(istag){
				lson->putpos(pos);
				rson->putpos(pos);
				istag=false;
			}
		}
		inline void up(){//up: mnlen, mxlef
			assert(!istag);
			mnlen=min(len,min(lson->len,rson->len));
			mxlef=max(pos-len+1,max(lson->mxlef,rson->mxlef));
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
			if(~g){
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
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			x->rson=s;
			x->up();
		}
	}
	inline void work(node x){
		acc(x),x->spa();
		x->dn();
		node y=x->lson;
		int lend=x->pos-x->len+1;
		assert(y->mxlef>=lend);
		while(true){
			assert(y!=null);
			y->dn();
			assert(y->mxlef>=lend);
			if(y->rson->mxlef>=lend){
				y=y->rson;
			}else if(y->pos-y->len+1<lend){
				y=y->lson;
			}else break;
		}
		y->spa();
		assert(y->pos-y->len+1>=lend);
		assert(y->pos<x->pos);
		apmax(x->lev,y->lev+1);
	}
	inline void ext(int c,int pos){
		node p=tail,np=tail=nn();
		np->len=p->len+1,np->pos=pos,np->lev=p->lev;
		np->up();
		for(;p!=null&&p->go[c]==null;p=p->lnk){
			p->go[c]=np;
			if(p->lnk!=null){
				assert(p->lnk->len<p->len);
			}
		}
		if(p==null){
			np->lnk=np->fa=st,work(np);
			acc(np),np->spa(),np->putpos(pos);
			return;
		}
		node q=p->go[c];
		if(q->len==p->len+1){
			np->lnk=np->fa=q;
			assert(pos-np->len+1==1);
			work(np);
			acc(np),np->spa(),np->putpos(pos);
			return;
		}
		acc(q),q->spa();
		node nq=nn(q);
		nq->len=p->len+1,assert(nq->pos==q->pos),nq->lev=p->lev;
		if(q->lson!=null){
			q->lson->fa=nq;
		}
		q->lson=null,assert(q->rson==null),q->up();
		/* nq lson ready */nq->rson=q;
		q->fa=q->lnk=nq,q->up(),nq->up();
		nq->spa(),nq->pos=pos,nq->up(),work(nq);
		nq->spa(),nq->pos=q->pos,nq->up(),np->lnk=np->fa=nq,work(np);
		nq->spa(),nq->pos=pos,nq->up();
		acc(np),np->spa(),np->putpos(pos);
		for(;p!=null&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
	}
	void draw(node x){
		if(x->sd()!=-1){
			draw(x->fa);
		}
		x->dn();
	}
	inline void init(){
		//Init null
		memset(null=&Null,0,sizeof(Null));
		null->lnk=null;
		for(int i=0;i<D;i++){
			null->go[i]=null;
		}
		null->len=INF,null->pos=-1,null->lev=-1;
		null->mnlen=INF,null->mxlef=-1;
		null->fa=null->lson=null->rson=null;
		//Init st
		tail=st=nn();
		st->len=0,st->pos=0,st->lev=0;
		st->up();
	}
}
char s[N];
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("level.in","r",stdin);
	freopen("level.out","w",stdout);
#endif
	scanf("%s",s+1);
	int n=strlen(s+1);
	sam::init();
	for(int i=1;i<=n;i++){
		sam::ext(s[i]-'a',i);
	}
	printf("%d\n",sam::tail->lev);
	return 0;
}
