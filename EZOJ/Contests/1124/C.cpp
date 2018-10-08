#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<lint>())
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
const lint N=500010,INF=0x7f7f7f7f7f7f7f7fll;
union Tag{
	lint a[3];
	struct{
		lint dt,dtmn,dtmx;
	};
	bool has(){
		return dt!=0||dtmn>-INF||dtmx<INF;
	}
	void clr(){
		dt=0,dtmn=-INF,dtmx=INF;
	}
};
inline lint get_nxt(lint x,lint a,lint b){
	return a!=x?a:b;
}
inline void infadd(lint &a,lint b){
	if(a!=INF&&a!=-INF){
		a+=b;
	}
}
namespace seg{
	const lint N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		//Static
		node lson,rson;
		lint l,m,r;
		lint len;
		//Info
		lint mn1,mn2;
		lint mx1,mx2;
		lint cntmn,cntmx;
		lint sum;
		Tag tag;
		//Functions
		void dn();
		inline void up(){
			mn1=min(lson->mn1,rson->mn1);
			mn2=min(get_nxt(mn1,lson->mn1,lson->mn2),get_nxt(mn1,rson->mn1,rson->mn2));
			mx1=max(lson->mx1,rson->mx1);
			mx2=max(get_nxt(mx1,lson->mx1,lson->mx2),get_nxt(mx1,rson->mx1,rson->mx2));
			cntmn=0;
			cntmn+=lson->mn1==mn1?lson->cntmn:0;
			cntmn+=rson->mn1==mn1?rson->cntmn:0;
			cntmx=0;
			cntmx+=lson->mx1==mx1?lson->cntmx:0;
			cntmx+=rson->mx1==mx1?rson->cntmx:0;
			sum=lson->sum+rson->sum;
			assert(!tag.has());
		}
	}pool[N];
	void uni(const node x,lint v){
		x->mn1=x->mx1=v;
		x->mn2=INF,x->mx2=-INF;
		x->cntmn=x->cntmx=x->len;
		x->sum=(lint)x->len*v;
		x->tag.dt=0;
		x->tag.dtmn=v;
		x->tag.dtmx=v;
	}
	node build(lint l,lint r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->len=r-l+1;
		x->tag.clr();
		if(l==r){
			uni(x,ni);
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void trim(const node x,const Tag &tag){
		if(tag.dt){
			const lint v=tag.dt;
			x->mn1+=v,infadd(x->mn2,v);
			x->mx1+=v,infadd(x->mx2,v);
			x->sum+=(lint)x->len*v;
			x->tag.dt+=tag.dt;
			infadd(x->tag.dtmn,tag.dt);
			infadd(x->tag.dtmx,tag.dt);
		}
		if(tag.dtmn>x->mn1){
			const lint v=tag.dtmn;
			assert(v>x->tag.dtmn);
			x->tag.dtmn=v,apmax(x->tag.dtmx,v);
			if(v>=x->mx1){
				uni(x,v);
			}else if(v>=x->mx2){
				assert(x->mx2>-INF);
				x->mn1=v,x->mn2=x->mx1,x->mx2=v;
				x->cntmn=x->len-x->cntmx;
				assert(x->cntmn);
				x->sum=(lint)x->cntmn*x->mn1+(lint)x->cntmx*x->mx1;
			}else{
				x->dn(),x->up();
			}
		}
		if(tag.dtmx<x->mx1){
			const lint v=tag.dtmx;
			assert(v<x->tag.dtmx);
			apmin(x->tag.dtmn,v),x->tag.dtmx=v;
			if(v<=x->mn1){
				uni(x,v);
			}else if(v<=x->mn2){
				assert(x->mn2<INF);
				x->mn2=v,x->mx1=v,x->mx2=x->mn1;
				x->cntmx=x->len-x->cntmn;
				assert(x->cntmx);
				x->sum=(lint)x->cntmn*x->mn1+(lint)x->cntmx*x->mx1;
			}else{
				x->dn(),x->up();
			}
		}
	}
	void Node::dn(){
		if(tag.has()){
			trim(lson,tag);
			trim(rson,tag);
			tag.clr();
		}
	}
	void dfs_trim(node x,lint l,lint r,const Tag &tag){
		if(x->l==l&&x->r==r)return trim(x,tag);
		x->dn();
		if(r<=x->m){
			dfs_trim(x->lson,l,r,tag);
		}else if(l>x->m){
			dfs_trim(x->rson,l,r,tag);
		}else{
			dfs_trim(x->lson,l,x->m,tag);
			dfs_trim(x->rson,x->m+1,r,tag);
		}
		x->up();
	}
	lint ask_sum(const node x,lint l,lint r){
		if(x->l==l&&x->r==r)return x->sum;
		x->dn();
		if(r<=x->m)return ask_sum(x->lson,l,r);
		if(l>x->m)return ask_sum(x->rson,l,r);
		return ask_sum(x->lson,l,x->m)+ask_sum(x->rson,x->m+1,r);
	}
	lint ask_mx(const node x,lint l,lint r){
		if(x->l==l&&x->r==r)return x->mx1;
		x->dn();
		if(r<=x->m)return ask_mx(x->lson,l,r);
		if(l>x->m)return ask_mx(x->rson,l,r);
		return max(ask_mx(x->lson,l,x->m),ask_mx(x->rson,x->m+1,r));
	}
	lint ask_mn(const node x,lint l,lint r){
		if(x->l==l&&x->r==r)return x->mn1;
		x->dn();
		if(r<=x->m)return ask_mn(x->lson,l,r);
		if(l>x->m)return ask_mn(x->rson,l,r);
		return min(ask_mn(x->lson,l,x->m),ask_mn(x->rson,x->m+1,r));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("wyywyy.in","r",stdin);
	freopen("wyywyy.out","w",stdout);
#endif
	const lint n=ni;
	const seg::node rt=seg::build(1,n);
	Tag dt;
	for(lint tot=ni;tot--;){
		const lint tp=ni,l=ni,r=ni;
		if(tp<=3){
			dt.clr();
			dt.a[tp-1]=ni;
			seg::dfs_trim(rt,l,r,dt);
		}else if(tp==4){
			printf("%lld\n",seg::ask_sum(rt,l,r));
		}else if(tp==5){
			printf("%lld\n",seg::ask_mx(rt,l,r));
		}else if(tp==6){
			printf("%lld\n",seg::ask_mn(rt,l,r));
		}
	}
	return 0;
}
