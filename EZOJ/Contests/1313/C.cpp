#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
#define cout cerr
#undef assert
#define assert(x) {};
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
const int R=100010,MOD=1000000007;
int p,r;
lint n;
inline int sqrt(lint n){
	lint i=0;
	for(;i*i<n;i++);
	return i;
}
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
inline int _n1(lint n){
	const static int rev2=(MOD+1)>>1;
	n%=MOD;
	return mul(mul(n,n+1),rev2);
}
namespace MillerRabin{
	inline lint mul(lint a,const lint &b,const lint &p){
		a=a*b-(lint)((double)a/p*b+0.5)*p;
		return a<0?a+p:a;
	}
	inline lint fpow(lint x,lint n,const lint &p=MOD){
		lint ans=1;
		for(;n;n>>=1,x=mul(x,x,p)){
			if(n&1){
				ans=mul(ans,x,p);
			}
		}
		return ans;
	}
	inline bool testi(int p){
		if(p%3==0||p%5==0||p%7==0||p%11==0||p%13==0||p%17==0||p%19==0){
			return false;
		}
		int n=p-1,cnt=0;
		lint w=1,x=3;
		for(;(n&1)==0;n>>=1,cnt++);
		for(;n;n>>=1,(x*=x)%=p){
			if(n&1){
				(w*=x)%=p;
			}
		}
		if(w==1){
			return true;
		}
		for(;cnt--;w=mul(w,w,p)){
			if(w==p-1){
				return true;
			}
		}
		return false;
	}
	inline bool testl(lint p){
		if(p%3==0||p%5==0||p%7==0||p%11==0||p%13==0||p%17==0||p%19==0||p==3493072871ll){
			return false;
		}
		lint n=p-1;
		int cnt=0;
		for(;(n&1)==0;n>>=1,cnt++);
		n=fpow(3,n,p);
		if(n==1){
			return true;
		}
		for(;cnt--;n=mul(n,n,p)){
			if(n==p-1){
				return true;
			}
		}
		return false;
	}
	inline bool isp(lint p){//accurate only to 4034k-1
		return p<=2147483647?testi(p):testl(p);
	}
}
namespace sieve{
	bool np[R];
	int prime[R],_prime[R],_fprime[R],ps=0;
	int wu[R],mnfac[R],mnp[R];//wu%=p
	inline void work(){
		memset(np,0,sizeof(np));
		_prime[0]=_fprime[0]=0,wu[1]=1;
		for(int i=2;i<=r;i++){
			if(!np[i]){
				prime[++ps]=i;
				_prime[ps]=add(_prime[ps-1],i);
				wu[i]=(i+1)%p;
				_fprime[ps]=_fprime[ps-1];
				if(wu[i]){
					apadd(_fprime[ps],i);
				}
				mnfac[i]=mnp[i]=i;
			}else if(mnfac[i]==i){
				wu[i]=(wu[i/mnp[i]]*mnp[i]+1)%p;
			}else{
				wu[i]=wu[mnfac[i]]*wu[i/mnfac[i]]%p;
			}
			assert(i%mnp[i]==0&&i%mnfac[i]==0&&i/mnfac[i]%mnp[i]);
			for(int j=1,cur=2;j<=ps&&i*cur<=r;cur=prime[++j]){
				np[i*cur]=true,	mnp[i*cur]=cur;
				if(i%cur==0){
					assert(mnp[i]==cur);
					mnfac[i*cur]=mnfac[i]*cur;
					break;
				}else{
					mnfac[i*cur]=cur;
				}
			}
		}
	}
}
namespace mapper{
	lint id[R<<1];
	int mxp[R<<1],gs=0;
	inline int dfn(lint x){
		assert(id[x<=r?x:gs-(n/x)+1]==x);
		return x<=r?x:gs-(n/x)+1;
	}
	inline void init(){
		int i=1;
		for(;i<=r;i++){
			id[++gs]=i;
		}
		for(;i&&id[gs]>=n/i;i--);
		for(;i>=1;i--){
			id[++gs]=n/i;
		}
		for(int i=gs,j=sieve::ps;i>=1;i--){//get mxp
			for(;sieve::prime[j]>id[i];j--);
			mxp[i]=j;
		}
	}
}
namespace G{
	int f[R<<1],g[R<<1],tag[R<<1];
	inline int getg(int i,int j){
		assert(tag[j]<=i);
		apmin(i,mapper::mxp[j]);
		if(tag[j]<i){
			using namespace sieve;
			apsub(g[j],sub(_prime[i],_prime[tag[j]])),tag[j]=i;
		}
		return g[j];
	}
	inline void init(){
		if(p==2){
			return;
		}
		using namespace mapper;
		{//get f
			memset(f,0,sizeof(f));
#define gap 4034
			int j=1;
			lint i=gap;
			for(;i<=r;i+=gap);
			for(lint _=n+1;i<=_;i+=gap){
				if(MillerRabin::isp(i-1)){
					for(;id[j]<i-1;j++);
					apadd(f[j],(i-1)%MOD);
				}
			}
			for(int i=1;i<=gs;i++){
				apadd(f[i],f[i-1]);
			}
#undef gap
		}
		{//get g
			using namespace sieve;
			memset(tag,0,sizeof(tag));
			for(int i=1;i<=gs;i++){
				g[i]=_n1(id[i]);
			}
			for(int i=1,cur=2;i<=ps;cur=prime[++i]){
				lint p2=(lint)cur*cur;
				for(int j=gs;id[j]>=p2;j--){
					assert(tag[j]==i-1);
					apsub(g[j],mul(cur,getg(i-1,dfn(id[j]/cur)))),tag[j]=i;
				}
			}
		}
	}
	inline int get(lint n){
		if(p==2){
			if(n<=1){
				return 0;
			}
			return r>=2?0:2;
		}
		int j=mapper::dfn(n);
		return sub(getg(sieve::ps,j),add(f[j],1));
	}
}
namespace F{
	int f[R<<1];
	bool tag[R<<1];
	inline int getf(int i,int j){
		if(tag[j]){
			return f[j];
		}
		using namespace sieve;
		using namespace mapper;
		return i>mxp[j]?1:add(1,sub(_fprime[mxp[j]],_fprime[i-1]));
	}
	inline void init(){
		using namespace mapper;
		using namespace sieve;
		memset(tag,0,sizeof(tag));
		for(int i=ps,cur=prime[i];i>=1;cur=prime[--i]){
			static lint pw[50]={1};
			static int pwm[50]={1},wu[50]={1};
			lint p2=(lint)cur*cur;
			for(int j=0;pw[j]<=n;j++){
				pw[j+1]=pw[j]*cur;
				pwm[j+1]=pw[j+1]%MOD;
				wu[j+1]=(wu[j]*cur+1)%p;
			}
			for(int j=gs;id[j]>=p2;j--){
				if(!tag[j]){
					f[j]=getf(i+1,j);
					tag[j]=true;
				}
				for(int k=1;pw[k]<=id[j];k++){
					if(wu[k]){
						apadd(f[j],mul(pwm[k],getf(i+1,dfn(id[j]/pw[k]))));
					}
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bu.in","r",stdin);
	freopen("bu.out","w",stdout);
#endif
	n=nl,p=ni,r=sqrt(n);
	sieve::work(),mapper::init(),G::init(),F::init();
	int ans=F::getf(sieve::ps,mapper::gs);
	for(int i=1;i<=r;i++){
		if(sieve::wu[i]){
			apadd(ans,mul(i,G::get(n/i)));
		}
	}
	printf("%d\n",sub(_n1(n),ans));
}
