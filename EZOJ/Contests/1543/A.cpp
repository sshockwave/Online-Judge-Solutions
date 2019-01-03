#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=110,O=1e9+7,matN=N<<1;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
const lint OO=(lint)O*O;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
int a[N],n,matn;
int vec[matN];
struct Mat{
	int a[matN][matN];
	inline void clr(){
		for(int i=1;i<=matn;i++){
			mset(a[i]+1,0,matn);
		}
	}
	inline void id(){
		clr();
		for(int i=1;i<=matn;i++){
			a[i][i]=1;
		}
	}
	inline void getmul(const Mat &x,const Mat &y){
		for(int i=1;i<=matn;i++){
			for(int j=1;j<=matn;j++){
				lint ans=0;
				for(int k=1;k<=matn;k++){
					ans+=(lint)x.a[i][k]*y.a[k][j];
					if(ans>LINF-OO){
						ans%=O;
					}
				}
				a[i][j]=ans%O;
			}
		}
	}
	inline void apvec(){
		static int tmp[matN];
		mcpy(tmp+1,vec+1,matn);
		for(int i=1;i<=matn;i++){
			lint ans=0;
			for(int j=1;j<=matn;j++){
				ans+=(lint)a[i][j]*tmp[j];
				if(ans>LINF-OO){
					ans%=O;
				}
			}
			vec[i]=ans%O;
		}
	}
}trans,tmp;
void fpow(int n){
	for(;n;n>>=1,tmp=trans,trans.getmul(tmp,tmp)){
		if(n&1){
			trans.apvec();
		}
	}
}
int fail[N];
inline int lssum(int l,int r){
	return (lint)(l+r)*(r-l+1)/2%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
#endif
	n=ni,matn=n<<1;
	const int m=ni,e=ni;
	a[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=n;i>=1;i--){
		a[i]-=a[i-1];
	}
	fail[0]=-1;
	for(int i=0,j=-1;i<n;){
		if(j==-1||a[i+1]==a[j+1]||(j==0&&a[i+1]>=a[1])){
			fail[++i]=++j;
		}else{
			j=fail[j];
		}
	}
	trans.clr();
	for(int i=1;i<=n;i++){
		int cnt=m-a[1]+1;
		int sum=lssum(a[1],m);
		set<int>s;
		for(int j=i;j!=-1;j=fail[j]){
			if(j+1>n)continue;
			if(s.find(a[j+1])!=s.end())continue;
			s.insert(a[j+1]);
			trans.a[j+1][i]=1;
			trans.a[n+j+1][n+i]=1;
			trans.a[n+j+1][i]=a[j+1];
			if(a[j+1]>=a[1]){
				--cnt,apadd(sum,O-a[j+1]);
			}
		}
		apadd(trans.a[1][i],cnt);
		apadd(trans.a[n+1][n+i],cnt);
		apadd(trans.a[n+1][i],sum);
	}
	mset(vec+1,0,matn);
	vec[1]=m-a[1]+1,vec[n+1]=lssum(a[1],m);
	fpow(e-1);
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=vec[i+n];
	}
	ans%=O;
	printf("%lld\n",ans);
	return 0;
}
