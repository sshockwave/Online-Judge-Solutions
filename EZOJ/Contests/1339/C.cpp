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
const int N=1000010,MOD=1000000007;
inline int fpow(int x,int n){
	lint ret=1;
	for(;n;n>>=1,x=(lint)x*x%MOD){
		if(n&1){
			(ret*=x)%=MOD;
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
bool np[N];
int prime[N],ps=0;
int phi[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				phi[i*cur]=phi[i]*cur;
				break;
			}else{
				phi[i*cur]=phi[i]*(cur-1);
			}
		}
	}
}
int a[N];
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
	int dfs(int x,int fa,int rt,int dep){
		lint ans=(lint)phi[a[x]*a[rt]]*dep%MOD;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				ans+=dfs(v,x,rt,dep+1);
			}
		}
		return ans%MOD;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	sieve(n*n);
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=T::dfs(i,0,i,0);
	}
	printf("%lld\n",ans%MOD*inv(n*(n-1))%MOD);
	return 0;
}
