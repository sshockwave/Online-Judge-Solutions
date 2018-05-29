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
const int N=53,L=10010,O=1000000009;
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
int n;
struct Mat{
	int a[N][N];
	inline void id(){
		for(int i=1;i<=n;i++){
			mset(a[i]+1,0,n);
			a[i][i]=1;
		}
	}
	inline void gmul(const Mat &p,const Mat &q){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int &ans=a[i][j]=0;
				for(int k=1;k<=n;k++){
					ans=(ans+(lint)p.a[i][k]*q.a[k][j])%O;
				}
			}
		}
	}
};
namespace poly{
	Mat m;
	inline int gauss(){
		int (*const a)[N]=m.a;
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
				if(a[j][i]==0)continue;
				r=O-a[j][i];
				for(int k=i;k<=n;k++){
					a[j][k]=(a[j][k]+(lint)a[i][k]*r)%O;
				}
			}
		}
		return ans;
	}
	int pval[N];
	int f[N];
	int polyup[N];
	inline void lagrange(){
		memset(polyup,0,sizeof(polyup));
		polyup[1]=1;
		for(int i=1;i<=n;i++){
			const int mul=O-i;
			for(int j=i+1;j>=1;j--){
				polyup[j]=(polyup[j-1]+(lint)polyup[j]*mul)%O;
			}
		}
		memset(f,0,sizeof(f));
		for(int i=0;i<=n;i++){
			int y=1;
			for(int j=0;j<=n;j++){
				if(i==j)continue;
				y=(lint)y*(i+O-j)%O;
			}
			y=(lint)pval[i]*inv_pow(y)%O;
			int r=polyup[n+1];
			for(int j=n;j>=0;j--){
				//polytmp[j]=r;
				f[j]=(f[j]+(lint)r*y)%O;
				r=(polyup[j]+(lint)r*i)%O;
			}
		}
	}
	inline void get(const Mat &a){
		for(int x=0;x<=n;x++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(i==j){
						m.a[i][j]=(x+O-a.a[i][j])%O;
					}else if(a.a[i][j]){
						m.a[i][j]=O-a.a[i][j];
					}else{
						m.a[i][j]=0;
					}
				}
			}
			pval[x]=gauss();
		}
		lagrange();
	}
	inline void muleq(int a[],const int b[],int lena,int lenb){
		static int c[N<<1];
		mset(c,0,lena+lenb+1);
		for(int i=0;i<=lena;i++){
			for(int j=0;j<=lenb;j++){
				c[i+j]=(c[i+j]+(lint)a[i]*b[j])%O;
			}
		}
		memcpy(a,c,(lena+lenb+1)*sizeof(a[0]));
	}
	inline void modeq(int a[],const int b[],int lena,int lenb){
		assert(b[lenb]==1);
		for(int i=lena;i>=lenb;i--){
			if(a[i]==0)continue;
			const int r=O-a[i];
			for(int j=0;j<=lenb;j++){
				a[i-j]=(a[i-j]+(lint)b[lenb-j]*r)%O;
			}
		}
	}
}
Mat trans,res;
int f[N<<1];
inline void fpow(char s[]){
	memset(f,0,sizeof(f));
	f[0]=1;
	for(;s[0];s++){
		int tn=n<<1;
		poly::muleq(f,f,n,n);
		if(s[0]=='1'){
			++tn;
			for(int i=tn;i>=1;i--){
				f[i]=f[i-1];
			}
			f[0]=0;
		}
		poly::modeq(f,poly::f,tn,n);
	}
}
inline void calcf(){
	memset(&res,0,sizeof(res));
	static Mat tmp;
	for(int p=n-1;p>=0;p--){
		tmp=res,res.gmul(tmp,trans);
		for(int i=1;i<=n;i++){
			res.a[i][i]=(res.a[i][i]+f[p])%O;
		}
	}
}
char s[L];
int main(){
#ifndef ONLINE_JUDGE
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
#endif
	n=ni;
	scanf("%s",s);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			trans.a[i][j]=ni;
		}
	}
	poly::get(trans);
	if(poly::f[n]!=1){
		const int r=inv_pow(poly::f[n]);
		for(int i=0;i<=n;i++){
			poly::f[i]=(lint)poly::f[i]*r%O;
		}
	}
	fpow(s);//put in f
	calcf();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",res.a[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
