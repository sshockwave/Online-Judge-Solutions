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
const int N=5010,D=105,INF=0x7f7f7f7f;
namespace G{
	const int N=::N<<2,E=((::N<<1/*in->t'*/)+(::N<<1/*s'->ou*/)+(::N<<1/*ou->t*/)+(::N<<3/*sam*/))<<1;//cout
	int to[E],bro[E],cap[E],head[N],e=0,n=0;
	inline int nn(){
		assert(n<N);
		return ++n;
	}
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int c){
		assert(e<E);
		to[e]=v,bro[e]=head[u],cap[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,0);
	}
	int que[N],dis[N],cur[N];
	inline void bfs(int s,int t){
		memset(dis+1,-1,n*sizeof(dis[0]));
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=cur[x]=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]==-1){
					dis[v]=dis[x]+1,que[qt++]=v;
				}
			}
		}
	}
	int aug(int x,int t,int a){
		if(x==t||a==0)return a;
		int r=a,d;
		for(int &i=cur[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+1){
				d=aug(v,t,min(cap[i],r));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	inline int dinic(int s,int t){
		int flow=0;
		for(;bfs(s,t),dis[t]!=-1;flow+=aug(s,t,INF));
		return flow;
	}
}
namespace sam{
	const int N=::N<<1;
	int lnk[N],go[N][D],len[N],n=0;
	inline void init(){
		memset(lnk,0,sizeof(lnk));
		memset(go,0,sizeof(go));
	}
	inline int nn(){
		return ++n;
	}
	inline int ext(int p,int c){
		int np=nn();
		len[np]=len[p]+1;
		for(;p&&go[p][c]==0;p=lnk[p]){
			go[p][c]=np;
		}
		if(p==0)return lnk[np]=1,np;
		int q=go[p][c];
		if(len[q]==len[p]+1)return lnk[np]=q,np;
		int nq=nn();
		memcpy(go[nq],go[q],sizeof(go[nq]));
		lnk[nq]=lnk[q],len[nq]=len[p]+1;
		lnk[q]=lnk[np]=nq;
		for(;p&&go[p][c]==q;p=lnk[p]){
			go[p][c]=nq;
		}
		return np;
	}
}
namespace trie{
	const int N=::N;
	int son[N][D],n=0,rt=0;
	inline int nn(int &x){
		return x=x?x:++n;
	}
	inline void init(){
		memset(son,0,sizeof(son));
		nn(rt);
	}
	inline void ins(int s[],int len){
		for(int i=1,x=1;i<=len;x=nn(son[x][s[i++]]));
	}
	int que[N],nd[N];
	inline void bfs(){
		sam::init();
		int qh=0,qt=0;
		nd[1]=sam::nn(),que[qt++]=1;
		while(qh<qt){
			int x=que[qh++];
			for(int i=0;i<D;i++){
				int s=son[x][i];
				if(s){
					nd[s]=sam::ext(nd[x],i);
					que[qt++]=s;
				}
			}
		}
	}
}
int s[N];
int nd_in[sam::N],nd_ou[sam::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("fri.in","r",stdin);
	freopen("fri.out","w",stdout);
#endif
	ni;
	trie::init();
	for(int tot=ni;tot--;){
		int len=ni;
		for(int i=1;i<=len;i++){
			s[i]=ni-1;
		}
		trie::ins(s,len);
	}
	trie::bfs();
	G::init();
	for(int x=1;x<=sam::n;x++){
		nd_in[x]=G::nn(),nd_ou[x]=G::nn();
	}
	int s=G::nn(),t=G::nn();
	int tse;
	for(int x=1;x<=sam::n;x++){
		if(x==1){
			tse=G::e;
			G::add(nd_in[x],nd_ou[x],INF);
		}else{
			/* choose */
			G::add(nd_ou[x],nd_in[1],1);
			/* with lower bound */
			G::add(nd_in[x],t,1);
			G::add(s,nd_ou[x],1);
		}
		using namespace sam;
		for(int c=0;c<D;c++){
			if(go[x][c]){
				G::add(nd_ou[x],nd_in[go[x][c]],1);
			}
		}
	}
	int f=G::dinic(s,t);
	if(f<sam::n-1){
		puts("0");
		return 0;
	}
	f=G::cap[tse^1];
	G::cap[tse]=0,G::cap[tse^1]=0;
	printf("%d\n",f-G::dinic(nd_in[1],nd_ou[1]));
	return 0;
}
