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
const int N=110;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int mxcnt[N];
int lst[N],ls=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dep[N];
	int dfs1(int x,int fa){
		int a=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dep[v]=dep[x]+1;
			int t=dfs1(v,x);
			if(dep[t]>dep[a]){
				a=t;
			}
		}
		return a;
	}
	bool dfs2(int x,int fa,int t){
		lst[++ls]=x;
		if(x==t)return true;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			if(dfs2(v,x,t))return true;
		}
		ls--;
		return false;
	}
	void dfs3(int x,int fa){
		int soncnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dep[v]=dep[x]+1;
			dfs3(v,x);
			++soncnt;
		}
		apmax(mxcnt[dep[x]],soncnt);
	}
}
inline lint calcans(int n){
	lint ans=1;
	for(int i=1;i<=n;i++){
		if(mxcnt[i]){
			ans*=mxcnt[i];
		}else break;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("freak.in","r",stdin);
	freopen("freak.out","w",stdout);
#endif
	const int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	const int a=(T::dep[1]=1,T::dfs1(1,0));
	const int b=(T::dep[a]=1,T::dfs1(a,0));
	T::dfs2(a,0,b);
	printf("%d ",(ls+1)>>1);
	lint ans=LINF;
	if(ls&1){
		const int rt=lst[(ls+1)>>1];
		mset(mxcnt+1,0,n);
		T::dep[rt]=1,T::dfs3(rt,0);
		apmin(ans,calcans(n));
		using namespace T;
		for(int i=head[rt],v;~i;i=bro[i]){
			v=to[i];
			mset(mxcnt+1,0,n);
			T::dep[rt]=1,T::dfs3(rt,v);
			T::dep[v]=1,T::dfs3(v,rt);
			apmin(ans,calcans(n)*2);
		}
	}else{
		const int rt1=lst[ls>>1],rt2=lst[(ls>>1)+1];
		mset(mxcnt+1,0,n);
		T::dep[rt1]=1,T::dfs3(rt1,rt2);
		T::dep[rt2]=1,T::dfs3(rt2,rt1);
		apmin(ans,calcans(n)*2);
	}
	printf("%lld\n",ans);
	return 0;
}
