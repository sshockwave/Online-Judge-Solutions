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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=43;
const lint LINF=0x7f7f7f7f7f;
namespace G{
	const int N=43*43,E=43*43*300;
	int to[E],bro[E],head[N],e,n,s,t;
	lint cap[E];
	inline int nn(){
		return ++n;
	}
	inline void init(){
		n=0,e=0,s=nn(),t=nn();
	}
	inline void reset(){
		memset(head+1,-1,n<<2);
	}
	inline void ae(int u,int v,lint c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,lint c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N];
	inline bool bfs(){
		memset(dis+1,-1,n<<2);
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==-1){
					dis[v=to[i]]=dis[x]+1,que[qt++]=v;
				}
			}
		}
		return ~dis[t];
	}
	lint aug(int x,lint a){
		if(x==t){
			return a;
		}
		lint d,r=a;
		for(int i=head[x],v;(~i)&&r;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
			}
		}
		if(r){
			dis[x]=-1;
		}
		return a-r;
	}
	inline lint dinic(){
		lint flow=0;
		for(;bfs();flow+=aug(s,LINF));
		return flow;
	}
}
int n,m;
int mat[N][N],node[N][N];
lint sum;
inline lint work(lint val){
	G::reset();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((i^j)&1){
				G::add(G::s,node[i][j],val-mat[i][j]);
				if(i>1){G::add(node[i][j],node[i-1][j],LINF);}
				if(i<n){G::add(node[i][j],node[i+1][j],LINF);}
				if(j>1){G::add(node[i][j],node[i][j-1],LINF);}
				if(j<m){G::add(node[i][j],node[i][j+1],LINF);}
			}else{
				G::add(node[i][j],G::t,val-mat[i][j]);
			}
		}
	}
	lint t=G::dinic();
	return t*2==val*n*m-sum?t:-1;
}
inline lint bchop(lint l,lint r){
	while(l<r){
		lint mid=(l+r)>>1,val=work(mid);
		if(~val){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	return work(l);
}
inline lint Main(){
	n=ni,m=ni;
	G::init();
	lint diff=0,mx=0;
	sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			apmax(mx,mat[i][j]=ni);
			sum+=mat[i][j];
			node[i][j]=G::nn();
			if((i^j)&1){
				diff-=mat[i][j];
			}else{
				diff+=mat[i][j];
			}
		}
	}
	return (n&m&1)?
		(diff>=mx?work(diff):-1):
		(diff==0?bchop(mx,LINF):-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
