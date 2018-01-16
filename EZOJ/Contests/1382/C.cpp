#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
const int N=5000010,O=1004535809;//TODO
inline int grt(lint n){
	lint x=sqrt(n);
	for(;x*x<n;x++);
	for(;x*x>n;x--);
	return x;
}
int pri[N],ps=0;
int mu[N];
int mnpw[N],mnp[N];
int f[N],g[N],h[N];
bool np[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	mu[1]=1;
	memset(h,0,sizeof(h));
	for(lint i=1,sqi;sqi=i*i,sqi<n;i++){
		for(lint j=1,sqj;sqj=j*j,sqi+sqj<=n;j++){
			(h[sqi+sqj]+=i)%=O;
		}
	}
	g[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			pri[ps++]=i;
			mu[i]=-1;
			mnpw[i]=i;
			mnp[i]=i;
		}
		g[i]=((lint)g[i/mnp[i]]*mnp[i]+g[i/mnpw[i]])%O;
		for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
			np[t]=true;
			mnp[t]=p;
			if(i%p){
				mnpw[t]=p;
				mu[t]=-mu[i];
			}else{
				mnpw[t]=mnpw[i]*p;
				mu[t]=0;
				break;
			}
		}
	}
	memset(f,0,sizeof(f));
	for(int i=1,sqi;sqi=i*i,sqi<=n;i++){
		if(mu[i]==0)continue;
		int tmp=(lint)(O+mu[i])*i%O;
		for(int j=1,k=sqi;k<=n;j++,k+=sqi){
			f[k]=(f[k]+(lint)h[j]*tmp%O)%O;
		}
	}
	for(int i=1;i<=n;i++){
		f[i]=(f[i-1]+f[i])%O;
		g[i]=(g[i-1]+g[i])%O;
		h[i]=(h[i-1]+h[i])%O;
	}
}
inline int _n2(lint n){
	n%=O;
	lint m=n+1;
	if(n&1){
		m>>=1;
	}else{
		n>>=1;
	}
	return m*n%O;
}
lint overall;
int b_h[N];
inline int H(lint n){
	if(n<N)return h[n];
	int &bans=b_h[overall/n];
	if(bans!=-1)return bans;
	lint ans=0;
	for(lint i=1,sqi;sqi=i*i,sqi<=n;i++){
		ans+=i*grt(n-sqi)%O;
	}
	return bans=ans%O;
}
int b_f[N];
inline int F(lint n){
	if(n<N)return f[n];
	int &bans=b_f[overall/n];
	if(bans!=-1)return bans;
	lint ans=0;
	for(lint i=1,sqi;sqi=i*i,sqi<=n;i++){
		ans+=(lint)mu[i]*i*H(n/sqi)%O;
	}
	return bans=(ans%O+O)%O;
}
inline int G(lint n){
	if(n<N)return g[n];
	lint ans=0;
	for(lint l=1,r,d;l<=n;l=r+1){
		r=n/(d=n/l);
		ans+=(_n2(r)-_n2(l-1))*d%O;
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("div.in","r",stdin);
	freopen("div.out","w",stdout);
#endif
	sieve(N-1);
	lint n=overall=next_num<lint>();
	lint ans=0;
	int cur,last=0;
	memset(b_f,-1,sizeof(b_f));
	memset(b_h,-1,sizeof(b_h));
	for(lint l=1,r,d;l<=n;l=r+1,last=cur){
		r=n/(d=n/l);
		cur=F(r);
		ans+=(lint)(cur+O-last)*G(d)%O;
	}
	ans=(ans<<1)%O;
	last=0;
	for(lint l=1,r,d;l<=n;l=r+1,last=cur){
		r=n/(d=n/l);
		cur=_n2(r);
		ans+=(cur+O-last)%O*d%O;
	}
	printf("%lld\n",ans%O);
	return 0;
}
