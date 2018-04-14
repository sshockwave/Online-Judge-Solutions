#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <fstream>
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
const int N=200010;
namespace seg{
	const int N=::N*40;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int mx,dt;
		inline void up(){
			mx=max(lson->mx,rson->mx)+dt;
		}
	}pool[N];
	inline node nn(node x=pool){
		static node n=pool+1;
		assert(n<pool+N);
		return *n=*x,n++;
	}
	node build(int l,int r){
		node x=nn();
		x->mx=x->dt=0;
		if(l!=r){
			int m=(l+r)>>1;
			x->lson=build(l,m);
			x->rson=build(m+1,r);
		}
		return x;
	}
	node add(node x,int l,int r,int v,int lend,int rend){
		x=nn(x);
		if(lend==l&&rend==r){
			x->mx+=v,x->dt+=v;
			return x;
		}
		int m=(lend+rend)>>1;
		if(r<=m){
			x->lson=add(x->lson,l,r,v,lend,m);
		}else if(l>m){
			x->rson=add(x->rson,l,r,v,m+1,rend);
		}else{
			x->lson=add(x->lson,l,m,v,lend,m);
			x->rson=add(x->rson,m+1,r,v,m+1,rend);
		}
		x->up();
		return x;
	}
	int ask(node x,int l,int r,int lend,int rend){
		if(lend==l&&rend==r)return x->mx;
		int m=(lend+rend)>>1;
		if(r<=m)return ask(x->lson,l,r,lend,m)+x->dt;
		if(l>m)return ask(x->rson,l,r,m+1,rend)+x->dt;
		return max(ask(x->lson,l,m,lend,m),ask(x->rson,m+1,r,m+1,rend))+x->dt;
	}
}
int a[N],lst[N];
inline bool lcmp(int x,int y){
	return a[x]<a[y];
}
seg::node rt[N];
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cracker.in","r",stdin);
	freopen("cracker.out","w",stdout);
#endif
	int n=ni,m=ni,t=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,lcmp);
	rt[0]=seg::build(1,n);
	for(int i=1;i<=n;i++){
		rt[i]=seg::add(rt[i-1],max(1,lst[i]-m+1),lst[i],1,1,n);
	}
	for(int tot=ni,ans=0;tot--;){
		int lend=ni^(ans*t),rend=ni^(ans*t),v=ni^(ans*t);
		int l=0,r=n;
		while(l<r){
			int m=((l+r)>>1)+1;
			if(a[lst[m]]<v){
				l=m;
			}else{
				r=m-1;
			}
		}
		printf("%d\n",ans=seg::ask(rt[l],lend,rend,1,n));
	}
	return 0;
}
