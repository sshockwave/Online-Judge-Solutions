#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef vector<int>vi;
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=1010,INF=0x7f7f7f7f;
int lnk[N];
namespace G{
	const int E=(::N*::N/4+::N)*2;
	int to[E],bro[E],cap[E],head[N],e=0,n,s,t;
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
	int dis[N],cur[N],que[N];
	inline void bfs(){
		memset(dis+1,127,n*sizeof(dis[0]));
		int qh=0,qt=0;
		dis[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
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
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	inline int dinic(){
		int flow=0;
		for(;bfs(),dis[t]<INF;flow+=aug(s,INF));
		memset(lnk,0,sizeof(lnk));
		for(int i=head[s],x;~i;i=bro[i]){
			assert(to[i]>=1&&to[i]<s);
			if(cap[i])continue;
			for(int j=head[x=to[i]],v;~j;j=bro[j]){
				if(to[j]==s){
					assert(cap[j]);
				}
				if(cap[j]==0){
					lnk[x]=v=to[j],lnk[v]=x;
					break;
				}
			}
			assert(lnk[x]);
		}
		return flow;
	}
}
struct Pt{
	int x,y;
	inline lint d2(){return sqr<lint>(x)+sqr<lint>(y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
}pt[N];
int tp[N];
inline bool xcmp(int a,int b){
	return pt[a].x!=pt[b].x?pt[a].x<pt[b].x:pt[a].y<pt[b].y;
}
int lst[N],ls;
inline void getConvex(const vi &vec){//from zero stored in lst
	ls=0;
	for(vi::const_iterator it=vec.begin(),ti=vec.end();it!=ti;++it){
		int x=*it;
		for(;ls>=2&&crs(pt[x]-pt[lst[ls-2]],pt[x]-pt[lst[ls-1]])>0;ls--);
		lst[ls++]=x;
	}
	static int lst2[N];
	int ls2=0;
	for(vi::const_iterator it=vec.begin(),ti=vec.end();it!=ti;++it){
		int x=*it;
		for(;ls2>=2&&crs(pt[x]-pt[lst2[ls2-2]],pt[x]-pt[lst2[ls2-1]])<0;ls2--);
		lst2[ls2++]=x;
	}
	assert(lst[0]==lst2[0]);
	assert(lst[ls-1]==lst2[ls2-1]);
	for(int i=ls2-2;i>=1;i--){
		lst[ls++]=lst2[i];
	}
}
vi con[N],waitlst[N];
set<int>waiting[N];
bool vis[N];
int que[N],qh=0,qt=0;
bool inque[N];
inline void pshque(int x){
	if(inque[x])return;
	inque[x]=true;
	que[qt++]=x;
	if(qt==N){
		qt=0;
	}
}
inline int gnxt(int x){
	return x<ls-1?x+1:0;
}
int outputcnt=0;
inline void proc_waitlst(int x){
	for(vi::iterator it=waitlst[x].begin(),ti=waitlst[x].end();it!=ti;++it){
		waiting[*it].erase(x);
		if(waiting[*it].size()==0){
			pshque(*it);
		}
	}
}
inline void work(int x){
	assert(waiting[x].empty());
	assert(lnk[x]);
	assert(con[x].size());
	{
		vi tmp;
		for(vi::iterator it=con[x].begin(),ti=con[x].end();it!=ti;++it){
			if(!vis[*it]){
				tmp.push_back(*it);
			}
		}
		con[x]=tmp;
	}
	assert(con[x].size());
	getConvex(con[x]);
	assert(ls);
	if(ls==1){
		assert(lnk[lst[0]]==x);
		assert(lnk[x]==lst[0]);
		vis[lnk[x]]=true;
		++outputcnt,printf("%d %d\n",x,lnk[x]);
		proc_waitlst(x);
		return;
	}
	int i=0,pr=ls-1,nx=1;
	vi conv;
	for(;;i++,pr=gnxt(pr),nx=gnxt(nx)){
		assert(i<ls);
		const Pt &a=pt[lst[pr]],&b=pt[lst[i]],&c=pt[lst[nx]];
		if(crs(b-pt[x],c-b)>0&&crs(b-pt[x],b-a)<0)break;
	}
	for(;;i=gnxt(i),pr=gnxt(pr),nx=gnxt(nx)){
		if(lnk[lst[i]]==0||lnk[lst[i]]==x){
			lnk[lnk[x]]=0,lnk[x]=lst[i],lnk[lst[i]]=x,vis[lnk[x]]=true;
			++outputcnt,printf("%d %d\n",x,lnk[x]);
			proc_waitlst(x);
			return;
		}
		conv.push_back(lst[i]);
		{
			int y=lnk[lst[i]];
			assert(y);
			if(waiting[y].find(x)!=waiting[y].end()){
				swap(lnk[x],lnk[y]);
				lnk[lnk[x]]=x,lnk[lnk[y]]=y;
				vis[lnk[x]]=true;
				++outputcnt,printf("%d %d\n",x,lnk[x]);
				{//cout
					bool flag=false;
					for(vi::iterator it=con[y].begin();it!=con[y].end();++it){
						if(*it==lnk[y]){
							flag=true;
							break;
						}
					}
					assert(flag);
				}
				waiting[y].clear();
				proc_waitlst(x);
				return;
			}
		}
		const Pt &a=pt[lst[pr]],&b=pt[lst[i]],&c=pt[lst[nx]];
		if(crs(b-pt[x],c-b)<0&&crs(b-pt[x],b-a)>0)break;
	}
	waiting[x].clear();
	for(vi::iterator it=conv.begin(),ti=conv.end();it!=ti;++it){
		waitlst[lnk[*it]].push_back(x);
		waiting[x].insert(lnk[*it]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("etoile.in","r",stdin);
	freopen("etoile.out","w",stdout);
#endif
	const int n=ni;
	const lint r=sqr(next_num<lint>()),d=sqr(next_num<lint>());
	ls=0;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		if((pt[i]-pt[1]).d2()<=r){
			tp[i]=2;
			lst[++ls]=i;
		}else{
			tp[i]=1;
		}
	}
	sort(lst+1,lst+ls+1,xcmp);
	G::init();
	G::s=n+1,G::t=n+2,G::n=n+2;
	for(int i=1;i<=n;i++){
		if(tp[i]==2){
			G::add(i,G::t,1);
			continue;
		}
		G::add(G::s,i,1);
		for(int j=1;j<=ls;j++){
			if((pt[i]-pt[lst[j]]).d2()<=d){
				con[i].push_back(lst[j]);
				G::add(i,lst[j],1);
			}
		}
	}
	int flow=G::dinic();
	memset(vis,0,sizeof(vis));
	printf("%d\n",flow<<1);
	for(int i=1;i<=n;i++){
		if(tp[i]==1&&lnk[i]){
			pshque(i);
		}
	}
	while(qh<qt){
		int x=que[qh++];
		inque[x]=false;
		if(qh==N){
			qh=0;
		}
		work(x);
	}
	assert(outputcnt==flow);
	return 0;
}
