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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2000010;
namespace IO{
	lint seed;
	lint rng(){
		return seed=((seed*19260817)^233333)&((1<<24)-1);
	}
	inline void gen(int a[],int n){
		for(int i=1;i<=n;i++){
			a[i]=i;
		}
		for(int i=1;i<=n;i++){
			swap(a[i],a[rng()%i+1]);
		}
	}
}
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
}
int pos[N],n;
inline lint work(const int a[],const int b[]){
	for(int i=1;i<=n;i++){
		pos[a[i]]=i;
	}
	B::init(n);
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=B::sum(b[pos[i]]);
		B::add(b[pos[i]],1);
	}
	return ans;
}
int a[N],b[N],c[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("dalao.in","r",stdin);
	freopen("dalao.out","w",stdout);
#endif
	n=ni;
	IO::seed=next_num<lint>(),IO::gen(a,n);
	IO::seed=next_num<lint>(),IO::gen(b,n);
	IO::seed=next_num<lint>(),IO::gen(c,n);
	printf("%lld\n",(work(a,b)+work(b,c)+work(c,a)-(((lint)n*(n-1))>>1))>>1);
	return 0;
}
