#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
namespace sieve{
	const int N=100010;
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
inline ull grand(){
	ull ans=0,pw=1;
	for(int i=0;i<4;i++,pw*=(ull)RAND_MAX+1){
		ans^=pw*rand();
	}
	return ans;
}
inline ull gph(int x){
	typedef map<int,ull>mp;
	static mp m;
	mp::iterator it=m.find(x);
	if(it!=m.end())return it->second;
	return m[x]=grand();
}
inline ull gh(int n){
	using sieve::pri;
	ull ans=0;
	for(int i=0,p;p=pri[i],p*p<=n;i++){
		int e=0;
		for(;n%p==0;n/=p,e^=1);
		if(e){
			ans^=gph(p);
		}
	}
	if(n>1){
		ans^=gph(n);
	}
	return ans;
}
map<ull,int>scnt;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	ull val[E];
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v,ull w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,ull w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs(int x,int fa,ull tort){
		++scnt[tort];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x,tort^val[i]);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hui.in","r",stdin);
	freopen("hui.out","w",stdout);
#endif
	sieve::main(sieve::N-1);
	int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v,gh(ni));
	}
	T::dfs(1,0,0);
	lint ans=0;
	for(map<ull,int>::iterator it=scnt.begin(),ti=scnt.end();it!=ti;++it){
		ans+=(lint)it->second*(it->second-1);
	}
	printf("%lld\n",ans);
	return 0;
}
