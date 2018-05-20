#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010;
int n;
db a[N],b[N];
namespace seg{
	const int N=::N*20;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		db sum;
		int cnt;
		inline void up(){
			cnt=lson->cnt+rson->cnt;
			sum=lson->sum+rson->sum;
		}
	}pool[N],Null;
	node pt[N],*ppt=pt;
	inline node nn(node x=null){
		return **ppt=*x,*(ppt++);
	}
	inline void del(node x){
		*--ppt=x;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		for(int i=0;i<N;i++){
			pt[i]=pool+i;
		}
	}
	node ins(node x,int p,int l=1,int r=n){
		x=nn(x);
		if(l==r){
			x->sum=b[p],x->cnt=1;
		}else{
			int m=(l+r)>>1;
			if(p<=m){
				x->lson=ins(x->lson,p,l,m);
			}else{
				x->rson=ins(x->rson,p,m+1,r);
			}
			x->up();
		}
		return x;
	}
	node mg(node u,node v,int l=1,int r=n){
		if(u==null||v==null)return u!=null?u:v;
		assert(l!=r);
		int m=(l+r)>>1;
		u->lson=mg(u->lson,v->lson,l,m);
		u->rson=mg(u->rson,v->rson,m+1,r);
		u->up();
		del(v);
		return u;
	}
	void sp(node x,int k,node &lhs,node &rhs,int l=1,int r=n){
		if(k==0||k==x->cnt)return (k?(lhs=x,rhs=null):(lhs=null,rhs=x)),void();
		assert(x!=null);
		assert(l<r);
		node y=nn();
		int m=(l+r)>>1;
		if(k<=x->lson->cnt){
			y->rson=x->rson,x->rson=null;
			sp(x->lson,k,x->lson,y->lson,l,m);
		}else{
			sp(x->rson,k-x->lson->cnt,x->rson,y->rson,m+1,r);
		}
		x->up(),y->up();
		lhs=x,rhs=y;
	}
	db ask(node x,int k,int l=1,int r=n){
		if(k==0)return 0;
		if(k==x->cnt)return x->sum;
		assert(l!=r);
		int m=(l+r)>>1;
		if(k<=x->lson->cnt)return ask(x->lson,k,l,m);
		return x->lson->sum+ask(x->rson,k-x->lson->cnt,m+1,r);
	}
	void dfs_print(node x,int l=1,int r=n){
		if(x==null)return;
		int m=(l+r)>>1;
		if(l==r){
			cout<<m<<" ";
			return;
		}
		assert(x->cnt==x->lson->cnt+x->rson->cnt);
		assert(x->sum==x->lson->sum+x->rson->sum);
		dfs_print(x->lson,l,m);
		dfs_print(x->rson,m+1,r);
	}
}
int rnk[N];
namespace intv_set{
	struct Block{
		seg::node rt;
		int lend,d;
		db _sum;
		inline friend bool operator < (const Block &a,const Block &b){
			return a.lend<b.lend;
		}
		inline db ask(int l,int r)const{
			if(r-l+1==rt->cnt)return rt->sum;
			l-=lend-1,r-=lend-1;
			if(d==0){
				const int len=rt->cnt;
				l=len+1-l,r=len+1-r;
				swap(l,r);
			}
			return seg::ask(rt,r)-seg::ask(rt,l-1);
		}
		inline Block spawn(int k){
			assert(k&&k<rt->cnt);
			Block b=(Block){0,lend+k,d,_sum+ask(lend,lend+k-1)};
			if(d){
				seg::sp(rt,k,rt,b.rt);
			}else{
				seg::sp(rt,rt->cnt-k,b.rt,rt);
			}
			return b;
		}
	};
	typedef set<Block>sb;
	sb s;
	inline void build(int n){
		db sum=0;
		for(int i=1;i<=n;i++){
			s.insert(s.end(),(Block){seg::ins(seg::null,rnk[i]),i,0,sum});
			sum+=a[i];
		}
		s.insert(s.end(),(Block){seg::null,n+1,0,sum});
	}
	inline void sort(int l,int r,int d){
		seg::node rt=seg::null;
		sb::iterator it=s.lower_bound((Block){0,l,0,0});
		if(it->lend>l){
			assert(it!=s.begin());
			--it;
			Block a=*it,b=a.spawn(l-a.lend);
			s.erase(it);
			it=s.insert(s.insert(a).first,b);
		}
		db _sum=0;
		if(it!=s.begin()){
			sb::iterator pr=it;
			--pr;
			_sum=pr->_sum+pr->rt->sum;
		}
		for(sb::iterator nxt;it->lend<=r;it=nxt){
			nxt=it,++nxt;
			if(nxt->lend>r+1){
				Block a=*it,b=a.spawn(r-it->lend+1);
				s.erase(it);
				s.insert(it=s.insert(a).first,b);
			}
			rt=seg::mg(rt,it->rt);
			s.erase(it);
		}
		s.insert((Block){rt,l,d,_sum});
	}
	inline db ask(int n){
		if(n==0)return 0;
		sb::iterator it=s.upper_bound((Block){0,n,0,0});
		assert(it!=s.begin());
		--it;
		return it->_sum+it->ask(it->lend,n);
	}
	inline db ask(int l,int r){
		return ask(r)-ask(l-1);
	}
	void travel_print(){
		for(sb::iterator it=s.begin();it!=s.end();++it){
			cout<<"["<<it->lend<<","<<it->lend+it->rt->cnt-1<<"],d="<<it->d<<",pre="<<it->_sum<<":";
			seg::dfs_print(it->rt);
			cout<<endl;
		}
	}
}
db pwlst[11];
inline bool lcmp(int x,int y){
	return a[x]<a[y];
}
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("zkb.in","r",stdin);
	freopen("zkb.out","w",stdout);
#endif
	n=ni;
	int m=ni;
	for(int i=1;i<10;i++){
		pwlst[i]=log10((db)i);
	}
	for(int i=1;i<=n;i++){
		a[i]=b[i]=log10((db)ni);
		lst[i]=i;
	}
	sort(b+1,b+n+1);
	sort(lst+1,lst+n+1,lcmp);
	for(int i=1;i<=n;i++){
		rnk[lst[i]]=i;
	}
	seg::init();
	intv_set::build(n);
	for(int tot=m;tot--;){
		int op=ni,l=ni,r=ni;
		if(op==1){//sort
			intv_set::sort(l,r,ni);
		}else{//ask
			db ans=intv_set::ask(l,r);
			ans-=floor(ans);
			int d=9;
			const static db EPS=1e-10;
			for(;pwlst[d]>ans+EPS;d--);
			putchar('0'+d),putchar('\n');
		}
	}
	return 0;
}
