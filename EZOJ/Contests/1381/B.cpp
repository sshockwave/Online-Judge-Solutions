#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
const int N=4000010;
lint overall;
uint overallk;
struct DuSieve{
	uint a[N],b[N];
	bool tag[N];
	DuSieve(){
		memset(a,0,sizeof(a));
		memset(tag,0,sizeof(tag));
	}
	inline virtual uint _dirchlet(lint n){return 0;}
	inline virtual uint _g(lint n){return 0;}
	inline uint operator [] (lint n){
		if(n<N)return a[n];
		uint div=overall/n;
		if(tag[div])return b[div];
		tag[div]=true;
		uint ans=_dirchlet(n);
		uint cur,last=_g(1);
		for(lint l=2,r,d;l<=n;l=r+1,last=cur){
			r=n/(d=n/l);
			cur=_g(r);
			ans-=(cur-last)*this->operator[](d);
		}
		return b[div]=ans;
	}
};
struct classPhi:DuSieve{
	inline uint _dirchlet(lint n){
		lint m=n+1;
		if(n&1){
			m>>=1;
		}else{
			n>>=1;
		}
		return m*n;
	}
	inline uint _g(lint n){return n;}
}_phi;
struct classGamma:DuSieve{
	inline uint _dirchlet(lint n){
		uint x=sqrt(n);
		for(;(lint)x*x<n;x++);
		for(;(lint)x*x>n;x--);
		return x;
	}
	inline uint _g(lint n){return n;}
}_gam;
int prime[N],ps=0;
bool np[N];
int mcnt[N]={0,0},mu[N]={0,1};
struct classF{
	uint a[N];
	classF(){
		memset(a,0,sizeof(a));
	}
	inline uint operator [] (lint n){
		if(n<N)return a[n];
		static lint* pw=new lint[N];
		uint rt;
		for(uint &i=rt=1;(lint)i*i<=n;i++){
			pw[i]=i;
		}
		uint ans=0;
		for(uint d=1;d<=overallk;d++){
			for(uint i=1;i<rt&&(lint)pw[i]*i<=n;i++){
				pw[i]*=i;
				ans+=(d&1?1:(_gam.a[i]-_gam.a[i-1]))*mu[i]*_gam[n/pw[i]];
			}
		}
		return ans;
	}
}F;
inline int gcnt(int n,int p){
	int cnt=0;
	for(;n%p==0;n/=p,cnt++);
	return cnt;
}
inline void sieve(int n){
	memset(np,0,sizeof(np));
	_phi.a[1]=_gam.a[1]=1;
	F.a[1]=overallk;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mcnt[i]=1;
			mu[i]=-1;
			_phi.a[i]=i-1;
			_gam.a[i]=-1;
		}
		for(int j=0,p,t;j<ps&&(p=prime[j],t=i*p,t<=n);j++){
			np[t]=true;
			mcnt[t]=max(gcnt(i,p)+1,mcnt[i]);
			_gam.a[t]=-_gam.a[i];
			if(i%p){
				mu[t]=-mu[i];
				_phi.a[t]=_phi.a[i]*(p-1);
			}else{
				mu[t]=0;
				_phi.a[t]=_phi.a[i]*p;
				break;
			}
		}
		_phi.a[i]+=_phi.a[i-1];
		F.a[i]=F.a[i-1]+max((int)overallk-mcnt[i]+1,0)*_gam.a[i];
		_gam.a[i]+=_gam.a[i-1];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	lint n=overall=next_num<lint>();
	overallk=ni;
	sieve(N-1);
	uint ans=0,cur,last=0;
	for(lint l=1,r,d;l<=n;l=r+1,last=cur){
		r=n/(d=n/l);
		ans+=((cur=F[r])-last)*((_phi[d]<<1)-1);
	}
	printf("%u\n",ans&((1<<30)-1));
	return 0;
}
