#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010,E=400010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
struct XorSum{
	const static int N=64;
	int n,a[N];
	XorSum(){
		n=1;
		memset(a,0,sizeof(a));
	}
	inline friend XorSum operator ^ (const XorSum& a,lint b){
		XorSum c=a;
		for(int i=0;i<N;i++){
			if((b>>i)&1){
				c.a[i]=sub(a.n,c.a[i]);
			}
		}
		return c;
	}
	inline void operator += (const XorSum& b){
		apadd(n,b.n);
		for(int i=0;i<N;i++){
			apadd(a[i],b.a[i]);
		}
	}
	inline int eval(){
		int ans=0,pow2=1;
		for(int i=0;i<N;i++,apmul(pow2,2)){
			apadd(ans,mul(a[i],pow2));
		}
		return ans;
	}
};
namespace LB{
	const static int N=64;
	lint a[N];
	inline void init(){
		memset(a,0,sizeof(a));
	}
	inline bool add(lint x){
		for(int i=N-1;x;i--){
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					return true;
				}
			}
		}
		return false;
	}
	inline XorSum ask(){
		XorSum ans;
		for(int i=N-1;i>=0;i--){
			if(a[i]){
				ans+=ans^a[i];
			}
		}
		return ans;
	}
};
int n;
namespace G{
	int vis[N],head[N],to[E],bro[E],e=0,tim=0;
	lint val[E],dis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v,lint w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,lint w){
		ae(u,v,w),ae(v,u,w);
	}
	int que[N],qtail=0;
	void dfs(int x){
		vis[x]=tim;
		que[qtail++]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]]){
				assert(vis[v]==tim);
				LB::add(dis[x]^dis[v]^val[i]);
			}else{
				dis[v]=dis[x]^val[i];
				dfs(v);
			}
		}
	}
	inline int solve(int x){
		tim++,qtail=0,LB::init(),G::dfs(x);
		XorSum lb=LB::ask(),ans,S=lb^dis[que[0]];
		for(int i=1;i<qtail;i++){
			if(vis[que[i]]==tim){
				ans+=S^G::dis[que[i]];
				S+=lb^G::dis[que[i]];
			}
		}
		return ans.eval();
	}
}
int main(){
	n=ni;
	G::init();
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::add(u,v,nl);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(G::vis[i]==0){
			apadd(ans,G::solve(i));
		}
	}
	printf("%d\n",ans);
}