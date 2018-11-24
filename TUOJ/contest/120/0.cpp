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
const int N=10010,INF=0x7f7f7f7f,D=3;
namespace G{
	const int N=::N*2,E=(50010*2+::N+::N)*2;
	int to[E],bro[E],cap[E],head[N],e=0,n,s,t;
	inline void init(){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int dis[N],que[N],cur[N];
	inline void bfs(){
		int qh=0,qt=0;
		mset(dis+1,127,n);
		dis[s]=0,que[qt++]=s;
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==INF){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int a){
		if(x==t||a==0)return a;
		int r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,min(cap[i],r));
				r-=d,cap[i]-=d,cap[i^1]+=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	int dinic(int a){
		int flow=0;
		for(;bfs(),dis[t]<INF&&flow<a;flow+=aug(s,a-flow));
		return flow;
	}
	int gpath(int lst[]){
		int ls=0;
		for(int x=s;x!=t;){
			if(ls==0||x/2!=lst[ls]){
				lst[++ls]=x/2;
			}
			for(int i=head[x];~i;i=bro[i]){
				if(cap[i]==0&&(i&1)==0){
					cap[i]=cap[i^1],cap[i^1]=0;
					x=to[i];
					break;
				}
			}
		}
		return ls;
	}
}
int lst[D][N],ls[D];
int pid[N],pos[N];
int lst2[2][N],ls2[2];
inline void pint(int x){
	printf("%d ",x);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	const int a=ni,b=ni,c=ni;
	G::n=n*2+1,G::s=a*2+1,G::t=b*2,G::init();
	for(int i=1;i<=n;i++){
		G::add(i*2,i*2+1,1);
	}
	for(;tot--;){
		const int u=ni,v=ni;
		G::add(u*2+1,v*2,1);
		G::add(v*2+1,u*2,1);
	}
	G::dinic(D);
	mset(pos+1,0,n);
	pid[b]=0;
	for(int i=0;i<D;i++){
		ls[i]=G::gpath(lst[i]);
		assert(lst[i][1]==a);
		assert(lst[i][ls[i]]!=b);
		for(int j=1;j<=ls[i];j++){
			pid[lst[i][j]]=i;
			pos[lst[i][j]]=j;
		}
		lst[i][++ls[i]]=b;
		if(ls[i]>ls[pid[b]]){
			pid[b]=i;
		}
	}
	pos[b]=ls[pid[b]];
	if(pos[c]){
		const int p1=pid[c],p2=p1?0:1;
		printf("%d\n",ls[p1]-1+ls[p2]-1);
		for(int i=1;i<=ls[p1];i++){
			pint(lst[p1][i]);
		}
		for(int i=ls[p2]-1;i>=1;i--){
			pint(lst[p2][i]);
		}
	}else{
		G::s=c*2+1,G::t=1;
		for(int i=1;i<=n;i++){
			if(pos[i]){
				G::add(i*2+1,G::t,1);
			}
		}
		if(G::dinic(2)<2){
			puts("-1");
			return 0;
		}
		for(int i=0;i<2;i++){
			ls2[i]=G::gpath(lst2[i]);
			assert(lst2[i][1]==c);
		}
		int x=lst2[0][ls2[0]],y=lst2[1][ls2[1]];
		int f1=0,f2=1;
		if(pos[x]>pos[y]){
			swap(x,y),swap(f1,f2);
		}
		const int p1=pid[x],p2=pid[y],p3=p1&&p2?0:p1!=1&&p2!=1?1:2;
		printf("%d\n",(pos[x]-1)+(ls2[f1]-1)+(ls2[f2]-1)+(ls[p2]-pos[y])+(ls[p3]-1));
		for(int i=1;i<pos[x];i++){
			pint(lst[p1][i]);
		}
		for(int i=ls2[f1];i>1;i--){
			pint(lst2[f1][i]);
		}
		for(int i=1;i<ls2[f2];i++){
			pint(lst2[f2][i]);
		}
		for(int i=pos[y];i<ls[p2];i++){
			pint(lst[p2][i]);
		}
		for(int i=ls[p3];i>1;i--){
			pint(lst[p3][i]);
		}
		pint(a);
	}
	putchar('\n');
	return 0;
}
