#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
const int N=310,D=10010,E=N<<1;
namespace disc{
	const int N=::N*4;
	int *num[N],n;
	inline void init(){
		n=0;
	}
	inline void psh(int &x){
		num[++n]=&x;
	}
	inline bool ncmp(int *a,int *b){
		return *a<*b;
	}
	inline int main(){
		int v=-1,j=0;
		sort(num+1,num+n+1,ncmp);
		for(int i=1;i<=n;i++){
			*num[i]=v!=*num[i]?v=*num[i],++j:j;
		}
		return j;
	}
}
struct Edge{
	int u,v;
}edg[E];
bool deci[E];
namespace T{
	const int N=::N*4,E=::E>>1<<1;
	int to[E],bro[E],eid[E],head[N],e;
	inline void init(int n){
		mset(head+1,-1,n);
		e=0;
	}
	inline void ae(int u,int v,int i){
		to[e]=v,bro[e]=head[u],eid[e]=i,head[u]=e++;
	}
	inline void add(int u,int v,int i){
		ae(u,v,i),ae(v,u,i);
	}
	int fa[N],rt[N],con[N],dep[N];
	void dfs(int x,int r){
		rt[x]=r;
		dep[x]=dep[fa[x]]+1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			fa[v]=x;
			con[v]=eid[i];
			dfs(v,r);
		}
	}
	int que[N],qh,qt;
	int pre[::E];
	inline bool psh(int i){
		if(rt[edg[i].u]!=rt[edg[i].v]){
			for(;~i;deci[i]=true,deci[i^1]=false,i=pre[i]);
			return true;
		}
		que[qt++]=i;
		return false;
	}
	int djfa[N];
	int gnxt(int x){
		return djfa[x]?djfa[x]=gnxt(djfa[x]):x;
	}
	inline bool bfs(int curid){
		{//build tree
			init(disc::n);
			for(int i=0;i<curid;i++){
				if(deci[i]){
					T::add(edg[i].u,edg[i].v,i);
				}
			}
			mset(fa+1,0,disc::n);
			mset(con+1,-1,disc::n);//cout
			for(int i=1;i<=disc::n;i++){
				djfa[i]=0;
				if(fa[i]==0){
					dfs(i,i);
				}
			}
		}
		qh=0,qt=0;
		pre[curid]=-1,que[qt++]=curid;
		deci[curid]=false;
		if(psh(curid))return true;
		for(;qh<qt;qh++){
			const int ex=que[qh];
			int u=gnxt(edg[ex].u),v=gnxt(edg[ex].v);
			for(;u!=v;u=gnxt(u)){
				if(dep[u]<dep[v]){
					swap(u,v);
				}
				assert(deci[con[u]]);
				pre[con[u]^1]=ex;
				if(psh(con[u]^1))return true;
				djfa[u]=fa[u];
			}
		}
		return false;
	}
}
inline int Main(){
	const int n=ni;
	disc::init();
	for(int i=0;i<n*2;i++){
		edg[i]=(Edge){ni+1,ni+1};
		disc::psh(edg[i].u);
		disc::psh(edg[i].v);
	}
	disc::main();
	int ans=0;
	for(int i=0;i<n*2;i+=2){
		ans+=T::bfs(i)||T::bfs(i+1);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()*2));
	return 0;
}
