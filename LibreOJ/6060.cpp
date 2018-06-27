#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
const int N=100010;
ull s;
namespace lb{
	const int logN=64;
	ull a[logN];
	int blst[logN],ls;
	inline void init(){
		memset(a,0,sizeof(a));
		ls=0;
		for(int i=logN-1;i>=0;i--){
			if((s>>i)&1){
				blst[ls++]=i;
			}
		}
		for(int i=logN-1;i>=0;i--){
			if(((s>>i)&1)==0){
				blst[ls++]=i;
			}
		}
	}
	inline void ins(lint x){
		for(int p=0;p<ls;p++){
			int i=blst[p];
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					break;
				}
			}
		}
	}
	inline ull work(){
		ull ans=0;
		for(int p=0;p<ls;p++){
			const int i=blst[p];
			if(((ans>>i)&1)==0&&a[i]){
				ans^=a[i];
			}
		}
		return ans;
	}
}
ull a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("set.in","r",stdin);
	freopen("set.out","w",stdout);
#endif
	const int n=ni;
	s=0;
	for(int i=1;i<=n;i++){
		s^=a[i]=next_num<ull>();
	}
	lb::init();
	for(int i=1;i<=n;i++){
		lb::ins(a[i]);
	}
	printf("%llu\n",s^lb::work());
	return 0;
}
