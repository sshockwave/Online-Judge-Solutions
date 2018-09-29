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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1010,N2=N*N;
namespace T{
	const int N=::N2<<1,E=N;
	int to[E],bro[E],head[N],e=0,n,gn;
	inline void init(int _n){
		n=_n,gn=_n;
		mset(head+1,-1,n);
	}
	inline int nn(){
		return ++n,head[n]=-1,n;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int fa[N],size[N];
	void dfs(int x){
		size[x]=x<=gn;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			size[x]+=size[v];
		}
	}
	inline void build(){
		for(int i=2;i<=n;i++){
			ae(fa[i],i);
		}
		dfs(1);
	}
}
namespace G{
	const int N=::N2,E=N*4;
	int to[E],bro[E],head[N],e=0,n=0;
	int dfn[N],low[N],tim=0;
	int stk[N],ss=0;
	int xcor[N],ycor[N];
	inline int nn(int x,int y){
		n++;
		xcor[n]=x,ycor[n]=y;
		head[n]=-1;
		dfn[n]=0;
		return n;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		if(u&&v){
			ae(u,v),ae(v,u);
		}
	}
	void dfs(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				dfs(v);
				apmin(low[x],low[v]);
				if(low[v]>=dfn[x]){
					int u;
					int t=T::nn();
					do{
						u=stk[--ss];
						T::fa[u]=t;
					}while(u!=v);
					T::fa[t]=x;
				}
			}else{
				apmin(low[x],dfn[v]);
			}
		}
	}
}
int nd[N][N],n,m;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
namespace B{
	int que[G::E],qh=0,qt=0;
	bool vis[G::E];
	inline void psh(int e){
		if(!vis[e]){
			vis[e]=true;
			que[qt++]=e;
		}
	}
	inline bool test_com(int a,int b,int x){
		using T::fa;
		if(fa[fa[a]]!=x&&fa[fa[b]]!=x)return true;
		return fa[a]==fa[b];
	}
	inline void main(){
		mset(vis,0,G::e);
		for(int i=G::head[1];~i;i=G::bro[i]){
			psh(i^1);
		}
		for(;qh<qt;){
			const int e=que[qh++];
			const int u=G::to[e^1];
			const int v=G::to[e];
			using G::xcor;
			using G::ycor;
			for(int i=G::head[u];~i;i=G::bro[i]){
				int t=G::to[i];
				bool bbx=xcor[u]-xcor[t]==xcor[v]-xcor[u];
				bool bby=ycor[u]-ycor[t]==ycor[v]-ycor[u];
				if(bbx&&bby){
					psh(i^1);
					break;
				}
			}
			for(int i=G::head[v];~i;i=G::bro[i]){
				int t=G::to[i];
				if(test_com(u,t,v)){
					psh(i^1);
				}
			}
		}
	}
	int tag[T::N],tim=0,sum=0;
	inline void upd(int x){
		if(tag[x]<tim){
			tag[x]=tim;
			sum+=T::size[x];
		}
	}
	inline int calc(const int x){
		sum=0,++tim;
		using namespace G;
		using T::fa;
		T::size[0]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[i^1])continue;
			v=to[i];
			upd(fa[fa[v]]==x?fa[v]:0);
		}
		if(tag[0]==tim){
			sum+=T::size[1]-T::size[x]-1;
		}
		return sum;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
#endif
	n=ni,m=ni;
	G::nn(0,0);
	memset(nd,0,sizeof(nd));
	for(int i=1;i<=n;i++){
		static char s[N];
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='.'){
				nd[i][j]=G::nn(i,j);
			}else if(s[j]=='X'){
				nd[i][j]=1;
				G::xcor[1]=i,G::ycor[1]=j;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int d=0;d<2;d++){
				G::add(nd[i][j],nd[i+dx[d]][j+dy[d]]);
			}
		}
	}
	T::init(G::n);
	G::dfs(1);
	T::build();
	B::main();
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			const int x=nd[i][j];
			if(G::dfn[x]&&x!=1){
				ans+=B::calc(x);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
