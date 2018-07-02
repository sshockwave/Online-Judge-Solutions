#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=410;
struct Pt{
#define Pt(x,y) ((Pt){x,y})
	int x,y;
	inline int d2(){return x*x+y*y;}
	inline friend Pt operator + (const Pt &a,const Pt &b){return Pt(a.x+b.x,a.y+b.y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return Pt(a.x-b.x,a.y-b.y);}
}pt[N];
inline int d2(int a,int b){
	return (pt[a]-pt[b]).d2();
}
set<int>to[N];
inline void lnk(int u,int v){
	to[u].insert(v),to[v].insert(u);
}
inline void cut(int u,int v){
	to[u].erase(v),to[v].erase(u);
}
int dis[N];
bool vis[N];
int dfs(int x,int t){
	int ans=x;
	vis[x]=true;
	for(set<int>::iterator it=to[x].begin(),ti=to[x].end();it!=ti;++it){
		const int v=*it;
		if(vis[v])continue;
		const int b=dfs(v,t);
		if(d2(b,t)<d2(ans,t)){
			ans=b;
		}
	}
	vis[x]=false;
	return ans;
}
inline void Main(const int n){
	for(int i=1;i<=n;i++){
		pt[i]=Pt(ni,ni);
		to[i].clear();
	}
	//input complete
	for(int i=1;i<n;i++){
		lnk(i,i+1);
	}
	if(n==1)return;
	for(int tot=50;tot--;){
		static int cnt[N],aff[N];
		mset(cnt+1,0,n);
		mset(aff+1,0,n);
		for(int i=1;i<=n;i++){
			dis[i]=0;
			for(set<int>::iterator it=to[i].begin(),ti=to[i].end();it!=ti;++it){
				apmax(dis[i],d2(i,*it));
			}
			for(int j=1;j<=n;j++){
				if(d2(i,j)<=dis[i]){
					++cnt[j],++aff[i];
				}
			}
		}
		int mxp=1;
		for(int i=2;i<=n;i++){
			if(cnt[i]>cnt[mxp]){
				mxp=i;
			}
		}
		int mxd=mxp!=1?1:2;
		for(int i=1;i<=n;i++){
			if(i==mxp)continue;
			if(aff[i]>aff[mxd]){
				mxd=i;
			}
		}
		int v;
		for(set<int>::iterator it=to[mxd].begin(),ti=to[mxd].end();it!=ti;++it){
			if(dis[mxd]==d2(mxd,*it)){
				v=*it;
			}
		}
		cut(mxd,v);
		lnk(mxd,dfs(v,mxd));
	}
	for(int i=1;i<=n;i++){//output
		for(set<int>::iterator it=to[i].begin(),ti=to[i].end();it!=ti;++it){
			if(i<*it){
				printf("%d %d\n",i,*it);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chaw.in","r",stdin);
	freopen("chaw.out","w",stdout);
#endif
	int n;
	for(;scanf("%d",&n)!=EOF;){
		Main(n);
	}
	return 0;
}
