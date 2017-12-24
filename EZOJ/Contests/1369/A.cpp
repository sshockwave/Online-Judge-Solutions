#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
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
const int N=100010;
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
	int gdep(int x,int fa){
		int dep=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				apmax(dep,gdep(v,x)+1);
			}
		}
		return dep;
	}
	int ans;
	int dfs(int x,int fa,int mxlen){
		int len=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				apmax(len,dfs(v,x,mxlen)-1);
			}
		}
		return len==0?ans++,mxlen:len;
	}
}
int ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	int mxdep=T::gdep(1,0);
	memset(ans,-1,sizeof(ans));
	for(int tot=ni;tot--;){
		if(clock()>CLOCKS_PER_SEC){
			puts("0");
			continue;
		}
		int k=min(ni,mxdep);
		if(ans[k]==-1){
			T::ans=0,T::dfs(1,0,k),ans[k]=T::ans;
		}
		printf("%d\n",ans[k]);
	}
	return 0;
}
