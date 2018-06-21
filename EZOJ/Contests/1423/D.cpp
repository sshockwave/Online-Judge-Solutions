#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=100010,INF=0x7f7f7f7f;
int nblock,mblock;
namespace blockchain{
	const double ratio=2.6;
	const int N=2010,Nl=N*ratio,Nc=N/ratio;
	struct Block;
	typedef Block* node;
	struct Block{
		int l,r;
		int val[Nl],sum[Nl];
		node pre,nxt;
		int mn,mx;
		bool online;
		inline void build(){
			int n=r-l+1;
			mn=INF,mx=-INF;
			for(int i=0;i<n;i++){
				apmin(mn,val[i]);
				apmax(mx,val[i]);
			}
			memset(sum,0,(mx-mn+1)*sizeof(sum[0]));
			for(int i=0;i<n;i++){
				++sum[val[i]-=mn];
			}
			for(int i=1,ti=mx-mn;i<=ti;i++){
				sum[i]+=sum[i-1];
			}
		}
		inline void add(const int _l,const int _r,int v){
			if(l==_l&&r==_r)return mn+=v,mx+=v,void();
			for(int i=0,t=r-l;i<=t;i++){
				val[i]+=mn;
				if(_l-l<=i&&i<=_r-l){
					val[i]+=v;
				}
			}
			build();
		}
		inline int ask(int _l,int _r,int v)const{
			if(l==_l&&r==_r)return v<mn?0:v<=mx?sum[v-mn]:sum[mx-mn];
			v-=mn;
			int cnt=0;
			for(int i=_l-l,t=_r-l;i<=t;i++){
				cnt+=val[i]<=v;
			}
			return cnt;
		}
		inline void ask_lim(int _l,int _r,int &_mn,int &_mx)const{
			if(l==_l&&r==_r){
				apmin(_mn,mn);
				apmax(_mx,mx);
			}else for(int i=_l-l,ti=_r-l;i<=ti;i++){
				apmin(_mn,val[i]+mn);
				apmax(_mx,val[i]+mn);
			}
		}
	}pool[Nc],head,tail;
	node pt[Nc],*pol=pt;
	inline node nn(){
		return (*pol)->online=true,*(pol++);
	}
	inline void del(node x){
		*--pol=x;
		x->online=false;
		x->nxt->pre=x->pre,x->pre->nxt=x->nxt;
	}
	inline void ins_aft(node u,node v){
		v->nxt=u->nxt,v->nxt->pre=v,u->nxt=v,v->pre=u;
	}
	struct bcmp{
		inline bool operator () (node a,node b){
			return a->r<b->r;
		}
	};
	inline void init(int a[],int n){
		for(int i=0;i<Nc;i++){
			pt[i]=pool+i;
		}
		head.r=0;
		head.nxt=&tail,tail.pre=&head;
		node pre=&head,cur=nn();
		cur->mn=INF,cur->mx=-INF;
		cur->l=1,cur->r=0;
		for(int i=1;i<=n;i++){
			if(i-cur->l+1>nblock*2||max(a[i],cur->mx)-min(a[i],cur->mn)>mblock){
				cur->build();
				ins_aft(pre,cur),pre=cur,cur=nn();
				cur->l=i,cur->r=i-1;
				cur->mn=INF,cur->mx=-INF;
			}
			cur->val[(++cur->r)-cur->l]=a[i];
			apmin(cur->mn,a[i]);
			apmax(cur->mx,a[i]);
		}
		cur->build();
		ins_aft(pre,cur);
	}
	node fir,las,ed;
	inline void giter(int l,int r,int &mn,int &mx){
		for(node &i=fir=&head;i->r<l;i=i->nxt);
		for(node &i=las=fir;i->r<r;i=i->nxt){
			i->ask_lim(max(i->l,l),min(i->r,r),mn,mx);
		}
		las->ask_lim(max(las->l,l),min(las->r,r),mn,mx);
		ed=las->nxt;
	}
	inline int ask(int l,int r,int v){//ask leq
		int cnt=0;
		for(node x=fir;x!=ed;x=x->nxt){
			cnt+=x->ask(max(x->l,l),min(x->r,r),v);
		}
		return cnt;
	}
	inline node join(node u,node v){
		assert(u->nxt==v);
		for(int i=0,t=u->r-u->l;i<=t;i++){
			u->val[i]+=u->mn;
		}
		for(int i=0,t=v->r-v->l;i<=t;i++){
			v->val[i]+=v->mn;
		}
		memcpy(u->val+v->l-u->l,v->val,(v->r-v->l+1)*sizeof(u->val[0]));
		u->r=v->r,u->build();
		del(v);
		return u;
	}
	void mt(node x){
		if(!x->online)return;
		assert(x->online);
		if(x->mx-x->mn>=mblock*2){
			static int premn[Nl],premx[Nl],sufmn[Nl],sufmx[Nl];
			int* const a=x->val;
			int t=x->r-x->l;
			for(int i=0;i<=t;i++){
				premn[i]=premx[i]=a[i]+=x->mn;
				if(i){
					apmin(premn[i],premn[i-1]);
					apmax(premx[i],premx[i-1]);
				}
			}
			for(int i=t;i>=0;i--){
				sufmn[i]=sufmx[i]=a[i];
				if(i<t){
					apmin(sufmn[i],sufmn[i+1]);
					apmax(sufmx[i],sufmx[i+1]);
				}
			}
			int sp=1;
			for(int &i=sp;max(premx[i-1]-premn[i-1],sufmx[i]-sufmn[i])>=mblock*2;i++);
			node y=nn();
			y->l=x->l+sp,y->r=x->r,x->r=y->l-1;
			memcpy(y->val,x->val+sp,(y->r-y->l+1)*sizeof(y->val[0])),y->build();
			x->build();
			ins_aft(x,y);
			return mt(x),mt(y);
		}
		if(x->pre!=&head){
			node y=x->pre;
			if(x->r-y->l+1<nblock*2&&max(x->mx,y->mx)-min(x->mn,y->mn)<mblock*2){
				return mt(join(y,x));
			}
		}
		if(x->nxt!=&tail){
			node y=x->nxt;
			if(y->r-x->l+1<nblock*2&&max(x->mx,y->mx)-min(x->mn,y->mn)<mblock*2){
				return mt(join(x,y));
			}
		}
	}
	inline void add(int l,int r,int v){
		if(fir->l<l&&r<fir->r){
			node x=fir;
			x->add(max(x->l,l),min(x->r,r),v);
			if(x->mx-x->mn>=mblock*2){//split into three
				for(int i=0,t=x->r-x->l;i<=t;i++){
					x->val[i]+=x->mn;
				}
				node lx=nn(),rx=nn();
				lx->l=x->l,lx->r=l-1;
				memcpy(lx->val,x->val,(lx->r-lx->l+1)*sizeof(lx->val[0]));
				rx->l=r+1,rx->r=x->r;
				memcpy(rx->val,x->val+r+1-x->l,(rx->r-rx->l+1)*sizeof(rx->val[0]));
				x->l=l,x->r=r;
				for(int i=0,j=l-lx->l,t=r-l;i<=t;i++,j++){
					x->val[i]=x->val[j];
				}
				x->build();
				lx->build(),ins_aft(x->pre,lx);
				rx->build(),ins_aft(x,rx);
			}
			return;
		}
		for(node x=fir;x!=ed;x=x->nxt){
			x->add(max(x->l,l),min(x->r,r),v);
		}
		if(fir->l<l||r<fir->r){
			mt(fir);
		}
		if(las->l<l||r<las->r){
			mt(las);
		}
	}
}
namespace T{
	const int E=::N;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	int dfn[N],dfe[N],tim=0;
	int dep[N];
	void dfs(int x){
		dfn[x]=++tim;
		for(int i=head[x],v;~i;i=bro[i]){
			dep[v=to[i]]=dep[x]+val[i];
			dfs(v);
		}
		dfe[x]=tim;
	}
}
inline int ask(int lend,int rend,int k){
	int l=INF,r=-INF;
	blockchain::giter(lend,rend,l,r);
	while(l<r){
		int m=(l+r)>>1;
		if(blockchain::ask(lend,rend,m)<k){
			l=m+1;
		}else{
			r=m;
		}
	}
	return l;
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
#endif
	int n=ni,m=ni,len=ni;
	nblock=sqrt(n)*blockchain::ratio,mblock=sqrt(m*len)*blockchain::ratio;
	T::init();
	for(int i=2;i<=n;i++){
		int fa=ni;
		T::ae(fa,i,ni);
	}
	T::dfs(1);
	for(int i=1;i<=n;i++){
		a[T::dfn[i]]=T::dep[i];
	}
	blockchain::init(a,n);
	for(int i=1;i<=m;i++){
		int op=ni,x=ni,k=ni;
		int l=T::dfn[x],r=T::dfe[x];
		if(op==1){
			if(k>r-l+1){
				puts("-1");
			}else{
				printf("%d\n",ask(l,r,k));
			}
		}else{
			int mn,mx;
			blockchain::giter(l,r,mn,mx);
			blockchain::add(l,r,k);
		}
	}
	return 0;
}
