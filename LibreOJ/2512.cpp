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
const int N=200010,O=1000000007;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int s[3],a[3],dt;
		inline void addv(int v){
			dt=(dt+v)%O;
			for(int i=0;i<3;i++){
				a[i]=(a[i]+(lint)s[i]*v)%O;
			}
		}
		inline void dn(){
			if(dt){
				lson->addv(dt);
				rson->addv(dt);
				dt=0;
			}
		}
		inline void up(){
			assert(dt==0);
			for(int i=0;i<3;i++){
				a[i]=(lson->a[i]+rson->a[i])%O;
			}
		}
		inline void ini_up(){
			for(int i=0;i<3;i++){
				s[i]=(lson->s[i]+rson->s[i])%O;
			}
		}
	}pool[N];
	node rt;
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->dt=0;
		if(l==r){
			x->s[0]=1,x->a[0]=ni;
			for(int i=1;i<3;i++){
				x->s[i]=(lint)x->s[i-1]*l%O,x->a[i]=(lint)x->s[i]*x->a[0]%O;
			}
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->ini_up();
			x->up();
		}
		return x;
	}
	void ask(node x,int l,int r,lint ans[]){
		if(l<=x->l&&x->r<=r){
			for(int i=0;i<3;i++){
				ans[i]+=x->a[i];
			}
			return;
		}
		x->dn();
		if(l<=x->m){
			ask(x->lson,l,r,ans);
		}
		if(r>x->m){
			ask(x->rson,l,r,ans);
		}
	}
	void add(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->addv(v);
		x->dn();
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
}
int n,lim;
inline int calc(int ll,int rr){
	if(ll>rr)return 0;
	lint s[3]={0,0,0};
	seg::ask(seg::rt,ll,rr,s);
	for(int i=0;i<3;i++){
		s[i]%=O;
	}
	const int r=lim;
	int ans=0;
	const static int inv2=(O+1)>>1;
	if(ll-r+1<1){
		if(rr+r-1>n){//[]
			int a=r+O-n,b=n+1;
			ans=(O-s[2]+s[1]*(b+O-a)+s[0]*a%O*b)%O;
			ans=(ans+(O-(s[1]<<1)%O+s[0]*(n+r+1))%O*(n-r)%O*inv2)%O;
		}else{//[~
			ans=(r*s[1]+(s[1]+O-s[2])*inv2)%O;
		}
	}else{
		if(rr+r-1>n){//~]
			int a=((lint)(r<<1)+O-n)%O,b=n+1;
			ans=(O-s[2]+s[1]*(b+O-a)+s[0]*a%O*b)%O*inv2%O;
		}else{//~~
			ans=((lint)r*(r+1)>>1)%O*s[0]%O;
		}
	}
	return ans;
}
int lst[N];
inline int ask(int _lim){
	lim=_lim;
	if(lim<=0)return 0;
	int ls=0;
	lst[++ls]=0;
	lst[++ls]=lim-1;
	lst[++ls]=n-lim+1;
	lst[++ls]=n;
	sort(lst+1,lst+ls+1);
	lint ans=0;
	for(int i=2;i<=ls;i++){
		ans+=calc(lst[i-1]+1,lst[i]);
	}
	return (ans%O+O)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	n=ni;
	int m=ni;
	seg::rt=seg::build(1,n);
	for(int i=1;i<=m;i++){
		if(ni==1){
			int l=ni,r=ni;
			seg::add(seg::rt,min(l,r),max(l,r),ni);
		}else{
			int l=ni,r=ni;
			printf("%d\n",(ask(r)+O-ask(l-1))%O);
		}
	}
	return 0;
}
