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
const int N=100010;
int pval[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	int f[E],g[E];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs1(int x,int fa){
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs1(v,x);
				f[i]=0;
				int maxsw=0;
				for(int j=head[v];~j;j=bro[j]){
					if(to[j]!=x){
						f[i]+=max(f[j],0);
						apmax(maxsw,g[j]-max(f[j],0));
					}
				}
				g[i]=f[i]+maxsw+pval[v]-val[i];
				f[i]+=pval[v]-(val[i]<<1);
			}
		}
	}
	void dfs2(int x,int fa){
		int sumf=0,g1=-1,g2=-1;
		for(int i=head[x];~i;i=bro[i]){
			sumf+=max(f[i],0);
			if(g1==-1||g[i]-max(f[i],0)>g[g1]-max(f[g1],0)){
				g2=g1,g1=i;
			}else if(g2==-1||g[i]-max(f[i],0)>g[g2]-max(f[g2],0)){
				g2=i;
			}
		}
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]!=fa){
				int e=i^1;
				f[e]=sumf-max(f[i],0)+pval[x]-(val[i]<<1);
				if(g1!=i){
					g[e]=sumf-max(f[i],0)+max(0,g[g1]-max(f[g1],0))+pval[x]-val[i];
				}else{
					g[e]=sumf-max(f[i],0)+max(0,g[g2]-max(f[g2],0))+pval[x]-val[i];
				}
				dfs2(to[i],x);
			}
		}
	}
	inline int calc(int x){
		int sumf=0,maxsw=0;
		for(int i=head[x];~i;i=bro[i]){
			sumf+=max(f[i],0);
			apmax(maxsw,g[i]-max(f[i],0));
		}
		return sumf+maxsw+pval[x];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
#endif
	T::init();
	int n=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,ni);
	}
	T::dfs1(1,0),T::dfs2(1,0);
	for(int i=1;i<=n;i++){
		printf("%d\n",T::calc(i));
	}
	return 0;
}
