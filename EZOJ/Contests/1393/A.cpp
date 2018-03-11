#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
uint a[N];
namespace lb{
	const int N=30;
	uint a[N];
	inline void init(){
		memset(a,0,sizeof(a));
	}
	inline bool ins(uint x){
		for(int i=N-1;i>=0;i--){
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					return true;
				}
			}
		}
		return false;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=next_num<uint>();
	}
	for(int tot=ni;tot--;){
		int op=ni,l=ni,r=ni;
		if(op==0){
			bool flag=false;
			lb::init();
			for(int i=l;i<=r;i++){
				flag|=!lb::ins(a[i]);
				if(flag)break;
			}
			puts(flag?"Yes":"No");
		}else{
			uint x=next_num<uint>();
			for(int i=l;i<=r;i++){
				if(op==1){
					a[i]&=x;
				}else if(op==2){
					a[i]|=x;
				}else if(op==3){
					a[i]^=x;
				}
			}
		}
	}
	return 0;
}
