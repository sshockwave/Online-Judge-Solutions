#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1000010,MOD=1000000007;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int rev(int x){
	return fpow(x,MOD-2);
}
int mu[N],prime[N],ptop=0;
bool np[N];
int f[N],g[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	g[0]=0,g[1]=f[1]=mu[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
		}
		for(int j=0,cur=2;i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
		g[i]=add(g[i-1],g[i-2]);
	}
	f[0]=g[0]=1;
	for(int i=2;i<N;i++){
		f[i]=rev(g[i]);
		for(int j=i<<1;j<N;j+=i){
			apmul(g[j],f[i]);
		}
		apmul(g[i],g[i-1]);
		apmul(f[i],f[i-1]);
	}
}
inline int work(int n,int m){
	if(n>m){
		swap(n,m);
	}
	int ans=1;
	for(int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		apmul(ans,fpow(mul(g[r],f[l-1]),(lint)(n/l)*(m/l)%(MOD-1)));
	}
	return ans;
}
int main(){
	sieve();
	for(int tot=ni;tot--;){
		printf("%d\n",work(ni,ni));
	}
}
