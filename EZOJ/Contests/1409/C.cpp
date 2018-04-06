#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=1000010,O=1000000007;
namespace sieve{
	int pri[N],ps=0;
	bool np[N];
	int mu[N];
	inline void main(int n){
		memset(np,0,sizeof(np));
		mu[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mu[i]=-1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p){
					mu[t]=-mu[i];
				}else{
					mu[t]=0;
					break;
				}
			}
		}
	}
}
int lend[N],rend[N];//(lend,rend]
int _n1[N];
inline int calc(const int n,const int m,const int l,const int r){
	int ans=0,ansi=0,ansj=0,ansij=0;
	sieve::main(r);
	lint l2=(lint)l*l,r2=(lint)r*r;
	for(int i=1;i<=n&&i<=r;i++){
		lint i2=(lint)i*i;
		lint tmpl=l2-i2,tmpr=r2-i2;
		if(tmpl<=0){
			lend[i]=0;
		}else{
			lend[i]=sqrt(tmpl);
			for(int &j=lend[i];i2+(lint)j*j<l2;j++);
			for(int &j=lend[i];i2+(lint)j*j>=l2;j--);
			apmin(lend[i],m);
		}
		if(tmpr<=0){
			rend[i]=0;
		}else{
			rend[i]=sqrt(tmpr);
			for(int &j=rend[i];i2+(lint)j*j<=r2;j++);
			for(int &j=rend[i];i2+(lint)j*j>r2;j--);
			apmin(rend[i],m);
		}
	}
	_n1[0]=0;
	for(int i=1;i<=m&&i<=r;i++){
		_n1[i]=(_n1[i-1]+i)%O;
	}
	for(int d=1;d<=n&&d<=m&&d<=r;d++){
		using sieve::mu;
		if(mu[d]<0){
			mu[d]=O-1;
		}
		for(int i=d;i<=n&&i<=r;i+=d){
			int tmpl=lend[i]/d,tmpr=rend[i]/d;
			int t=(lint)mu[d]*(tmpr-tmpl)%O;
			ans=(ans+t)%O,ansi=(ansi+(lint)i*t)%O;
			t=(lint)mu[d]*(_n1[tmpr]+O-_n1[tmpl])%O*d%O;
			ansj=(ansj+t)%O,ansij=(ansij+(lint)i*t)%O;
		}
	}
	ans=(lint)(n+1)*(m+1)%O*ans%O;
	ansi=(lint)(m+1)*ansi%O;
	ansj=(lint)(n+1)*ansj%O;
	return ((lint)ans+O-ansi+O-ansj+ansij)%O;
}
inline int calc2(int n,int m,int l,int r){
	return l<=1?((lint)n*(m+1)+(lint)(n+1)*m)%O:0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
#endif
	int n=ni,m=ni,l=ni,r=ni;
	int ans=(((lint)calc(n,m,l,r)<<1)+calc2(n,m,l,r))%O;
	printf("%d\n",ans);
	return 0;
}
