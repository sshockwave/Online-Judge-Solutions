#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	int val,cnt,delta;
	void build(int l,int r){
		lend=l,rend=r,mid=(l+r)>>1;
		val=0,cnt=r-l+1;
		if(l!=r){
			static node n=new SegmentTree[N<<1];
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	inline void up(){
		if(lson->val<rson->val){
			val=lson->val,cnt=lson->cnt;
		}else if(lson->val>rson->val){
			val=rson->val,cnt=rson->cnt;
		}else{
			val=lson->val,cnt=lson->cnt+rson->cnt;
		}
	}
	inline void down(){
		if(delta){
			lson->val+=delta,lson->delta+=delta;
			rson->val+=delta,rson->delta+=delta;
			delta=0;
		}
	}
	void add(int l,int r,int v){
		if(lend==l&&rend==r){
			val+=v,delta+=v;
			return;
		}
		down();
		if(r<=mid){
			lson->add(l,r,v);
		}else if(l>mid){
			rson->add(l,r,v);
		}else{
			lson->add(l,mid,v);
			rson->add(mid+1,r,v);
		}
		up();
	}
	inline int ask(){
		return val?0:cnt;
	}
}seg;
int n,color[N];
lint ans=0;
queue<int>q[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int _c[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(_c,0,sizeof(_c));
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int &u,const int &v){
		ae(u,v),ae(v,u);
	}
	int dfn[N]={0},dfe[N],tim=0;
	void dfs(int x,int e){
		static int stk[N],ss=0;
		int c=color[x],old=_c[c],pre=0;
		dfn[x]=++tim,stk[++ss]=x,_c[c]=ss;
		if(old){
			pre=stk[old+1];
			seg.add(1,dfn[pre]-1,1);
		}
		queue<int>tmp;
		for(int i;!q[c].empty();tmp.push(i),q[c].pop()){
			i=q[c].front();
			if(dfn[i]>=dfn[pre]){
				seg.add(dfn[i],dfe[i],1);
			}
		}
		ans+=seg.ask()-(n-tim);
		for(int i=head[x];~i;i=bro[i]){
			if(i!=e){
				dfs(to[i],i^1);
				for(int u;!q[c].empty();q[c].pop()){
					u=q[c].front();
					seg.add(dfn[u],dfe[u],1);
				}
			}
		}
		dfe[x]=tim,ss--,_c[c]=old;
		if(old){
			seg.add(1,dfn[pre]-1,-1);
		}
		for(int i;!tmp.empty();q[c].push(i),tmp.pop()){
			i=tmp.front();
			if(dfn[i]>=dfn[pre]){
				seg.add(dfn[i],dfe[i],-1);
			}
		}
		q[c].push(x);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		color[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	seg.build(1,n),T::dfs(1,-1);
	printf("%lld\n",ans);
	return 0;
}
