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
	neg&&(c=getchar());
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1010,O=1000000007;
int s1,s2;
int pval[N];
lint ans=0;
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
	int f[N];
	void dfs(int x,int fa){
		f[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				f[x]=(lint)f[x]*(f[v]+1)%O;
			}
		}
		if((s1|pval[x])==pval[x]&&(pval[x]|s2)==s2){
			ans+=f[x];
		}else{
			f[x]=0;
		}
	}
}
namespace sieve{
	const int N=55;
	int pri[N],ps=0;
	bool np[N];
	inline void main(int n){
		mset(np+1,0,n);
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p==0)break;
			}
		}
	}
}
int dfs(int x,int a,int b){
	assert((a|b)==b);
	if(x==sieve::ps){
		s1=a,s2=b;
		ans=0;
		T::dfs(1,0);
		return ans%O;
	}
	int ans=dfs(x+1,a,b);
	if(((a^b)>>x)&1){
		ans=((lint)ans+O-dfs(x+1,a|(1<<x),b)+O-dfs(x+1,a,b^(1<<x)))%O;
	}
	return ans;
}
inline int hush(lint x){
	int a=0;
	for(int i=0;i<sieve::ps;i++){
		if(x%sieve::pri[i]==0){
			a|=1<<i;
		}
	}
	return a;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	sieve::main(50);
	int n=ni;
	s1=hush(next_num<lint>()),s2=hush(next_num<lint>());
	for(int i=1;i<=n;i++){
		pval[i]=hush(next_num<lint>());
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	printf("%d\n",dfs(0,s1,s2));
	return 0;
}
