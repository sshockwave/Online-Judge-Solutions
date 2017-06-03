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
	if(a>b){a=b;}
}
const int N=1000000,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apsub(int &a,const int &b){
	a=sub(a,b);
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
int phi[N],_phi[N],prime[N],ptop=0;
bool np[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	_phi[1]=phi[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			phi[i]=i-1;
		}
		_phi[i]=add(_phi[i-1],mul(phi[i],i));
		for(int j=0,cur=2;i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				phi[i*cur]=cur*phi[i];
				break;
			}else{
				phi[i*cur]=phi[i]*phi[cur];
			}
		}
	}
}
inline int prephi(int n){
	if(n<N){
		return _phi[n];
	}
	static map<int,int>cache;
	map<int,int>::iterator it=cache.find(n);
	if(it!=cache.end()){
		return it->second;
	}
	static const int rev2=fpow(2,MOD-2),rev6=fpow(6,MOD-2);
	int ans=mul(mul(n,add(n,1)),mul(add(mul(n,2),1),rev6));
	for(int l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		apsub(ans,mul(prephi(n/l),mul(mul(add(l,r),r-l+1),rev2)));
	}
	return cache[n]=ans;
}
int main(){
	sieve();
	printf("1\n%d\n",prephi(ni));
}