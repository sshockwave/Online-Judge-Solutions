#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;
typedef set<int>si;
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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=300010,O=1000000007;
namespace gmath{
	int fac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
	}
}
namespace sieve{
	bool np[N];
	int pri[N],ps=0;
	int mnfact[N],nxt[N];
	int iso[N];
	inline void main(int n){
		mset(np+1,0,n);
		iso[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mnfact[i]=i;
				iso[i]=i;
				nxt[i]=1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				mnfact[t]=p;
				if(i%p){
					nxt[t]=i;
					iso[t]=iso[i]*p;
				}else{
					nxt[t]=nxt[i];
					iso[t]=iso[i];
					break;
				}
			}
		}
	}
	inline int factorize_arr(int lst[],int n){
		int ls=0;
		if(n==1){
			lst[++ls]=1;
		}else for(;n!=1;n=nxt[n]){
			lst[++ls]=mnfact[n];
		}
		return ls;
	}
}
int lst[N],lst2[N];
int a[N];
int isocnt[N];
int mp[N];
int bel[N];
int belcnt[N];
inline bool bel_cmp(int a,int b){
	return bel[a]<bel[b];
}
inline int Main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	mset(belcnt+1,0,n);
	bel[1]=1,++belcnt[1];
	for(int i=0,cur,las=-1;i<sieve::ps&&sieve::pri[i]<=n;i++,las=cur){
		const int p=sieve::pri[i];
		cur=n/p;
		if(cur==1){
			bel[p]=1;
		}else if(cur==las){
			bel[p]=bel[sieve::pri[i-1]];
		}else{
			bel[p]=p;
		}
		++belcnt[bel[p]];
	}
	mset(mp+1,0,n);
	for(int i=1;i<=n;i++){
		if(a[i]==0)continue;
		int ls=sieve::factorize_arr(lst,i);
		int ls2=sieve::factorize_arr(lst2,a[i]);
		if(ls!=ls2)return 0;
		sort(lst+1,lst+ls+1,bel_cmp);
		sort(lst2+1,lst2+ls2+1,bel_cmp);
		for(int j=1;j<=ls;j++){
			int p=lst[j],p2=lst2[j];
			if(bel[p]!=bel[p2])return 0;
			if(mp[p]==0){
				mp[p]=p2;
				--belcnt[bel[p]];
			}else if(mp[p]!=p2)return 0;
		}
	}
	mset(isocnt+1,0,n);
	for(int i=1;i<=n;i++){
		++isocnt[sieve::iso[i]];
	}
	for(int i=1;i<=n;i++){
		--isocnt[sieve::iso[a[i]]];
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		if(isocnt[i]){
			ans=(lint)ans*gmath::fac[isocnt[i]]%O;
		}
		if(belcnt[i]){
			assert(belcnt[i]>0);
			ans=(lint)ans*gmath::fac[belcnt[i]]%O;
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
#endif
	gmath::main(N-1);
	sieve::main(N-1);
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
