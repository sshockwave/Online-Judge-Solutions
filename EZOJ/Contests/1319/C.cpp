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
const int N=100010,M=110,MOD=1000000007;
inline int mod(int x){
	return x>=MOD?x-MOD:x;
}
inline int mod(lint x){
	return x>=MOD?x%MOD:x;
}
inline int add(const int &a,const int &b){
	return mod(a+b);
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return mod((lint)a*b);
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
bool f[N<<2];
int pwp[N],pw1p[N];
int fac[N],infac[N];
inline int c(int n,int k){
	return mul(fac[n],mul(infac[k],infac[n-k]));
}
inline int work(){
	int n=ni,m=ni,p=ni,p1=100-p;
	pwp[0]=pw1p[0]=fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=mul(fac[i-1],i);
		pwp[i]=mul(pwp[i-1],p);
		pw1p[i]=mul(pw1p[i-1],p1);
	}
	infac[n]=fpow(fac[n],MOD-2);
	for(int i=n;i>=1;i--){
		infac[i-1]=mul(infac[i],i);
	}
	memset(f,0,sizeof(f));
	f[0]=true;
	for(int i=1;i<=m;i++){
		int c=ni;
		for(int j=0;j<=n;j++){
			f[j+c]|=f[j];
		}
	}
	int cur=n,ans=0;
	for(;!f[cur];cur++);
	for(int i=n;i>=0;i--){
		if(f[i]){
			cur=i;
		}
		apadd(ans,mul(mul(cur-i,c(n,i)),mul(pwp[i],pw1p[n-i])));
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flair.in","r",stdin);
	freopen("flair.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",work());
	}
}
