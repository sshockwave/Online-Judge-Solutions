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
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
union Intv{
	struct{lint l,r;};
	struct{lint x,y;};
	inline friend bool operator < (const Intv &a,const Intv &b){
		return a.r<b.r;
	}
}intv[N];
namespace seg{
	const int N=::N*20;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int tag;
		int cnt;
		Intv sum;
		inline void up(){
			cnt=lson->cnt+rson->cnt;
			sum.x=lson->sum.x+rson->sum.x;
			sum.y=lson->sum.y+rson->sum.y;
		}
	}pool[N];
	node pol=pool;
	int tim=0;
	node build(int l,int r){
		static node &n=pol;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	inline node nn(node x){
		static node &n=pol;
		return x->tag<tim?*n=*x,n->tag=tim,n++:x;
	}
	void add(node &x,const Intv &v){
		x=nn(x);
		if(x->l==x->r){
			x->cnt++;
			x->sum.x+=v.x;
			x->sum.y+=v.y;
		}else{
			add(v.x<=x->m?x->lson:x->rson,v);
			x->up();
		}
	}
	int cnt;
	lint sumx,sumy;
	inline void clr(){
		cnt=sumx=sumy=0;
	}
	void ask(node x,int l,int r){
		if(l>r)return;
		if(x->l==l&&x->r==r)return cnt+=x->cnt,sumx+=x->sum.x,sumy+=x->sum.y,void();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		ask(x->lson,l,x->m);
		ask(x->rson,x->m+1,r);
	}
}
int n;
namespace calc{
	seg::node rt[N];
	inline lint ask(int l,int r){//[l,r)
		lint ans=0;
		using seg::ask;
		using seg::clr;
		{//ql<=l&&r<=qr
			ans+=(clr(),ask(rt[n],1,l),seg::cnt);
			ans-=(clr(),ask(rt[r-1],1,l),seg::cnt);
		}
		{//l<=ql&&qr<=r
			clr(),ask(rt[r],l,n);
			ans+=(lint)seg::cnt*(r-l);
			ans+=seg::sumx;
			ans-=seg::sumy;
		}
		{//ql<l&&qr<r
			int m=(l+r-1)>>1;
			clr(),ask(rt[l-1],1,l-1);
			int cnt1=seg::cnt;
			lint val1=seg::sumy;
			clr(),ask(rt[m],1,l-1);
			int cnt2=seg::cnt;
			lint val2=seg::sumy;
			clr(),ask(rt[r],1,l-1);
			int cnt3=seg::cnt;
			lint val3=seg::sumy;
			ans+=val2-val1-(lint)l*(cnt2-cnt1);
			ans+=(lint)r*(cnt3-cnt2)-(val3-val2);
		}
		{//l<ql&&r<qr
			int m=(l+r-1)>>1;
			{
				clr(),ask(rt[r],l,m);
				int cnt1=seg::cnt;
				lint val1=seg::sumx;
				clr(),ask(rt[n],l,m);
				int cnt2=seg::cnt;
				lint val2=seg::sumx;
				ans+=(val2-val1)-(lint)l*(cnt2-cnt1);
			}
			{
				clr(),ask(rt[r],m+1,r);
				int cnt1=seg::cnt;
				lint val1=seg::sumx;
				clr(),ask(rt[n],m+1,r);
				int cnt2=seg::cnt;
				lint val2=seg::sumx;
				ans+=(lint)r*(cnt2-cnt1)-(val2-val1);
			}
		}
		return ans;
	}
	lint f[N];
	int que[N];
	int fr[N];
	inline lint dp(){
		int qh=0,qt=0;
		f[1]=0,fr[1]=1;
		que[qt++]=1;
		for(int i=2;i<=n;i++){
			for(;qh+1<qt&&fr[que[qh+1]]<=i;qh++);
			assert(qh<qt);
			f[i]=f[que[qh]]+ask(que[qh],i);
			int &r=fr[i]=n+1;
			for(int j;qh<qt&&(j=que[qt-1],f[j]+ask(j,fr[j])>f[i]+ask(i,fr[j]));r=fr[j],qt--);
			if(qh==qt){
				assert(r<=n);
				que[qt++]=i;
				continue;
			}
			int j=que[qt-1],l=fr[j]+1;
			while(l<r){
				int m=(l+r)>>1;
				if(f[j]+ask(j,m)<f[i]+ask(i,m)){
					l=m+1;
				}else{
					r=m;
				}
			}
			if(r<=n){
				que[qt++]=i;
			}
		}
		assert(qh<qt);
		return f[n];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ship.in","r",stdin);
	freopen("ship.out","w",stdout);
#endif
	n=ni;
	int q=ni;
	for(int i=1;i<=q;i++){
		intv[i]=(Intv){next_num<lint>(),next_num<lint>()};
	}
	sort(intv+1,intv+q+1);
	calc::rt[0]=seg::build(1,n);
	for(int i=1,j=1;i<=n;i++){
		calc::rt[i]=calc::rt[i-1],seg::tim++;
		for(;j<=q&&intv[j].r==i;j++){
			seg::add(calc::rt[i],intv[j]);
		}
	}
	printf("%lld\n",calc::dp());
	return 0;
}
