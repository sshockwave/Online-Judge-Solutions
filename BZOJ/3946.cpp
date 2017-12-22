#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
const int N=50010,L=600010,O=998244353,INF=0x7f7f7f7f;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
namespace T{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int prior;
		int *str,hush;
		int len,sum;
		int pw,prod;
		inline void gstr(){
			static char* s=new char[L];
			static int* num=new int[L];
			scanf("%s",s);
			pw=1,hush=0;
			for(int &i=len=0;s[i];i++,pw=(lint)pw*26%O){
				hush=num[i]=((lint)(s[i]-'a')*pw+hush)%O;
			}
			len=strlen(s),hush=num[len-1];
			str=num,num+=len;
			sum=len,prod=pw;
		}
		inline void up(){
			sum=lson->sum+len+rson->sum;
			prod=(lint)lson->prod*pw%O*rson->prod%O;
			hush=(((lint)rson->hush*pw%O+str[len-1])%O*lson->prod%O+lson->hush)%O;
		}
	};
	node null;
	inline void init(){
		null=new Node;
		null->lson=null->rson=null;
		null->str=NULL,null->hush=0;
		null->len=null->sum=0;
		null->pw=null->prod=1;
	}
	inline node nn(node x=null){
		static node n=new Node[N*100];
		return *n=*x,n->prior=rand(),n++;
	}
	int ghush(node x,int len){
		if(x==null)return 0;
		if(len<=x->lson->sum)return ghush(x->lson,len);
		if(len>x->lson->sum+x->len){
			lint rh=ghush(x->rson,len-x->lson->sum-x->len);
			return ((rh*x->pw%O+x->str[x->len-1])%O*x->lson->prod%O+x->lson->hush)%O;
		}else return ((lint)x->str[len-x->lson->sum-1]*x->lson->prod%O+x->lson->hush)%O;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		node x;
		if(u->prior>v->prior){
			x=nn(u);
			x->prior=u->prior;
			x->rson=mg(x->rson,v);
		}else{
			x=nn(v);
			x->prior=v->prior;
			x->lson=mg(u,x->lson);
		}
		x->up();
		return x;
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		T::node rt;
		inline void down(){
			if(rt!=T::null){
				lson->rt=T::mg(rt,lson->rt);
				rson->rt=T::mg(rt,rson->rt);
				rt=T::null;
			}
		}
	};
	node rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->rt=T::nn();
			x->rt->gstr();
		}else{
			x->rt=T::null;
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void cover(node x,int l,int r,T::node pt){
		if(x->l==l&&x->r==r)return x->rt=T::mg(pt,x->rt),void();
		x->down();
		if(r<=x->m)return cover(x->lson,l,r,pt),void();
		if(l>x->m)return cover(x->rson,l,r,pt),void();
		cover(x->lson,l,x->m,pt);
		cover(x->rson,x->m+1,r,pt);
	}
	int asklen(node x,int p){
		int ans=x->rt->sum;
		if(x->l!=x->r){
			ans+=asklen(p<=x->m?x->lson:x->rson,p);
		}
		return ans;
	}
	int ask(node x,int p,int len){
		if(len<=x->rt->sum)return T::ghush(x->rt,len);
		lint ans=ask(p<=x->m?x->lson:x->rson,p,len-x->rt->sum);
		return ((lint)ans*x->rt->prod%O+x->rt->hush)%O;
	}
}
int glcp(int x,int y){
	int l=0,r=min(seg::asklen(seg::rt,x),seg::asklen(seg::rt,y));
	while(l<r){
		int m=((l+r)>>1)+1;
		if(seg::ask(seg::rt,x,m)==seg::ask(seg::rt,y,m)){
			l=m;
		}else{
			r=m-1;
		}
	}
	return l;
}
namespace seg2{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,dt;
		inline void down(){
			if(dt){
				lson->mn+=dt,lson->dt+=dt;
				rson->mn+=dt,rson->dt+=dt;
				dt=0;
			}
		}
		inline void up(){
			assert(dt==0);
			mn=min(lson->mn,rson->mn);
		}
	};
	node rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->dt=0;
		if(l==r){
			x->mn=glcp(l,l+1);
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void set(node x,int p,int v){
		if(x->l==x->r){
			x->mn=v,x->dt=0;
		}else{
			x->down();
			set(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	void add(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->mn+=v,x->dt+=v,void();
		if(r<=x->m){
			add(x->lson,l,r,v);
		}else if(l>x->m){
			add(x->rson,l,r,v);
		}else{
			add(x->lson,l,x->m,v);
			add(x->rson,x->m+1,r,v);
		}
		x->up();
	}
	int ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mn;
		x->down();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return min(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("boring.in","r",stdin);
	freopen("boring.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	seg::rt=seg::build(1,n);
	if(n>1){
		seg2::rt=seg2::build(1,n-1);
	}
	while(tot--){
		char c;
		while(!isalpha(c=getchar()));
		int l=ni,r=ni;
		if(c=='I'){
			T::node x=T::nn();
			x->gstr();
			seg::cover(seg::rt,l,r,x);
			if(l>1){
				seg2::set(seg2::rt,l-1,glcp(l-1,l));
			}
			if(r<n){
				seg2::set(seg2::rt,r,glcp(r,r+1));
			}
			if(l<r){
				seg2::add(seg2::rt,l,r-1,x->len);
			}
		}else{
			printf("%d\n",l==r?seg::asklen(seg::rt,l):seg2::ask(seg2::rt,l,r-1));
		}
	}
	return 0;
}
