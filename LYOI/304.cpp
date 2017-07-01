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
#define nl (next_num<lint>())
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
const static int D=64;
ull a[D];
inline void ins(ull x){
	for(int i=D-1;i>=0;i--){
		if((x>>i)&1){
			if(a[i]){
				x^=a[i];
			}else{
				a[i]=x;
				return;
			}
		}
	}
}
int main(){
	int n=ni;
	ull xsum=0;
	for(int i=1;i<=n;i++){
		ull cur=next_num<ull>();
		xsum^=cur;
		ins(cur);
	}
	ull x=0;
	for(int i=D-1;i>=0;i--){
		if((xsum^x)+x<(xsum^x^a[i])+(x^a[i])){
			x^=a[i];
		}
	}
	printf("%llu\n",x);
}
