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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10010,O=998244353;
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
int fac[N],invfac[N];
inline int c(int n,int k){
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
namespace poly{
    const int SH=15,N=1<<SH;
    int sh,n,invn;
    int rev[N],o[SH][N>>1],io[SH][N>>1];
    inline void init(int _n){
        for(sh=0;(1<<sh)<_n;sh++);
        n=1<<sh,invn=inv(n);
        rev[0]=0;
        for(int i=0;i<n;i++){
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
        }
        for(int i=0;i<sh;i++){
            int half=1<<i,full=half<<1;
            lint w=1,iw=1,wn=fpow(3,(O-1)/full),iwn=inv(wn);
            for(int j=0;j<half;j++,(w*=wn)%=O,(iw*=iwn)%=O){
                o[i][j]=w,io[i][j]=iw;
            }
        }
    }
    inline void ntt(int a[],int d=1){
        for(int i=0;i<n;i++){
            if(rev[i]>i){
                swap(a[i],a[rev[i]]);
            }
        }
        for(int i=0;i<sh;i++){
            int half=1<<i,full=half<<1;
            for(int j=0;j<half;j++){
                int w=(d==1?o:io)[i][j];
                for(int k=j;k<n;k+=full){
                    int p=a[k],q=(lint)a[k+half]*w%O;
                    a[k]=(p+q)%O;
                    a[k+half]=(p+O-q)%O;
                }
            }
        }
        if(d==-1){
            for(int i=0;i<n;i++){
                a[i]=(lint)a[i]*invn%O;
            }
        }
    }
	inline void fpow(int a[],int b[],int o,int e){
		if(e==0){
			memset(a,0,n<<2);
			ntt(b);
			a[0]=1;
			return;
		}
		fpow(a,b,o,e>>1);
		ntt(a);
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*a[i]%O;
		}
		ntt(a,-1);
		memset(a+o,0,(n-o)<<2);
		if(e&1){
			ntt(a);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*b[i]%O;
			}
			ntt(a,-1);
			memset(a+o,0,(n-o)<<2);
		}
	}
}
int f[poly::N],g[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("shuffle.in","r",stdin);
	freopen("shuffle.out","w",stdout);
#endif
	int a=0,b=0;
	{
		static char s1[N],s2[N];
		scanf("%s%s",s1,s2);
		for(int i=0;s1[i];i++){
			if(s2[i]=='1'){
				(s1[i]=='1'?a:b)++;
			}
		}
	}
	gmath(a+b);
	lint ans=0;
	poly::init((a<<1)|1);
	memset(g,0,poly::n<<2);
	for(int i=0;i<=a;i++){
		g[i]=invfac[i+1];
	}
	poly::fpow(f,g,a+1,b);
	for(int i=0;i<=a;ans+=f[i],i++);
	ans=ans%O*fac[a+b]%O*fac[a]%O*fac[b]%O;
	printf("%lld\n",ans);
	return 0;
}
