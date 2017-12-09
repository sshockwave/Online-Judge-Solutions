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
const int N=200010,O=924844033;
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
namespace poly{
	const int SH=19,N=1<<SH;
	int sh,n,invn;
	int rev[N],o[SH][N<<1],io[SH][N<<1];
	inline void init(int _n){//g=5
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		rev[0]=0;
		for(int i=0;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			lint w=1,iw=1,wn=fpow(5,(O-1)/full),iwn=inv(wn);
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
}
int n,cnt[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dfs(int x,int fa){
		int size=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				size+=dfs(v,x);
			}
		}
		if(fa){
			cnt[size]++;
			cnt[n-size]++;
		}
		return size;
	}
}
int fac[N],invfac[N];
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
int a[poly::N],b[poly::N];
int main(){
	n=ni;
	gmath(n),T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	T::dfs(1,0);
	poly::init(n<<1);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	for(int i=0;i<n;i++){
		a[i]=(lint)fac[n-i]*cnt[n-i]%O;
		b[i]=invfac[i];
	}
	poly::ntt(a),poly::ntt(b);
	for(int i=0;i<poly::n;i++){
		a[i]=(lint)a[i]*b[i]%O;
	}
	poly::ntt(a,-1);
	for(int k=1;k<=n;k++){
		lint ans=(lint)fac[n]*invfac[k]%O*invfac[n-k]%O*n%O;
		ans-=(lint)a[n-k]*invfac[k]%O;
		printf("%lld\n",(ans%O+O)%O);
	}
	return 0;
}
