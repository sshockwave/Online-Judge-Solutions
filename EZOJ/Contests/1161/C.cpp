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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=200010,INF=0x7f7f7f7f;
struct card{
	int f[2],g[2];
	inline int with(int x){
		return x<=f[0]?g[0]:x<=f[1]?g[1]:INF;
	}
	inline friend card operator + (card &a,card &b){
		return (card){a.f[0],a.f[1],b.with(a.g[0]),b.with(a.g[1])};
	}
}a[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int lend,rend,mid;
		node lson,rson;
		card c;
	};
	inline void up(node x){
		x->c=x->lson->c+x->rson->c;
	}
	node build(int l,int r){
		static node n=new Node[N*2];
		node x=n++;
		x->lend=l,x->rend=r,x->mid=(l+r)>>1;
		if(l==r){
			x->c=a[l];
		}else{
			x->lson=build(l,x->mid);
			x->rson=build(x->mid+1,r);
			up(x);
		}
		return x;
	}
	void set(node x,int p,const card &v){
		if(x->lend==x->rend){
			x->c=v;
		}else{
			set(p<=x->mid?x->lson:x->rson,p,v);
			up(x);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("kar.in","r",stdin);
	freopen("kar.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		if(x>y){
			swap(x,y);
		}
		a[i]=(card){x,y,x,y};
	}
	seg::node rt=seg::build(1,n);
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		swap(a[u],a[v]);
		seg::set(rt,u,a[u]);
		seg::set(rt,v,a[v]);
		puts(rt->c.g[0]<INF?"TAK":"NIE");
	}
	return 0;
}
