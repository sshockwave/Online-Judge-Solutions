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
int eqn[N*N][N],f[N];
inline int gauss(){
	int i;
	for(i=0;;i++){
		int j=i;
		for(;j<=n*n&&eqn[j][i]==0;j++);
		if(j>n*n)break;
		if(i!=j){
			for(int k=i;k<=n;k++){
				swap(eqn[i][k],eqn[j][k]);
			}
		}
		int r=eqn[i][i];
		if(r!=1){
			r=inv_pow(r);
			for(int k=i;k<=n;k++){
				eqn[i][k]=(lint)eqn[i][k]*r%O;
			}
		}
		for(j=0;j<=n*n;j++){
			if(i==j)continue;
			r=O-eqn[j][i];
			if(r==O)continue;
			for(int k=i;k<=n;k++){
				eqn[j][k]=(eqn[j][k]+(lint)eqn[i][k]*r)%O;
			}
		}
	}
	memset(f,0,sizeof(f));
	assert(i<=n);
	f[i]=1;
	for(int j=0;j<i;j++){
		f[j]=(O-eqn[j][i])%O;
	}
	return i;
}
int mat[N][N],a[N][N];
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
			a[i][j]=i==j;
		}
	}
	for(int t=0;t<=n;t++,mulmat()){
		int ps=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				eqn[ps++][t]=a[i][j];
			}
		}
	}
	const int tn=gauss();
	printf("%d\n",tn);
	for(int i=0;i<=tn;i++){
		printf("%d ",f[i]);
	}
	putchar('\n');
	return 0;
}
