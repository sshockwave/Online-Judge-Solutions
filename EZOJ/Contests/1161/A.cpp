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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=200010,INF=0x7f7f7f7f;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int len,cnt;
	bool vis[N];//all set
	int dfs(int x,int f){
		int mxdep=0,mndep=INF;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=f){
				int t=dfs(v,x)+1;
				if(vis[v]) apmin(mndep,t);
				else apmax(mxdep,t);
			}
		}
		if(mxdep==len){
			cnt++,vis[x]=true;
			return -len;
		}
		if(mndep<=0){
			vis[x]=mxdep+mndep<=0;
			return vis[x]?mndep:mxdep;
		}
		vis[x]=false;
		return mxdep;
	}
}
inline bool check(int m){
	T::len=m,T::cnt=0;
	T::dfs(1,0);
	if(!T::vis[1]){
		T::cnt++;
	}
	return T::cnt<=2;
}
inline int Main(){
	int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	int l=0,r=n-1;
	while(l<r){
		int m=(l+r)>>1;
		if(check(m)){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("station.in","r",stdin);
	freopen("station.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
