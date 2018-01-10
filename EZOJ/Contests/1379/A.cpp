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
int a[N],b[N],c[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("dalao.in","r",stdin);
	freopen("dalao.out","w",stdout);
#endif
	int n=ni;
	IO::seed=next_num<lint>(),IO::gen(a,n);
	IO::seed=next_num<lint>(),IO::gen(b,n);
	IO::seed=next_num<lint>(),IO::gen(c,n);
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans+=a[i]<a[j]&&b[i]<b[j]&&c[i]<c[j];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
