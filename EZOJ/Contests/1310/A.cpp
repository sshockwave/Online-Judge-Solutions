#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=1000000;
int MOD;
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
inline void apsub(int &a,const int &b){
	a=sub(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int _n1(int n){
	int a=n,b=n+1;
	if(a&1){
		b>>=1;
	}else{
		a>>=1;
	}
	return mul(a,b);
}
inline int _n2(int n){
	int a=n,b=n+1,c=(n<<1)+1;
	if(a%3==0){
		a/=3;
	}else if(b%3==0){
		b/=3;
	}else{
		c/=3;
	}
	if((a&1)==0){
		a>>=1;
	}else if((b&1)==0){
		b>>=1;
	}else{
		c>>=1;
	}
	return mul(mul(a,b),c);
}
inline int _n3(int n){
	int a=n,b=n+1;
	if(a&1){
		b>>=1;
	}else{
		a>>=1;
	}
	apmul(a,b);
	return mul(a,a);
}
int prime[N],ps=0;
bool np[N];
int phi[N],prephi[N],prephi1[N],prephi2[N];
inline int _phi(int n){
	if(n<N){
		return prephi[n];
	}
	static map<int,int>cache;
	map<int,int>::iterator it;
	it=cache.find(n);
	if(it!=cache.end()){
		return it->second;
	}
	int ans=_n1(n);
	for(int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		apsub(ans,mul(r-l+1,_phi(n/l)));
	}
	return cache[n]=ans;
}
inline int _phi1(int n){
	if(n<N){
		return prephi1[n];
	}
	static map<int,int>cache;
	map<int,int>::iterator it;
	it=cache.find(n);
	if(it!=cache.end()){
		return it->second;
	}
	int ans=_n2(n);
	for(int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		apsub(ans,mul(sub(_n1(r),_n1(l-1)),_phi1(n/l)));
	}
	return cache[n]=ans;
}
inline int _phi2(int n){
	if(n<N){
		return prephi2[n];
	}
	static map<int,int>cache;
	map<int,int>::iterator it;
	it=cache.find(n);
	if(it!=cache.end()){
		return it->second;
	}
	int ans=_n3(n);
	for(int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		apsub(ans,mul(sub(_n2(r),_n2(l-1)),_phi2(n/l)));
	}
	return cache[n]=ans;
}
inline void sieve(){
	memset(np,0,sizeof(np));
	phi[1]=prephi[1]=prephi1[1]=prephi2[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			phi[i]=(i-1)%MOD;
			prime[ps++]=i;
		}
		prephi[i]=add(prephi[i-1],phi[i]);
		prephi1[i]=add(prephi1[i-1],mul(phi[i],i));
		prephi2[i]=add(prephi2[i-1],mul(phi[i],mul(i,i)));
		for(int j=0,cur=2;j<ps&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				phi[i*cur]=mul(phi[i],cur);
				break;
			}else{
				phi[i*cur]=mul(phi[i],cur-1);
			}
		}
	}
}
inline int work(int n){
	if(n==1||MOD==1){
		return 0;
	}
	sieve();
	int ans=0;
	apadd(ans,mul(mul(2,mul(n,n)),sub(_phi(n),_phi(1))));
	apsub(ans,mul(mul(3,n),sub(_phi1(n),_phi1(1))));
	apadd(ans,sub(_phi2(n),_phi2(1)));
	apadd(ans,mul(n-1,n-1));
	apmul(ans,2);
	apadd(ans,mul(mul(n,n-1),2));
	return ans;
}
int main(){
	int n=ni;
	MOD=ni;
	printf("%d\n",work(n));
}