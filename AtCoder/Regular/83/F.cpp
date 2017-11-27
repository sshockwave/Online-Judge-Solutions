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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=200010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int nlst[N],ns,ecnt;
int fac[N],invfac[N];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
namespace G{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int size[N],ringe;
	int edg[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void getring(int x){
		nlst[++ns]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			ecnt++;
			if((v=to[i])!=edg[x]){
				if(edg[v]){
					if(ringe==-1){
						ringe=i;
					}else if(to[ringe]!=x){
						ringe=-2;
					}
				}else{
					edg[v]=x;
					getring(v);
				}
			}
		}
	}
	int dfs(int x){
		size[x]=1;
		lint ans=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])<edg[x]){
				ans=ans*dfs(v)%O;
				ans=ans*invfac[size[v]]%O;
				size[x]+=size[v];
			}
		}
		return ans*fac[size[x]-1]%O;
	}
}
int deg[N];
inline int work2(){
	using namespace G;
	for(int i=1;i<=ns;i++){
		int x=nlst[i];
		deg[x]=0;
	}
	for(int t=1;t<=ns;t++){
		int x=nlst[t];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])<edg[x]){
				deg[v]++;
			}
		}
	}
	lint ans=fac[ns];
	for(int t=1;t<=ns;t++){
		int x=nlst[t];
		if(deg[x]==0){
			ans=ans*dfs(x)%O;
			ans=ans*invfac[size[x]]%O;
		}
	}
	return ans;
}
inline int work(int x){//kind*invfac[n]
	using namespace G;
	ns=0,ecnt=0;
	ringe=-1;
	edg[x]=-1;
	getring(x);
	if((ecnt>>1)!=ns)return 0;
	assert(ringe>=0);
	for(int p=to[ringe],q=to[ringe^1];~p;swap(edg[p],q),swap(p,q));
	int ans=work2();
	for(int p=to[ringe^1],q=to[ringe],tp=p;swap(edg[p],q),swap(p,q),p!=tp;);
	return (lint)invfac[ns]*(ans+work2())%O;
}
inline int Main(){
	int n=ni,n2=n<<1;
	G::init();
	for(int i=1;i<=n2;i++){
		G::add(ni,n+ni);
	}
	gmath(n<<1);
	lint ans=fac[n<<1];
	memset(G::edg,0,sizeof(G::edg));
	memset(G::size,0,sizeof(G::size));
	for(int i=1;i<=n2;i++){
		if(G::edg[i]==0){
			(ans*=work(i))%=O;
			if(ans==0)return 0;
		}
	}
	return ans;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
