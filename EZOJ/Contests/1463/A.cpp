#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,sizeof(a[0])*n);}
template<class T>T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=510,A=2333333;
namespace getans{
	struct frac{
		int a,b;
		frac(int _a,int _b){
			const int g=gcd(_a,_b);
			a=_a/g,b=_b/g;
		}
		inline friend bool operator < (const frac &a,const frac &b){
			return a.a!=b.a?a.a<b.a:a.b<b.b;
		}
	};
	set<frac>s;
	lint _a[N],_a2[N];
	inline int main(const int a[],const int n){
		s.clear();
		_a[0]=_a2[0]=0;
		for(int i=1;i<=n;i++){
			_a[i]=_a[i-1]+a[i];
			_a2[i]=_a2[i-1]+sqr<lint>(a[i]);
		}
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				const int len=j-i+1;
				lint up=_a2[j]-_a2[i-1];
				up*=len;
				up-=sqr(_a[j]-_a[i-1]);
				s.insert(frac(up,sqr<lint>(len)));
			}
		}
		return s.size();
	}
}
int a[N],n;
inline int gen(){
	return rand()%A;
}
inline int f(int n){
	return (n*(n-1)>>1)+1;
}
inline void Main(const int k){
	if(k<=500){
		n=k;
		for(int i=1;i<=n;i++){
			a[i]=i;
		}
		return;
	}
	for(int &i=n=1;f(i)<k;i++);
	int ls=0;
	int cur=f(n);
	for(int len=n;len>=2;len--){
		const int dt=len*(len-1)>>1;
		for(;k<=cur-dt;cur-=dt){
			const int v=gen();
			for(int tot=len;tot--;){
				a[++ls]=v;
			}
			a[++ls]=gen();
		}
	}
	assert(ls<=n);
	for(int &i=ls;i<n;a[++i]=gen());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("var.in","r",stdin);
	freopen("var.out","w",stdout);
#endif
	srand(26126);
	const int k=ni;
	for(;Main(k),getans::main(a,n)!=k;);
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
	return 0;
}
