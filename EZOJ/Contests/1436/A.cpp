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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int col[N];
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	lint f[N][2];
	void dfs(int x,int fa){
		f[x][0]=f[x][1]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				{
					lint t=f[v][0];
					if(f[v][1]<LINF){
						apmin(t,f[v][1]+val[i]);
					}
					f[x][0]+=t;
				}
				{
					lint t=f[v][1];
					if(f[v][0]<LINF){
						apmin(t,f[v][0]+val[i]);
					}
					f[x][1]+=t;
				}
			}
		}
		if(col[x]!=-1){
			f[x][col[x]]=LINF;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,ni);
	}
	mset(col+1,-1,n);
	for(int tot=ni;tot--;){
		col[ni]=0;
	}
	for(int tot=ni;tot--;){
		col[ni]=1;
	}
	T::dfs(1,0);
	printf("%lld\n",min(T::f[1][0],T::f[1][1]));
	return 0;
}
