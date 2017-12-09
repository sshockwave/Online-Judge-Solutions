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
const int N=2010,O=924844033;
int f[N][N][2][2],g[N];
inline void dp(int n){//n slots n elements
	memset(f,0,sizeof(f));
	f[0][0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			for(int a=0;a<2;a++){//i-1
				for(int b=0;b<2;b++){//i
					int F=f[i-1][j][a][b];
					if(F==0)continue;
					//use nothing
					(f[i][j][b][0]+=F)%=O;
					//use i-1
					if(a==0&&i>1){
						(f[i][j+1][b][0]+=F)%=O;
					}
					//use i+1
					if(i<n){
						(f[i][j+1][b][1]+=F)%=O;
					}
				}
			}
		}
	}
	for(int i=0;i<=n;i++){
		g[i]=(f[n][i][0][0]+f[n][i][1][0])%O;
	}
}
int h[N];
int fac[N];
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
}
inline int Main(){
	int n=ni,k=ni;
	gmath(n);
	int sum=0,lastlen=-1;
	memset(h,0,sizeof(h));
	h[0]=1;
	for(int i=1;i<=k;i++){
		int curlen=(n-i)/k+1;
		if(curlen!=lastlen){
			dp(lastlen=curlen);
		}
		for(int j=sum;j>=0;j--){
			lint tmp=h[j];
			h[j]=0;
			for(int k=0;k<=curlen;k++){
				(h[j+k]+=tmp*g[k]%O)%=O;
			}
		}
		sum+=curlen;
	}
	lint ans=0;
	for(int i=0;i<=n;i++){
		if(i&1){
			ans-=(lint)h[i]*fac[n-i]%O;
		}else{
			ans+=(lint)h[i]*fac[n-i]%O;
		}
	}
	return (ans%O+O)%O;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
