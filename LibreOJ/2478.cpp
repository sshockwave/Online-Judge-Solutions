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
const int N=300010;
lint c;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	struct Val{
		lint val;
		int cnt;
		inline Val form(){
			return (Val){val-c,cnt+1};
		}
		inline friend Val operator + (const Val &a,const Val &b){
			return (Val){a.val+b.val,a.cnt+b.cnt};
		}
		inline friend Val operator - (const Val &a,const Val &b){
			return (Val){a.val-b.val,a.cnt-b.cnt};
		}
		inline friend Val operator + (const Val &a,const int &b){
			return (Val){a.val+b,a.cnt};
		}
		inline friend bool operator < (const Val &a,const Val &b){
			return a.val!=b.val?a.val<b.val:a.cnt>b.cnt;
		}
	};
	Val f[N],g[N];//g:single-ended route
	void dfs(int x,int fa){
		f[x]=(Val){0,0};
		Val mx1=(Val){0,0},mx2=(Val){0,0};
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				f[x]=f[x]+f[v];
				Val tmp=g[v]+val[i]-f[v];
				if(mx1<tmp){
					mx2=mx1,mx1=tmp;
				}else if(mx2<tmp){
					mx2=tmp;
				}
			}
		}
		g[x]=f[x];
		apmax(g[x],f[x]+mx1);
		apmax(f[x],(f[x]+mx1+mx2).form());
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	int n=ni,k=ni+1;
	T::init();
	lint sum=0;
	for(int i=1;i<n;i++){
		int u=ni,v=ni,w=ni;
		T::add(u,v,w);
		sum+=w>=0?w:-w;
	}
	lint l=-sum-1,r=sum+1;
	while(l<r){
		c=l+(r-l)/2;
		T::dfs(1,0);
		if(T::f[1].cnt>k){
			l=c+1;
		}else{
			r=c;
		}
	}
	c=l;
	T::dfs(1,0);
	printf("%lld\n",T::f[1].val+c*k);
	return 0;
}
