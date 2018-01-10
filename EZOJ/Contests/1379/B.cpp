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
const int N=300010,D=26;
namespace T{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		//spa
		node fa,fail;
		node nxt[D];
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		//info
		int len,cnt;
		//subtree
		lint sum,lensum;
		//tags
		int dt;
		inline void* operator new(size_t,node x);
		inline void addcnt(int x){
			if(this==null)return;
			cnt+=x,sum+=lensum*x,dt+=x;
		}
		inline int sd(){
			assert(this!=null);
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void up(){
			assert(dt==0);
			lensum=lson->lensum+len+rson->lensum;
			sum=lson->sum+(lint)len*cnt+rson->sum;
		}
		inline void down(){
			if(dt){
				lson->addcnt(dt);
				rson->addcnt(dt);
				assert(lson->sum+(lint)len*cnt+rson->sum==sum);
				dt=0;
			}
		}
		inline void rot(){//tocheck
			assert(this!=null);
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
		inline void spa();
	}pool[N<<1],Null;
	void draw(node x){
		if(x!=null){
			draw(x->fa),x->down();
		}
	}
	inline void Node::spa(){
		draw(this);
		for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot(),rot():fd==!d?rot(),rot():rot());
	}
	inline void* Node::operator new(size_t,node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline node acc(node x){
		node s=null;
		for(;x!=null;s=x,x=x->fa){
			x->spa();
			x->rson=s;
			x->up();
		}
		assert(s->fa==null);
		return s;
	}
	node lastnode;//remember to splay this!
	inline node _low(node x,int len){//find last <=len
		if(x==null)return x;
		lastnode=x;
		if(x->len<=len){
			node y=_low(x->rson,len);
			return y!=null?y:x;
		}else return _low(x->lson,len);
	}
	inline node low(node x,int len){
		lastnode=null;
		x=_low(x,len);
		if(lastnode!=null){
			lastnode->spa();
		}
		return x;
	}
	node len0,len1;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
		null->fail=null;
		for(int i=0;i<D;i++){
			null->nxt[i]=null;
		}
		len1=new Node;
		len1->len=-1;
		len1->up();
		len1->fail=len1;
		len0=new Node;
		len0->fa=len0->fail=len1;
		null->fail=len0;
	}
	inline lint gans(node u,node v){
		if(u==null||v==null)return 0;
		node w=acc(u);
		lint ans=w->sum;
		w=acc(v);//lca
		ans+=w->sum;
		acc(w);
		w->spa();
		ans-=w->sum*2;
		ans+=(lint)w->len*w->cnt;
		return ans;
	}
}
struct Q{
	int op,l1,r1,l2,r2,c;
}q[N];
int tmp[N];
int pool[N<<1],ps=0;
T::node bef[N<<1],aft[N<<1];
//TODO::check array size
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=0;i<n;i++){
		tmp[i]=ni;
	}
	for(int i=1;i<=tot;i++){
		static char s[10];
		scanf("%s",s);
		if(s[0]=='a'){
			q[i].op=s[3]=='r';
			q[i].c=ni;
		}else{
			q[i]=(Q){2|(s[5]=='r'),ni,ni,ni,ni};
		}
	}
	for(int i=tot;i>=1;i--){
		if(q[i].op==0){
			pool[ps++]=q[i].c;
		}
	}
	int* str=pool+ps-1;
	memcpy(pool+ps,tmp,n<<2);
	ps+=n;
	for(int i=1;i<=tot;i++){
		if(q[i].op==1){
			pool[ps++]=q[i].c;
		}
	}
	T::init();
	{
		T::node x=T::len1;
		for(int i=0;i<ps;i++){
			for(;i-x->len-1<0||pool[i]!=pool[i-x->len-1];x=x->fail);
			T::node &y=x->nxt[pool[i]];
			if(y==T::null){
				y=new T::Node;
				T::node p=x->fail;
				for(;pool[i]!=pool[i-p->len-1];p=p->fail);
				y->fa=y->fail=p->nxt[pool[i]];
				if(y->fa==y){
					y->fa=y->fail=T::len0;
				}
				assert(y->len>=0);
				y->len=x->len+2;
				y->up();
			}
			x=bef[i]=y;
			assert(x!=T::null);
		}
		x=T::len1;
		for(int i=ps-1;i>=0;i--){
			for(;i+x->len+1>=ps||pool[i]!=pool[i+x->len+1];x=x->fail);
			x=aft[i]=x->nxt[pool[i]];
			assert(x!=T::null);
		}
	}
	for(int i=1;i<=n;i++){
		T::acc(T::low(T::acc(bef[str+i-pool]),i))->addcnt(1);
	}
	for(int tt=1;tt<=tot;tt++){
		if(q[tt].op<2){
			n++;
			if(q[tt].op==0){
				str--;
				T::acc(T::low(T::acc(aft[str+1-pool]),n))->addcnt(1);
			}else{
				T::acc(T::low(T::acc(bef[str+n-pool]),n))->addcnt(1);
			}
		}else{
			int l1=q[tt].l1,r1=q[tt].r1,l2=q[tt].l2,r2=q[tt].r2;
			int len1=r1-l1+1,len2=r2-l2+1;
			T::node u,v;
			if(q[tt].op==2){//del left
				u=T::low(T::acc(bef[str+r1-pool]),len1);
				v=T::low(T::acc(bef[str+r2-pool]),len2);
			}else{
				u=T::low(T::acc(aft[str+l1-pool]),len1);
				v=T::low(T::acc(aft[str+l2-pool]),len2);
			}
			printf("%lld\n",T::gans(u,v));
		}
	}
	return 0;
}
