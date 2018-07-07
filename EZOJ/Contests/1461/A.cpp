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
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=73;
int n,O;
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
	assert(x);
	return fpow(x,O-2);
}
namespace lagrange{
	int x[N],y[N];
	int a[N],f[N];
	inline void main(){
		a[0]=1,mset(a+1,0,n+1);
		for(int i=0;i<=n;i++){
			const int r=(O-x[i])%O;
			for(int j=i;j>=0;j--){
				a[j+1]=(a[j+1]+a[j])%O;
				a[j]=(lint)a[j]*r%O;
			}
		}
		mset(f,0,n+1);
		for(int i=0;i<=n;i++){
			int k=1;
			for(int j=0;j<=n;j++){
				if(j!=i){
					k=(lint)k*(x[i]+O-x[j])%O;
				}
			}
			k=(lint)y[i]*inv_pow(k)%O;
			int r=0;
			for(int j=n+1;j>=0;j--){
				f[j]=(f[j]+(lint)r*k)%O;
				r=(a[j]+(lint)r*x[i])%O;
			}
			assert(r==0);
		}
	}
}
int a[N][N];
inline int gauss(){
	int ans=1;
	for(int i=1;i<=n;i++){
		int j=i;
		for(;j<=n&&a[j][i]==0;j++);
		if(j>n)return 0;
		if(i!=j){
			ans=O-ans;
			for(int k=i;k<=n;k++){
				swap(a[i][k],a[j][k]);
			}
		}
		int r=a[i][i];
		if(r!=1){
			ans=(lint)ans*r%O;
			r=inv_pow(r);
			for(int k=i;k<=n;k++){
				a[i][k]=(lint)a[i][k]*r%O;
			}
		}
		for(j=i+1;j<=n;j++){
			r=O-a[j][i];
			if(r==O)continue;
			for(int k=i;k<=n;k++){
				a[j][k]=(a[j][k]+(lint)a[i][k]*r)%O;
			}
		}
	}
	return ans;
}
int mat[N][N];
inline int calc(const int lam){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=(O-mat[i][j])%O;
		}
		a[i][i]=(a[i][i]+lam)%O;
	}
	return gauss();
}
inline void add_I(int v){
	for(int i=1;i<=n;i++){
		a[i][i]=(a[i][i]+v)%O;
	}
}
inline bool isz(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j])return false;
		}
	}
	return true;
}
inline void mulmat(){
	static int b[N][N];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int ans=0;
			for(int k=1;k<=n;k++){
				ans=(ans+(lint)a[i][k]*mat[k][j])%O;
			}
			b[i][j]=ans;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=b[i][j];
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("poly.in","r",stdin);
	freopen("poly.out","w",stdout);
#endif
	n=ni,O=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mat[i][j]=ni;
		}
	}
	for(int i=0;i<=n;i++){
		lagrange::x[i]=i;
		lagrange::y[i]=calc(i);
	}
	lagrange::main();
	using lagrange::f;
	assert(f[n]==1);
	int t=0,p=n;
	memset(a,0,sizeof(a));
	for(;add_I(f[p]),!isz();t++,p--,mulmat());
	printf("%d\n",t);
	for(;p<=n;p++){
		printf("%d ",f[p]);
	}
	putchar('\n');
	return 0;
}
