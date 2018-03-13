#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <algorithm>
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
const int N=160000,O=998244353;
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
namespace gmath{
	int fac[N],invfac[N];
	inline void init(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int c(int n,int k){
		assert(k<=n);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
namespace poly{
	const int SH=18,N=1<<SH,g=3;
	int sh,n,invn,w[N],r[N];
	inline void clr(int a[],int x=0){
		memset(a+x,0,(n-x)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		lint wn=fpow(g,(O-1)>>sh);
		w[0]=1,r[0]=0;
		for(int i=1;i<n;i++){
			w[i]=w[i-1]*wn%O;
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
		}
	}
	inline void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=poly::w[j<<(sh-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
namespace mem{
	const int N=::N*20;
	int a[N],*b;
	inline void init(){
		b=a;
	}
	inline int* New(int len){
		return b+=len,b-len;
	}
}
struct polysh{
	int *a,len,sh;//x^(len-1)
	polysh(int _len,int _sh):a(mem::New(_len)),len(_len),sh(_sh){}
	inline friend bool operator < (const polysh &a,const polysh &b){
		return a.len>b.len;
	}
};
int p[N],a[poly::N],b[poly::N];
inline int Main(){
	int n=ni,mx=ni;
	priority_queue<polysh>q;
	for(int i=1;i<=n;i++){
		p[i]=ni;
	}
	mem::init();
	gmath::init(n);
	for(int i=1;i<=n;i++){
		if(p[i]){
			int cnt=0;
			for(int j=i;p[j];cnt++){
				int k=j;
				j=p[j],p[k]=0;
			}
			polysh a(cnt,1);
			for(int i=1;i<=cnt;i++){
				a.a[i-a.sh]=gmath::c(cnt,i);
			}
			q.push(a);
		}
	}
	while(q.size()>1){
		polysh f1=q.top(),f2=(q.pop(),q.top());
		q.pop();
		if(f1.sh+f2.sh>mx)return 0;
		polysh f3((f1.len-1)+(f2.len-1)+1,f1.sh+f2.sh);
		memcpy(a,f1.a,f1.len*sizeof(a[0]));
		memcpy(b,f2.a,f2.len*sizeof(b[0]));
		using namespace poly;
		init(f3.len);
		clr(a,f1.len),ntt(a);
		clr(b,f2.len),ntt(b);
		for(int i=0;i<poly::n;i++){
			a[i]=(lint)a[i]*b[i]%O;
		}
		ntt(a,-1);
		memcpy(f3.a,a,f3.len*sizeof(a[0]));
		q.push(f3);
	}
	polysh a=q.top();
	return (lint)a.a[mx-a.sh]*inv(gmath::c(n,mx))%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bishop.in","r",stdin);
	freopen("bishop.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
