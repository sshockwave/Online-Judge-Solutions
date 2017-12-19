#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
inline int fpow(int x,int n){
	assert(n>=0);
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int len,sigma;
int lst[N],cnt[N],ls=0;
inline void factor(lint num){
	memset(cnt,0,sizeof(cnt));
	for(lint i=2;i*i<=num;i++){
		lst[ls]=i;
		for(;num%i==0;cnt[ls]++,num/=i);
		ls+=cnt[ls]!=0;
	}
	if(num>1){
		lst[ls]=num;
		cnt[ls]++;
		ls++;
	}
}
lint lcm=0;
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
			lcm=lcm?lcm/gcd(lcm,x->g)*x->g:x->g;
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
map<lint,int>f,g;
int rst[N];
int dfs2(int x,int mu,lint p){
	if(x==ls)return (lint)mu*fpow(sigma,p%(O-1))%O;
	lint ans=0;
	for(int i=0;i<=rst[x];i++,p/=lst[x]){
		ans+=dfs2(x+1,i==0?mu:i==1?O-mu:0,p);
	}
	return ans%O;
}
int faccnt=0;
void dfs1(int x,lint p){
	if(x==ls)return faccnt++,f[p]=dfs2(0,1,p),void();
	for(int &i=rst[x]=0;i<=cnt[x];i++,p*=lst[x]){
		dfs1(x+1,p);
	}
}
int dfs4(int x,lint p){
	if(x==ls)return (lint)(len/p)*f[p]%O;
	lint ans=0;
	for(int i=0;i<=rst[x];i++,p*=lst[x]){
		ans+=dfs4(x+1,p);
	}
	return ans%O;
}
void dfs3(int x,lint b){
	if(x==ls)return g[b]=dfs4(0,1),void();
	for(int &i=rst[x]=0;i<=cnt[x];i++,b*=lst[x]){
		dfs3(x+1,b);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("heiten.in","r",stdin);
	freopen("heiten.out","w",stdout);
#endif
	int n=ni;
	len=ni,sigma=ni;
	int tot=ni;
	seg::rt=seg::build(1,n);
	factor(lcm);
	dfs1(0,1),dfs3(0,1);
	while(tot--){
		int l=ni,r=ni;
		printf("%d\n",g[seg::ask(seg::rt,l,r)]);
	}
	return 0;
}
