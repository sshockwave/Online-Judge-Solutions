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
const int N=1000010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
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
inline int inv(int x){
	return fpow(x,MOD-2);
}
inline int c3(int n){
	static int inv6=inv(6);
	if(n<3){
		return 0;
	}
	return mul(n,mul(n-1,mul(n-2,inv6)));
}
int prime[N],mu[N],ps=0;
int n2[N],n3[N];
int _n1[N],_n2[N],_n3[N];
lint f1[N],f2[N],f3[N];
bool np[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	n2[0]=n3[0]=_n1[0]=_n2[0]=_n3[0]=0;
	for(int i=1;i<N;i++){
		n2[i]=mul(i,i);
		n3[i]=mul(i,mul(i,i));
		_n1[i]=add(_n1[i-1],i);
		_n2[i]=add(_n2[i-1],n2[i]);
		_n3[i]=add(_n3[i-1],n3[i]);
	}
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=MOD-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=mul(mu[i],mu[cur]);
			}
		}
	}
	memset(f1,0,sizeof(f1));
	memset(f2,0,sizeof(f2));
	memset(f3,0,sizeof(f3));
	for(int i=1;i<N;i++){
		int val1=mu[i];
		int val2=mul(mu[i],i);
		int val3=mul(mu[i],n2[i]);
		for(int j=1,k=i;k<N;j++,k+=i){
			f1[k]+=(lint)j*val1%MOD;
			f2[k]+=(lint)n2[j]*val2%MOD;
			f3[k]+=(lint)n3[j]*val3%MOD;
		}
	}
	for(int i=1;i<N;i++){
		(f1[i]+=f1[i-1])%=MOD;
		(f2[i]+=f2[i-1])%=MOD;
		(f3[i]+=f3[i-1])%=MOD;
	}
}
inline int work(int n,int m){
	if(n>m){
		swap(n,m);
	}
	lint sum=0,sumi=0,sumj=0,sumij=0;
	for(int l=1,r;l<=n;l=r+1){
		int p=n/l,q=m/l;
		r=min(n/p,m/q);//[l,r]
		sum+=mul(mul(p,q),sub(f1[r],f1[l-1]));
		sumi+=mul(mul(_n1[p],q),sub(f2[r],f2[l-1]));
		sumj+=mul(mul(p,_n1[q]),sub(f2[r],f2[l-1]));
		sumij+=mul(mul(_n1[p],_n1[q]),sub(f3[r],f3[l-1]));
	}
	int ans=sub(add(mul(mul(n+1,m+1),sum%MOD),sumij%MOD),add(mul(m+1,sumi%MOD),mul(n+1,sumj%MOD)));
	return sub(ans,mul(_n1[n],_n1[m]));
}
inline int Main(){
	int n=ni,m=ni;
	int ans=add(mul(n+1,c3(m+1)),mul(m+1,c3(n+1)));
	return sub(c3(mul(n+1,m+1)),add(ans,mul(2,work(n,m))));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
#endif
	sieve();
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
