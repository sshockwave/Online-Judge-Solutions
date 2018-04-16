#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <algorithm>
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=260;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace G{
	const int N=::N*::N,E=::N*::N*::N+::N*::N*2;
	int to[E],bro[E],head[N],e,n;
	lint val[E];
	inline int nn(){
		return ++n,head[n]=-1,n;
	}
	inline void init(){
		e=n=0;
	}
	inline void ae(int u,int v,lint w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	struct Stat{
		int x;
		lint d;
		inline friend bool operator < (const Stat &a,const Stat &b){
			return a.d>b.d;
		}
	};
	lint dis[N];
	inline void dij(int s){
		memset(dis+1,127,n*sizeof(dis[0]));
		priority_queue<Stat>q;
		q.push((Stat){s,dis[s]=0});
		while(!q.empty()){
			int x=q.top().x;
			lint d=q.top().d;
			q.pop();
			if(d>dis[x])continue;
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>dis[x]+val[i]){
					q.push((Stat){v,dis[v]=dis[x]+val[i]});
				}
			}
		}
	}
}
struct Pt{
	int x,y;
	inline lint d2(){
		return (lint)x*x+(lint)y*y;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
}pt[N];
struct Disk{
	int rad,cost;
}disk[N];
inline bool circ_cmp(const Disk &a,const Disk &b){
	return a.rad<b.rad;
}
int nd[N][N];
inline void Main(){
	G::init();
	int n=ni,m=ni,w=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1;i<=m;i++){
		disk[i]=(Disk){ni,ni};
	}
	sort(disk+1,disk+m+1,circ_cmp);
	for(int i=1,ti=m,&j=m=0;i<=ti;i++){
		for(;j&&disk[j].cost>=disk[i].cost;--j);
		disk[++j]=disk[i];
	}
	int s=G::nn(),t=G::nn();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			nd[i][j]=G::nn();
			if(j>1){
				G::ae(nd[i][j-1],nd[i][j],disk[j].cost-disk[j-1].cost);
			}
			if(cabs(pt[i].y)<=disk[j].rad){
				G::ae(s,nd[i][j],disk[j].cost);
			}
			if(cabs(pt[i].y-w)<=disk[j].rad){
				G::ae(nd[i][j],t,0);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			lint d2=(pt[i]-pt[j]).d2();
			for(int k=m,p=1;k>=1;k--){
				for(;p<=m&&d2>sqr((lint)disk[k].rad+disk[p].rad);p++);
				if(p>m)break;
				G::ae(nd[i][k],nd[j][p],disk[p].cost);
			}
		}
	}
	G::dij(s);
	if(G::dis[t]==LINF){
		puts("impossible");
	}else{
		printf("%lld\n",G::dis[t]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rivpile.in","r",stdin);
	freopen("rivpile.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
