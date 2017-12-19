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
template<class T>T gcd(T a,T b){
	return b?gcd(b,a%b):a;
}
const int N=100010,O=998244353;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		lint g;
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->g=next_num<lint>();
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->g=gcd(x->lson->g,x->rson->g);
		}
		return x;
	}
	lint ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->g;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return gcd(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
}
int pw[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("heiten.in","r",stdin);
	freopen("heiten.out","w",stdout);
#endif
	int n=ni,len=ni;
	pw[0]=1,pw[1]=ni%O;
	int tot=ni;
	for(int i=2;i<=len;i++){
		pw[i]=(lint)pw[i-1]*pw[1]%O;
	}
	seg::rt=seg::build(1,n);
	while(tot--){
		int l=ni,r=ni;
		lint ans=0,g=seg::ask(seg::rt,l,r);
		for(int i=1;i<=len;i++){
			ans+=pw[gcd((lint)i,g)];
		}
		printf("%lld\n",ans%O);
	}
	return 0;
}
