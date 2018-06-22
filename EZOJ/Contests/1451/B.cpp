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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010;
namespace manacher{
	int a[N],n;
	inline void init(){
		a[n=0]=-1;
		a[++n]=0;
	}
	inline void fixup(){
		a[n+1]=-2;
	}
	inline void psh(int x){
		a[++n]=x,a[++n]=0;
	}
	int rad[N];
	inline lint main(){
		lint ans=0;
		for(int i=1,j=0;i<=n;i++){
			rad[i]=i<=j+rad[j]?min(j+rad[j]-i,rad[j*2-i]):0;
			for(int &k=rad[i];a[i-k-1]==a[i+k+1];k++);
			ans+=(rad[i]+1)>>1;
		}
		return ans;
	}
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pal.in","r",stdin);
	freopen("pal.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int tot=ni;tot--;){
		manacher::init();
		using manacher::psh;
		const int k=ni,l=ni;
		for(int i=1;i<=k;i++){
			int x=ni;
			for(int tt=l;tt--;){
				psh(a[x++]);
			}
		}
		manacher::fixup();
		printf("%lld\n",manacher::main());
	}
	return 0;
}
