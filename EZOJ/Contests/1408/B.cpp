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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int SH=20,N=(1<<SH)+10,O=998244353;
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
	assert(x);
	return fpow(x,O-2);
}
namespace poly{
	int n,invn,sh,r[N],o[N];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		r[0]=0,o[0]=1;
		for(int i=1,w=fpow(3,(O-1)>>sh);i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1)),o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			if(r[i]<i){
				swap(a[i],a[r[i]]);

			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=o[j<<(sh-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
inline int _n(int n){
	return (lint)n*(n+1)/2%O;
}
inline int work(int f[],int sh,int p){
	int n=1<<sh;
	poly::init(n);
	poly::ntt(f);
	for(int i=0;i<poly::n;i++){
		f[i]=inv((lint)(1+O-(lint)p*f[i]%O)%O);
	}
	poly::ntt(f,-1);
	f[0]=(f[0]+O-1)%O;
	int ans=0;
	for(int i=0;i<n;i++){
		ans=(ans+(lint)f[i]*i)%O;
	}
	return (lint)ans*(O+1-p)%O*inv(p)%O;
}
char ban[SH+1];
int prob[SH][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("inhibit.in","r",stdin);
	freopen("inhibit.out","w",stdout);
#endif
	int n=ni,p=ni;
	scanf("%s",ban);
	memset(prob,0,sizeof(prob));
	int probinv=inv(_n((1<<n)-1));
	for(int s=0,ts=1<<n;s<ts;s++){
		int a=0;
		for(int i=0;i<n;i++){
			a|=1<<i;
			if(ban[i]=='1'){
				int t=s&a,&F=prob[i][t/(a&-a)];
				F=(F+(lint)s*probinv)%O;
				a=0;
			}
		}
	}
	int acnt=0,st=0;
	int ans=0;
	for(int i=0;i<n;i++){
		acnt++;
		if(ban[i]=='1'){
			ans=(ans+((lint)work(prob[i],acnt,p)<<st))%O;
			acnt=0;
			st=i+1;
		}
	}
	printf("%d\n",ans);
	return 0;
}
