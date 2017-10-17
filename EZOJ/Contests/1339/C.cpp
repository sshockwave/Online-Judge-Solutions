#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=200010,O=1000000007;
inline int fpow(int x,int n){
	lint ret=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			(ret*=x)%=O;
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,O-2);
}
bool np[N];
int prime[N],ps=0;
int phi[N],invnum[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	phi[1]=invnum[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
		}
		invnum[i]=(O-(lint)O/i*invnum[O%i]%O)%O;
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
int a[N],ida[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int dfn[N],dep[N],ett[N<<1][20],lg[N<<1],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	inline int mindep(int u,int v){
		return dep[u]<dep[v]?u:v;
	}
	inline int maxdep(int u,int v){
		return dep[u]>dep[v]?u:v;
	}
	inline bool dfscmp(int a,int b){
		return dfn[a]<dfn[b];
	}
	void dfs(int x){
		ett[dfn[x]=++tim][0]=x;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dep[v=to[i]]==0){
				dep[v]=dep[x]+1;
				dfs(v);
				ett[++tim][0]=x;
			}
		}
	}
	inline void prep(){
		for(int i=tim;i>=1;i--){
			for(int &j=lg[tim-i+1]=0;i+(1<<(j+1))-1<=tim;j++){
				ett[i][j+1]=mindep(ett[i][j],ett[i+(1<<j)][j]);
			}
		}
	}
	inline int lca(int u,int v){
		u=dfn[u],v=dfn[v];
		if(u>v){
			swap(u,v);
		}
		int j=lg[v-u+1];
		return mindep(ett[u][j],ett[v-(1<<j)+1][j]);
	}
}
namespace T2{
	const int E=N;
	int bro[N],head[N],tag[N],key[N],tim=0;
	lint ans=0;
	inline void ae(int u,int v){
		if(tag[u]<tim){
			tag[u]=tim,bro[v]=0,head[u]=v;
		}else{
			bro[v]=head[u],head[u]=v;
		}
	}
	struct pii{
		lint sum,prod;
	};
	pii dfs(int x,pii cur){
		cur.sum%=O,cur.prod%=O;
		pii sub=cur;
		if(key[x]==tim){
			ans+=cur.prod*phi[a[x]]%O;
			sub.sum+=phi[a[x]];
		}
		if(tag[x]==tim){
			for(int v=head[x];v;v=bro[v]){
				pii tmp=dfs(v,(pii){sub.sum,sub.sum*(T::dep[v]-T::dep[x])%O+sub.prod});
				sub.sum+=tmp.sum;
				sub.prod+=(tmp.prod+(T::dep[v]-T::dep[x])*tmp.sum%O)%O;
			}
		}
		return (pii){(sub.sum-cur.sum)%O,(sub.prod-cur.prod)%O};
	}
}
int f[N];
int lst[N],ls;
int stk[N],st;
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	sieve(n);
	for(int i=1;i<=n;i++){
		ida[a[i]=ni]=i;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dep[1]=1,T::dfs(1),T::prep();
	lint ans=0;
	for(int i=n;i>=1;i--){
		ls=st=0;
		T2::tim++,T2::ans=0;
		lint tmp=0;
		for(int j=i;j<=n;j+=i){
			tmp+=f[j];
			lst[ls++]=ida[j];
		}
		sort(lst,lst+ls,T::dfscmp);
		stk[st++]=1;
		for(int j=0;j<ls;j++){
			int u=lst[j],v=T::lca(stk[st-1],u);
			T2::key[u]=T2::tim;
			for(;T::dep[v]<T::dep[stk[st-1]];st--,T2::ae(T::maxdep(v,stk[st-1]),stk[st]));
			if(v!=stk[st-1]){
				stk[st++]=v;
			}
			if(u!=stk[st-1]){
				stk[st++]=u;
			}
		}
		for(;st>1;st--,T2::ae(stk[st-1],stk[st]));
		T2::dfs(1,(T2::pii){0,0});
		f[i]=(((T2::ans%O)<<1)+O-tmp%O)%O;
		ans+=(lint)f[i]*i%O*invnum[phi[i]]%O;
	}
	printf("%lld\n",ans%O*inv((lint)n*(n-1)%O)%O);
	return 0;
}
