#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
const int N=110,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int deg[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(deg+1,0,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
		++deg[u],++deg[v];
	}
}
namespace solve1{
	inline int main(const int n){
		return (lint)(n-1)*inv_pow(2)%O;
	}
}
namespace solve2{
	inline int main(const int _n){
		const int n=_n-1;
		if(n==0)return 0;
		return (lint)(n*2-1)%O*inv_pow(n+1)%O;
	}
}
namespace solve3{
	inline int main(const int n){
		return rand()%O;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("farmer.in","r",stdin);
	freopen("farmer.out","w",stdout);
#endif
	const int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	int cnt2=0,cnt3=0;
	for(int i=1;i<=n;i++){
		cnt2+=T::deg[i]>=2;
		cnt3+=T::deg[i]>=3;
	}
	int ans;
	if(cnt3==0){
		ans=solve1::main(n);
	}else if(cnt2==1){
		ans=solve2::main(n);
	}else if(cnt3==1){
		ans=solve3::main(n);
	}else{
		ans=rand()%O;
	}
	printf("%d\n",ans);
	return 0;
}
