#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
const int N=1000010;
int pval[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int f[E];
	void dfs(int x,int fa){
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				int j=v<x?i^1:i;
				if(pval[v]>0){
					f[j]=pval[v],f[j^1]=0;
				}else{
					f[j]=0,f[j^1]=-pval[v];
				}
				pval[x]-=pval[v],pval[v]=0;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1,0);
	int ans=0;
	for(int x=1;x<=n;x++){
		assert(pval[x]==0);
		using namespace T;
		for(int i=head[x];~i;i=bro[i]){
			pval[x]+=f[i]-f[i^1];
		}
		if(pval[x]>0){
			ans+=pval[x];
		}
	}
	printf("%d\n",ans);
	for(int i=1,j=1;i<=n;i++){
		while(pval[i]>0){
			for(;pval[j]>=0;j++);
			pval[i]--,pval[j]++;
			printf("%d %d\n",i,j);
		}
	}
	return 0;
}
