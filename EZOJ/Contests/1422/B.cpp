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
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int vis[N],tim=0;
	inline void init(int n){
		mset(head+1,-1,n);
		mset(vis+1,0,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int f[N];
	inline bool test(int v){
		return (s1|v)==v&&(v|s2)==s2;
	}
	void dfs(int x){
		vis[x]=tim;
		f[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]]<tim&&test(pval[v])){
				dfs(v);
				f[x]=(lint)f[x]*(f[v]+1)%O;
			}
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
int lst[N];
int dfs(int x,int a,int b,int l,int r){
	if(l>r)return 0;
	assert((a|b)==b);
	if(x==sieve::ps){
		s1=a,s2=b;
		lint ans=0;
		++T::tim;
		for(int t=l;t<=r;t++){
			int i=lst[t];
			assert(T::test(pval[i]));
			if(T::vis[i]<T::tim){
				T::dfs(i);
			}
			ans+=T::f[i];
		}
		return ans%O;
	}
	int ans=dfs(x+1,a,b,l,r);
	if(((a^b)>>x)&1){
		int i=l,j=r;
		for(;;){
			for(;i<=r&&((pval[lst[i]]>>x)&1)==0;i++);
			for(;j>=l&&((pval[lst[j]]>>x)&1)==1;j--);
			if(i<=j){
				swap(lst[i],lst[j]);
			}else break;
		}
		int ans0=dfs(x+1,a,b^(1<<x),l,j);
		int ans1=dfs(x+1,a|(1<<x),b,i,r);
		ans=((lint)ans+O-ans0+O-ans1)%O;
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
		lst[i]=i;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	printf("%d\n",dfs(0,s1,s2,1,n));
	return 0;
}
