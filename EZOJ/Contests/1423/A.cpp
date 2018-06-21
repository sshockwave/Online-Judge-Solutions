#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
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
const int N=100010,INF=0x7f7f7f7f;
struct Query{
	int h,full;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.h<b.h;
	}
};
typedef vector<Query>vq;
vq qry[N<<1],qry2[N<<1];
namespace T{
	const int N=::N<<1,E=N;
	int to[E],bro[E],head[N],e=0,n=0;
	inline int nn(){
		return ++n,qry[n].clear(),qry2[n].clear(),head[n]=-1,n;
	}
	inline void init(){
		e=0,n=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int hei[N];
	int f[N],g[N];
	int stk[N],ss=0;
	void dfs(int x){
		stk[++ss]=x;
		if(head[x]==-1){
			for(vq::iterator it=qry[x].begin(),ti=qry[x].end();it!=ti;it++){
				int l=1,r=ss;
				while(l<r){
					int m=((l+r)>>1)+1;
					if(it->h<hei[stk[m]]){
						l=m;
					}else{
						r=m-1;
					}
				}
				qry2[stk[l]].push_back(*it);
			}
		}
		f[x]=0,g[x]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]),f[x]+=f[v],g[x]+=g[v];
		}
		assert(f[x]<=g[x]);
		vq::iterator it=qry2[x].begin(),ti=qry2[x].end();
		sort(it,ti);
		for(vq::iterator i=it;i!=ti;i++){
			f[x]+=!i->full;
			g[x]+=!i->full;
		}
		assert(f[x]<=g[x]);
		for(vq::iterator i=it,j=it;i!=ti;i=j){
			for(;j!=ti&&j->h==i->h;j++){
				if(j->full){
					f[x]++;
				}else{
					f[x]--;
				}
			}
			apmax(g[x],f[x]);
		}
		ss--;
	}
}
using T::hei;
int stk[N],ss;
inline void psh(int x,int h){
	stk[++ss]=x;
	while(hei[stk[ss]]<h){
		assert(ss>1);
		int l=ss;
		for(;hei[stk[l-1]]==hei[stk[ss]];l--);
		x=T::nn();
		hei[x]=min(hei[stk[l-1]],h);
		for(;ss>=l;T::ae(x,stk[ss--]));
		stk[++ss]=x;
	}
}
int nd[N];
inline int Main(){
	int n=ni,tot=ni;
	hei[stk[ss=0]=0]=INF;
	T::init();
	for(int i=1;i<n;i++){
		nd[i]=T::nn();
		int a=ni;
		hei[nd[i]]=min(a,hei[stk[ss]]);
		psh(nd[i],a);
	}
	{
		nd[n]=T::nn();
		int a=INF;
		hei[nd[n]]=hei[stk[ss]];
		psh(nd[n],a);
	}
	assert(ss==1);
	while(tot--){
		int x=ni;
		qry[nd[x]].push_back((Query){ni,ni});
	}
	T::dfs(stk[1]);
	return T::g[stk[1]];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tank.in","r",stdin);
	freopen("tank.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
