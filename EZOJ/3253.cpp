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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=310,O=1000000007;
inline void apadd(int &a,const lint &b){
	a=(a+b)%O;
}
int f[N][N];
int a[N],b[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("g.in","r",stdin);
	freopen("g.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni,b[i]=ni;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=1,j=1;i<=n;i++){
		for(;j<=n&&a[j]<b[i];j++);
		const int cnt=j-1;
		for(int u=cnt;u>=0;u--){
			for(int v=cnt-u;v>=0;v--){
				const lint F=f[u][v];
				f[u][v]=0;
				if(v>0){
					apadd(f[u+1][v-1],F*v);
				}
				apadd(f[u+1][v],F*(cnt-u-v));
				apadd(f[u][cnt-u],F);
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=f[i][0];
	}
	printf("%lld\n",ans%O);
	return 0;
}
