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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=200010,INF=0x7f7f7f7f;
namespace T{
	const int E=N<<2;
	int to[E],bro[E],dhead[N],mhead[N],e=0;
	inline void init(){
		memset(dhead,-1,sizeof(dhead));
		memset(mhead,-1,sizeof(mhead));
	}
	inline void ae(int u,int v,int *head){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v,int *head){
		ae(u,v,head),ae(v,u,head);
	}
	int fa[N],dep[N],hei[N];
	void dfs(int x){
		hei[x]=0;
		for(int i=mhead[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dep[v]=dep[x]+1;
				dfs(v);
				apmax(hei[x],hei[v]+1);
			}
		}
	}
}
namespace Subtask1{
	const int N=1010;
	int f[N][N][2];//0:deer 1:man
	inline void init(){
		memset(f,-1,sizeof(f));
	}
	int F(int x,int y,bool d){
		if(x==y){
			return 0;
		}
		if(f[x][y][d]>=0){
			return f[x][y][d];
		}
		if(f[x][y][d]==-2){
			throw -1;
		}
		f[x][y][d]=-2;
		int ans=d?INF:0;
		for(int i=d?T::mhead[y]:T::dhead[x];~i;i=T::bro[i]){
			if(d){
				apmin(ans,F(x,T::to[i],0));
			}else{
				apmax(ans,F(T::to[i],y,1));
			}
		}
		return f[x][y][d]=ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("deer.in","r",stdin);
	freopen("deer.out","w",stdout);
#endif
	int n=ni,x=ni,y=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni,T::dhead);
	}
	for(int i=1;i<n;i++){
		T::add(ni,ni,T::mhead);
	}
	T::dep[y]=1,T::dfs(y);
	int ans=0;
	for(int i=x;T::dep[i]-1>T::dep[x]-T::dep[i];i++){
		apmax(ans,T::dep[x]-T::dep[i]+T::hei[i]+(T::dep[i]-1-(T::dep[x]-T::dep[i])));
	}
	printf("%d\n",ans<<1);
	return 0;
}
