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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=55,INF=0x7f7f7f7f;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	int f[E][N][N],ccnt[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(f,-1,sizeof(f));
		memset(ccnt,0,sizeof(ccnt));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int tmp[E][N][N][N];
	int F(int e,int in,int out){
		if(~f[e][in][out]){
			return f[e][in][out];
		}
		int &ans=f[e][in][out];
		if(bro[head[to[e]]]==-1){
			return ans=out?F(e^1,out,0)+val[e]:0;
		}
		assert(in);
		int *g=tmp[e][in][out];
		g[0]=INF;
		memset(g+1,0,in<<2);
		for(int i=head[to[e]];~i;i=bro[i]){
			if(i^e^1){
				for(int j=in;j>=1;j--){
					for(int k=1;k<=j;k++){
						apmax(g[j],min(g[j-k],F(i,k,in+out-k)+val[i]));
					}
				}
			}
		}
		return ans=g[in];
	}
	void dfs(int x,int fa){
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				ccnt[x]+=ccnt[v];
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("policeman.in","r",stdin);
	freopen("policeman.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1,u,v;i<n;u=ni,v=ni,T::add(u,v,ni),i++);
	int s=ni,m=ni;
	for(int i=1;i<=m;T::ccnt[ni]++,i++);
	m-=T::ccnt[s];
	T::dfs(s,0);
	int ans=INF;
	for(int i=T::head[s];~i;i=T::bro[i]){
		using namespace T;
		if(ccnt[to[i]]){
			apmin(ans,F(i,ccnt[to[i]],m-ccnt[to[i]])+val[i]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
