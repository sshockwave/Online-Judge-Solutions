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
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int main(){
	int n=ni;
	lint f[3]={ni,-LINF,-LINF};
	for(int i=2;i<=n;i++){
		char c;
		while(c=getchar(),c!='+'&&c!='-');
		int val=ni;
		if(c=='+'){
			f[0]+=val;
		}else{
			f[2]=f[1],f[1]=f[0],f[0]=-LINF;
		}
		if(f[1]!=-LINF){
			f[1]-=val;
			if(f[2]!=-LINF){
				f[2]+=val;
				apmax(f[1],f[2]);
			}
			apmax(f[0],f[1]);
		}
		assert(f[0]>=f[1]&&f[1]>=f[2]);
	}
	printf("%lld\n",f[0]);
	return 0;
}
