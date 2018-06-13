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
const int N=100010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int ansa=0,ansb=0,ansf=0,ansn=0;
inline void Main(const int n,const int a,const int b){
	assert(a<=b);
	int cntn=0,cnta=0,cntf=0,cntfa=0;
	for(int i=1;i<=n;i++){
		const int x=ni%(a+b);
		++(x<a?cntn:x<b?cnta:x<a*2?cntf:cntfa);
	}
	cntn=fpow(2,cntn);
	//bob wins
	ansb=0;
	//first wins
	const int odd=cntf?fpow(2,cntf-1):0;
	const int eve=cntf?odd:1;
	ansf=(odd+(lint)eve*cntfa)%O*cntn%O;
	//second wins
	ansn=(lint)eve*cntn%O;
	//alice wins
	ansa=((lint)fpow(2,n)+O-ansf+O-ansn)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
#endif
	const int n=ni,a=ni,b=ni;
	if(a>b){
		Main(n,b,a);
		swap(ansa,ansb);
	}else{
		Main(n,a,b);
	}
	assert(ansa>=0&&ansb>=0&&ansf>=0&&ansn>=0);
	assert(((lint)ansa+ansb+ansf+ansn)%O==fpow(2,n));
	printf("%d %d %d %d\n",ansa,ansb,ansf,ansn);
	return 0;
}
