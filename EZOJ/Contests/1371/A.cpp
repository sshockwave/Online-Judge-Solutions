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
const int N=1010,M=35,O=998244353;
int a[M][M],n,m;
namespace brute12{
	int ans;
	bool vis[M][N];
	int perm[M][N];
	inline bool check(){
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				bool flag=true;
				for(int k=1;k<=n;k++){
					if(perm[j][perm[i][k]]!=perm[a[i][j]][k])return false;
					flag&=perm[i][k]==perm[j][k];
				}
				if(i!=j&&flag)return false;
			}
		}
		return true;
	}
	void dfs(int i,int j){
		if(j>n){
			i++,j=1;
		}
		if(i>m)return ans+=check(),void();
		for(int &x=perm[i][j]=1;x<=n;x++){
			if(!vis[i][x]){
				vis[i][x]=true;
				dfs(i,j+1);
				vis[i][x]=false;
			}
		}
	}
	inline int Main(){
		ans=0;
		memset(vis,0,sizeof(vis));
		dfs(1,1);
		return ans;
	}
}
int mu[N],prime[N],ps=0;
bool np[N];
inline void sieve(int n){
	mu[1]=1;
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur){
				mu[i*cur]=-mu[i];
			}else{
				mu[i*cur]=0;
				break;
			}
		}
	}
}
int fac[N];
int c[N][N];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	memset(c,0,sizeof(c));
	for(int i=0;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%O;
		}
	}
}
namespace brute34{
	int f[N];
	inline int dp(int m){
		f[0]=1;
		for(int i=1;i<=n;i++){
			lint ans=0;
			for(int j=1;j<=m&&j<=i;j++){
				if(m%j==0){
					ans+=(lint)f[i-j]*c[i-1][j-1]%O*fac[j-1]%O;
				}
			}
			f[i]=ans%O;
		}
		return f[n];
	}
	inline int Main(){
		lint ans=0;
		for(int i=1;i<=m;i++){
			if(m%i==0){
				ans+=dp(i)*mu[m/i];
			}
		}
		return (ans%O+O)%O;
	}
}
inline int Main(){
	n=ni,m=ni;
	bool flag34=true;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=ni;
			flag34&=(a[i][j]-(i+j-1))%m==0;
		}
	}
	if(m<=4&&n<=5)return brute12::Main();
	if(flag34)return brute34::Main();
	//TODO
	return 0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("monkey.in","r",stdin);
	freopen("monkey.out","w",stdout);
#endif
	sieve(N-1);
	gmath(N-1);
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
