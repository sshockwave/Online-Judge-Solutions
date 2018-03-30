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
	bool f=c=='-'&&(c=getchar());
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return f?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=300010,INF=0x7f7f7f7f;
int c[N],pos[N];
namespace solve1{
	namespace G{
		const int E=::N*3*2;
		int to[E],bro[E],cap[E],val[E],head[N],e=0,s,t,n;
		inline void init(){
			memset(head,-1,sizeof(head));
		}
		inline void ae(int u,int v,int c,int w){
			to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
		}
		inline void add(int u,int v,int c,int w){
			ae(u,v,c,w),ae(v,u,0,-w);
		}
		inline void resetflow(){
			for(int i=0;i<e;i+=2){
				cap[i]+=cap[i^1],cap[i^1]=0;
			}
		}
		int dis[N],que[N];
		bool inque[N];
		inline void spfa(){
			memset(dis+1,127,n*sizeof(dis[0]));
			memset(inque+1,0,n*sizeof(inque[0]));
			int qh=0,qt=0;
			dis[s]=0;
			que[qt++]=s,inque[s]=true;
			while(qh!=qt){
				int x=que[qh++];
				if(qh==N){
					qh=0;
				}
				for(int i=head[x],v;~i;i=bro[i]){
					if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
						dis[v]=dis[x]+val[i];
						if(!inque[v]){
							que[qt++]=v,inque[v]=true;
							if(qt==N){
								qt=0;
							}
						}
					}
				}
				inque[x]=false;
			}
		}
		int vis[N],tim=0;
		int aug(int x,int a){
			if(x==t||a==0)return a;
			vis[x]=tim;
			int r=a,d;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==dis[x]+val[i]&&vis[v]<tim){
					d=aug(v,min(r,cap[i]));
					cap[i]-=d,cap[i^1]+=d,r-=d;
					if(r==0)break;
				}
			}
			return a-r;
		}
		inline int mcmf(){
			int cost=0;
			for(;spfa(),dis[t]<INF;tim++,cost+=dis[t]*aug(s,INF));
			return cost;
		}
	}
	inline void main(int n,int m){
		G::init();
		G::s=n+1,G::t=n+2,G::n=n+2;
		for(int i=1;i<=n;i++){
			G::add(i,G::t,c[i],0);
		}
		for(int i=2;i<=n;i++){
			G::add(i/2,i,INF,1);
			G::add(i,i/2,INF,1);
		}
		for(int i=1;i<=m;i++){
			G::resetflow();
			G::add(G::s,pos[i],1,0);
			printf("%d\n",G::mcmf());
		}
	}
}
namespace solve8{
	inline int getdis(int u,int v){
		int cnt=0;
		while(u!=v){
			if(u>v){
				u>>=1;
			}else{
				v>>=1;
			}
			cnt++;
		}
		return cnt;
	}
	inline void main(int n,int m){
		int toc=0;
		for(int &i=toc;c[i]==0;i++);
		int ans=0;
		for(int i=1;i<=m;i++){
			printf("%d\n",ans+=getdis(pos[i],toc));
		}
	}
}
namespace solve11{
	map<int,int>mp;
	int n;
	void dfs(int x,int fa,int dis){
		mp[dis]+=c[x];
		if(x>1&&(x>>1)!=fa){
			dfs(x>>1,x,dis+1);
		}
		if((x<<1)<=n&&(x<<1)!=fa){
			dfs(x<<1,x,dis+1);
		}
		if(((x<<1)|1)<=n&&((x<<1)|1)!=fa){
			dfs((x<<1)|1,x,dis+1);
		}
	}
	inline void main(int _n,int m){
		n=_n;
		dfs(pos[1],0,0);
		int ans=0;
		for(int i=1;i<=m;i++){
			for(;mp.begin()->second==0;mp.erase(mp.begin()));
			ans+=mp.begin()->first;
			mp.begin()->second--;
			printf("%d\n",ans);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bird.in","r",stdin);
	freopen("bird.out","w",stdout);
#endif
	int n=ni,m=ni;
	int cntc=0,cntp=-1;
	for(int i=1;i<=n;i++){
		c[i]=ni;
		cntc+=c[i]>0;
	}
	for(int i=1;i<=m;i++){
		pos[i]=ni;
		if(cntp==-1){
			cntp=pos[i];
		}else if(cntp!=pos[i]){
			cntp=-2;
		}
	}
	if(cntc==1){
		solve8::main(n,m);
	}else if(cntp>0){
		solve11::main(n,m);
	}else{
		solve1::main(n,m);
	}
	return 0;
}
