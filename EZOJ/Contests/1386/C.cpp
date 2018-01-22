#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
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
template<class T>T sqr(const T &x){return x*x;}
template<class T>T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
template<class T>T lcm(const T &a,const T &b){return a/gcd(a,b)*b;}
const int N=210;
int n,O;
namespace math{
	int fac[N],invfac[N];
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
	inline void init(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		if(n<k)return 0;
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
typedef vector<int>vi;
vi nums[N];
int nump[N];
namespace sieve{
	int pri[N],ps=0;
	bool np[N];
	int mxp[N],mxid[N],tim=0;
	void init(int n){
		memset(np,0,sizeof(np));
		mxid[1]=++tim;
		nums[1].push_back(1);
		nump[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				if(i*i<=n){
					mxid[i]=1;
				}else{
					mxid[i]=++tim;
					nump[tim]=i;
				}
			}
			nums[mxid[i]].push_back(i);
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				mxid[t]=mxid[i];
				if(i%p==0)break;
			}
		}
	}
}
namespace hush{
	const int C=2060;
	typedef map<lint,int>mp;
	mp dfn;
	lint idx[C];
	int tim=0;
	void dfs(int x,int sum,lint prod){
		if(x==sieve::ps-(sieve::tim-1)){
			idx[dfn[prod]=++tim]=prod;
			return;
		}
		using sieve::pri;
		dfs(x+1,sum,prod);
		for(lint cur=1;cur*=pri[x],sum+cur<=n;){
			dfs(x+1,sum+cur,prod*cur);
		}
	}
}
int f[N][hush::C][2],g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
#endif
	n=ni,O=ni;
	math::init(n);
	sieve::init(n);
	hush::dfs(0,0,1);
	memset(f,0,sizeof(f));
	f[0][1][0]=1;
	assert(hush::idx[1]==1);
	for(int i=1;i<=sieve::tim;i++){
		for(vi::iterator it=nums[i].begin(),ti=nums[i].end();it!=ti;it++){
			int x=*it,y=x/nump[i];
			assert(y*nump[i]==x);
			using math::fac;
			using math::invfac;
			g[0]=1;
			for(int e=1,sum=x,w=(lint)invfac[x]*fac[x-1]%O;sum<=n;e++,sum+=x){
				g[e]=(lint)g[e-1]*w%O;
			}
			for(int e=1,sum=x;sum<=n;e++,sum+=x){
				g[e]=(lint)g[e]*invfac[e]%O;
			}
			for(int k=hush::tim;k>=1;k--){
				int tk=hush::dfn[lcm(hush::idx[k],(lint)y)];
				if(tk==0)continue;
				for(int j=n-x;j>=0;j--){
					lint F=f[j][k][0]+f[j][k][1];
					if(F==0)continue;
					F=F*fac[n-j]%O;
					for(int e=1,sum=j+x;sum<=n;e++,sum+=x){
						f[sum][tk][1]=(f[sum][tk][1]+F*invfac[n-sum]%O*g[e])%O;
					}
				}
			}
		}
		lint sq=(lint)nump[i]*nump[i]%O;
		for(int j=0;j<=n;j++){
			for(int k=1;k<=hush::tim;k++){
				if(f[j][k][1]){
					f[j][k][0]=(f[j][k][0]+sq*f[j][k][1])%O;
					f[j][k][1]=0;
				}
			}
		}
	}
	lint ans=0;
	for(int k=1;k<=hush::tim;k++){
		ans+=sqr((lint)hush::idx[k])%O*f[n][k][0]%O;
	}
	printf("%lld\n",ans%O*math::invfac[n]%O);
	return 0;
}
