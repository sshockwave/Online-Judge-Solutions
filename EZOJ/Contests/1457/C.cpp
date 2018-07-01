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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010,INF=0x7f7f7f7f;
struct Val{
	int v,cnt;
	inline friend bool operator < (const Val &a,const Val &b){
		return a.v!=b.v?a.v<b.v:a.cnt<b.cnt;
	}
};
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		Val v;
		int dt;
		inline void addv(int x){
			v.v+=x,dt+=x;
		}
		inline void up(){
			v=max(lson->v,rson->v);
			v.v+=dt;
		}
	}pool[N];
	node npt=pool;
	node build(int l,int r){
		const node x=npt++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void set(node x,int p,const Val &v){
		if(x->l==x->r){
			x->v=v;
			x->dt=0;
		}else{
			set(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	void add(node x,int r,int v){
		if(x->r==r)return x->addv(v);
		if(r<=x->m){
			add(x->lson,r,v);
		}else{
			x->lson->addv(v);
			add(x->rson,r,v);
		}
		x->up();
	}
	inline void clr(){
		for(node i=pool;i<npt;i++){
			i->v=(Val){0,0},i->dt=0;
		}
	}
}
struct Event{
	int x,r,v;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.x<b.x;
	}
}ev[N<<1];
int es=0;
inline Val calc(const seg::node rt,int v){
	seg::clr();
	Val ans=(Val){0,0};
	for(int i=1,j=1;i<=rt->r;i++){
		for(;j<=es&&ev[j].x==i;j++){
			seg::add(rt,ev[j].r,ev[j].v);
		}
		const Val cur=(Val){rt->v.v-v,rt->v.cnt+1};
		apmax(ans,cur);
		seg::set(rt,i,cur);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
#endif
	const int n=ni,m=ni;
	int sum=0,mxr=0;
	for(int i=1;i<=n;i++){
		const int l=ni,r=ni,c=ni;
		sum+=c,apmax(mxr,r);
		ev[++es]=(Event){l,l-1,c};
		ev[++es]=(Event){r,l-1,-c};
	}
	sort(ev+1,ev+es+1);
	const seg::node rt=seg::build(0,mxr);
	int l=0,r=sum;
	for(;l<r;){
		const int mid=((l+r)>>1)+1;
		if(calc(rt,mid).cnt<m){
			r=mid-1;
		}else{
			l=mid;
		}
	}
	const Val ans=calc(rt,l);
	assert(ans.v+(lint)min(ans.cnt,m)*l<=sum);
	printf("%d\n",ans.v+min(ans.cnt,m)*l);
	return 0;
}
