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
const int N=100010,O=1000000007;
int p[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int mn,mx;
		inline void up(){
			mn=min(lson->mn,rson->mn);
			mx=max(lson->mx,rson->mx);
		}
	}pool[N<<1];
	node n,rt;
	node build(int l,int r){
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mn=x->mx=p[l];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	int ask_max(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mx;
		if(r<=x->m)return ask_max(x->lson,l,r);
		if(l>x->m)return ask_max(x->rson,l,r);
		return max(ask_max(x->lson,l,x->m),ask_max(x->rson,x->m+1,r));
	}
	int ask_min(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->mn;
		if(r<=x->m)return ask_min(x->lson,l,r);
		if(l>x->m)return ask_min(x->rson,l,r);
		return min(ask_min(x->lson,l,x->m),ask_min(x->rson,x->m+1,r));
	}
}
int fac[N];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
}
int a[N],b[N];
inline int calc(int n){
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	lint ans=1;
	for(int i=n,j=n;i>=1;i--){
		for(;j>0&&b[j]>a[i];j--);
		ans=ans*(n-j-(n-i))%O;
	}
	return ans;
}
inline void Main(){
	int n=ni,tot=ni;
	gmath(n);
	for(int i=1;i<=n;i++){
		p[i]=ni;
	}
	seg::n=seg::pool;
	seg::rt=seg::build(1,n);
	while(tot--){
		int l1=ni,r1=ni,l2=ni,r2=ni,len=r1-l1+1;
		int ans;
		if(seg::ask_max(seg::rt,l1,r1)<seg::ask_min(seg::rt,l2,r2)){
			ans=fac[len];
		}else{
			memcpy(a+1,p+l1,len<<2);
			memcpy(b+1,p+l2,len<<2);
			ans=calc(len);
		}
		printf("%d\n",ans);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("y.in","r",stdin);
	freopen("y.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		Main();
	}
	return 0;
}
