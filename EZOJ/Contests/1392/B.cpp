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
const int N=1000010,O=998244353;
int n;
namespace chain{
	const int N=::N*4;
	int pre[N],val[N];
	inline void init(){
		val[0]=-1;
	}
	inline int nn(int x,int v){
		static int n=1;
		return pre[n]=x,val[n]=v,n++;
	}
}
struct bignum{
	int d[N],ds;
	bignum():ds(0){
		memset(d,0,sizeof(d));
	}
	inline int sha(){
		int a=0;
		for(int i=ds-1;i>=0;i--){
			a=((a<<1)|d[i])%O;
		}
		return a;
	}
	inline void frchain(int x){
		using namespace chain;
		memset(d,0,sizeof(d));
		ds=val[x]+1;
		for(;x;x=pre[x]){
			d[val[x]]=1;
		}
	}
	inline void exc(int i=0){
		for(;i<ds;i++){
			d[i+1]+=d[i]>>1;
			d[i]&=1;
		}
		for(int &i=ds;d[i];i++){
			d[i+1]+=d[i]>>1;
			d[i]&=1;
		}
	}
	inline void addone(int p){
		d[p]++,apmax(ds,p),exc(p);
	}
	inline void gadd(const bignum &a,const bignum &b){
		memset(d,0,sizeof(d));
		ds=max(a.ds,b.ds);
		for(int i=0;i<ds;i++){
			d[i]=a.d[i]+b.d[i];
		}
		exc();
	}
	inline friend bool operator < (const bignum &a,const bignum &b){
		if(a.ds!=b.ds)return a.ds<b.ds;
		for(int i=a.ds-1;i>=0;i--){
			if(a.d[i]!=b.d[i])return a.d[i]<b.d[i];
		}
		return false;
	}
}ans1,ans2;
inline void dp(int f[N][3],int s[N]){
	for(int i=0;i<3;i++){
		for(int tot=ni;tot--;){
			s[ni]=i;
		}
	}
	for(int i=0;i<3;i++){
		f[0][i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){
			f[i][j]=s[i]==j?f[i-1][j]:chain::nn(f[i-1][3^j^s[i]],i-1);
		}
	}
}
int s[2][N];
int f[2][N][3];
bignum tmp1,tmp2;
inline int gans(){
	for(;n>0&&s[0][n]==s[1][n];n--);
	if(n==0)return 0;
	{//get ans1
		int thr=3^s[0][n]^s[1][n];
		tmp1.frchain(f[0][n-1][thr]);
		tmp2.frchain(f[1][n-1][thr]);
		ans1.gadd(tmp1,tmp2);
		ans1.addone(0);
	}
	{//get ans2
		tmp1.frchain(f[0][n-1][s[1][n]]);
		tmp2.frchain(f[1][n-1][s[0][n]]);
		ans2.gadd(tmp1,tmp2);
		ans2.addone(0),ans2.addone(n-1);
	}
	return (ans1<ans2?ans1:ans2).sha();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hanoi.in","r",stdin);
	freopen("hanoi.out","w",stdout);
#endif
	n=ni;
	chain::init();
	dp(f[0],s[0]);
	dp(f[1],s[1]);
	printf("%d\n",gans());
	return 0;
}
