#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1010,E=N<<1,INF=0x7f7f7f7f;
int st[N<<1],len[N<<1];
inline int dis(const int a,const int b){
	const int t=st[b]-(st[a]+len[a])%24;
	return t<0?t+24:t;
}
int pe[N][2][2];
int nx[N<<1];
int fa[N<<1];
inline int grt(int x){
	return fa[x]?fa[x]=grt(fa[x]):x;
}
inline void mg(int u,int v){
	u=grt(u),v=grt(v);
	if(u!=v){
		fa[u]=v;
	}
}
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}edg[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("yist.in","r",stdin);
	freopen("yist.out","w",stdout);
#endif
	const int n=ni;
	int ans=0;
	memset(pe,0,sizeof(pe));
	for(int i=1;i<=n*2;i++){
		const int u=(i+1)>>1,v=ni;
		if(pe[u][0][0]==0){
			pe[u][0][0]=i;
		}else{
			assert(pe[u][0][1]==0);
			pe[u][0][1]=i;
		}
		if(pe[v][1][0]==0){
			pe[v][1][0]=i;
		}else{
			assert(pe[v][1][1]==0);
			pe[v][1][1]=i;
		}
		st[i]=ni;
		ans+=len[i]=ni;
	}
	int es=0;
	mset(fa+1,0,n*2);
	{//i==1
		const int (*const e)[2]=pe[1];
		const int val0=min(st[e[0][1]]+dis(e[1][0],e[0][0]),st[e[0][0]]+dis(e[1][1],e[0][1]));
		const int val1=min(st[e[0][0]]+dis(e[1][0],e[0][1]),st[e[0][1]]+dis(e[1][1],e[0][0]));
		if(val0<val1){
			mg(e[1][0],e[0][0]),mg(e[1][1],e[0][1]);
		}else{
			mg(e[1][0],e[0][1]),mg(e[1][1],e[0][0]);
		}
		ans+=min(val0,val1);
		edg[++es]=(Edge){e[0][0],e[0][1],max(val0,val1)-min(val0,val1)};
	}
	for(int i=2;i<=n;i++){
		const int (*const e)[2]=pe[i];
		const int val0=dis(e[1][0],e[0][0])+dis(e[1][1],e[0][1]);
		const int val1=dis(e[1][0],e[0][1])+dis(e[1][1],e[0][0]);
		if(val0<val1){
			mg(e[1][0],e[0][0]),mg(e[1][1],e[0][1]);
		}else{
			mg(e[1][0],e[0][1]),mg(e[1][1],e[0][0]);
		}
		ans+=min(val0,val1);
		edg[++es]=(Edge){e[0][0],e[0][1],max(val0,val1)-min(val0,val1)};
	}
	sort(edg+1,edg+es+1);
	for(int i=1;i<=es;i++){
		const int u=edg[i].u,v=edg[i].v;
		if(grt(u)==grt(v))continue;
		ans+=edg[i].w;
		mg(u,v);
	}
	printf("%d\n",ans);
	return 0;
}
