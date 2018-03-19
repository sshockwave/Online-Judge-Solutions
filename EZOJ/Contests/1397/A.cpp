#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
const int N=18,K=20,O=232792561;
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
inline void apadd(int &a,const int &b){
	a=(a+b)%O;
}
inline void apmul(int &a,const int &b){
	a=(lint)a*b%O;
}
int pri[N],cnt[N],n,k;
int f[1<<N][K],h[1<<N],bitcnt[1<<N];
void dfs(int x,int s,int j){
	if(x==n){
		int *f=::f[s],g[K];
		memcpy(g,f,sizeof(g));
		memset(f,0,sizeof(g));
		for(int i=0;i<k;i++){
			apadd(f[i],g[i]);
			apadd(f[(i+j)%k],g[i]);
		}
		return;
	}
	for(int i=0;i<=cnt[x];i++,j=j*pri[x]%k){
		dfs(x+1,s|((i==cnt[x])<<x),j);
	}
}
inline int Main(){
	{
		lint all=next_num<lint>();
		n=0,k=ni;
		for(int i=2;i<=100&&all>1;i++){
			int e=0;
			for(;all%i==0;all/=i,e++);
			if(e){
				pri[n]=i,cnt[n]=e,n++;
			}
		}
	}
	int sn=1<<n;
	memset(f,0,sizeof(f));
	for(int i=0;i<sn;i++){
		f[i][0]=1;
	}
	dfs(0,0,1);
	lint ans=0;
	for(int tot=k,wn=fpow(71,(O-1)/k),w=1;tot--;w=(lint)w*wn%O){
		for(int i=0;i<sn;i++){
			int *f=::f[i],&a=h[i]=0;
			for(int j=k-1;j>=0;j--){
				a=((lint)a*w+f[j])%O;
			}
		}
		for(int i=0;i<n;i++){
			for(int s=0,ts=1<<(n-1);s<ts;s++){
				int hi=s>>i<<i,s2=(s^hi)|(hi<<1);
				apmul(h[s2|(1<<i)],h[s2]);
			}
		}
		for(int i=0;i<sn;i++){
			if((n-bitcnt[i])&1){
				ans-=h[i];
			}else{
				ans+=h[i];
			}
		}
	}
	return (ans%O+O)*inv(k)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("lcm.in","r",stdin);
	freopen("lcm.out","w",stdout);
#endif
	bitcnt[0]=0;
	for(int i=1;i<(1<<N);i++){
		bitcnt[i]=bitcnt[i^(i&-i)]+1;
	}
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
