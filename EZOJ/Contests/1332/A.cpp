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
const int N=14010,K=10,KN=N*K,MOD=786433;
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
int fac[MOD],invfac[MOD],inv[MOD];
namespace poly{
	const int SH=18,N=1<<SH;
	int sh,n;
	int o[SH][N],io[SH][N],rev[N];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
		rev[0]=0;
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			int w=1,iw=1,wn=fpow(10,(MOD-1)/full),iwn=inv[wn];
			for(int j=0;j<half;j++,apmul(w,wn),apmul(iw,iwn)){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			if(rev[i]>i){
				swap(a[rev[i]],a[i]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				int w=d==1?o[i][j]:io[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=mul(w,a[k+half]);
					a[k]=add(p,q);
					a[k+half]=sub(p,q);
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				apmul(a[i],inv[n]);
			}
		}
	}
}
int f[K][poly::N],prod[poly::N],cnt0[poly::N],nttp[poly::N];
int tmp;//debug
inline int getv(int f[],int x){
	int ans=0;
	for(int i=0,w=1;i<poly::n;i++,apmul(w,x)){
		apadd(ans,mul(f[i],w));
	}
	return ans;
}
int g[K][KN];
inline void altf(int f[],int p,int ov,int nv){
	for(int i=0,w=sub(nv,ov),wn=fpow(poly::o[poly::sh-1][1],p);i<poly::n;i++,apmul(w,wn)){
		if(f[i]){
			apmul(prod[i],inv[f[i]]);
		}else{
			cnt0[i]--;
		}
		apadd(f[i],w);
		if(f[i]){
			apmul(prod[i],f[i]);
		}else{
			cnt0[i]++;
		}
		nttp[i]=cnt0[i]?0:prod[i];
	}
}
inline int work(){
	poly::ntt(nttp,-1);
	lint ans=0;
	for(int i=0;i<poly::n;i++){
		ans+=mul(fac[i],nttp[i]);
	}
	return ans%MOD;
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("int.in","r",stdin);
	freopen("int.out","w",stdout);
#endif
	int k=ni,n=ni,tot=ni;
	fac[0]=1;
	for(int i=1;i<MOD;i++){
		fac[i]=mul(fac[i-1],i);
	}
	invfac[MOD-1]=fpow(fac[MOD-1],MOD-2);
	for(int i=MOD-1;i>=1;i--){
		invfac[i-1]=mul(invfac[i],i);
	}
	for(int i=1;i<MOD;i++){
		inv[i]=mul(invfac[i],fac[i-1]);
	}
	poly::init(n*(k-1)+1);
	memset(f,0,sizeof(f));
	for(int i=1;i<k;i++){
		scanf("%s",s);
		for(int j=0;j<=n;j++){
			f[i][j]=g[i][j]=s[j]=='1'?invfac[j]:0;
		}
		poly::ntt(f[i]);
	}
	for(int i=0;i<poly::n;i++){
		prod[i]=1,cnt0[i]=0;
		for(int j=1;j<k;j++){
			if(f[j][i]){
				apmul(prod[i],f[j][i]);
			}else{
				cnt0[i]++;
			}
		}
		nttp[i]=cnt0[i]?0:prod[i];
	}
	lint ans=work();
	while(tot--){
		int u=ni,v=ni;
		tmp=u;
		altf(f[u],v,g[u][v],invfac[v]-g[u][v]);
		g[u][v]=invfac[v]-g[u][v];
		ans+=work();
	}
	printf("%lld\n",ans%MOD);
	return 0;
}
