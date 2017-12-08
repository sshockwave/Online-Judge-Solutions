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
const int N=1000010,O=1000000007;
int f[N],_f[N];
int main(){
	int n=ni;
	f[0]=_f[0]=1;
	f[1]=n,_f[1]=n+1;
	for(int i=2;i<=n;i++){
		lint tmp=0;
		tmp+=f[i-1];
		if(i-3>=1){
			tmp+=_f[i-3]-_f[0];
		}
		tmp+=n-i+2;
		if(i==2){
			tmp--;
		}
		tmp+=(lint)(n-1)*(n-1)%O;
		f[i]=(tmp%O+O)%O;
		_f[i]=(_f[i-1]+f[i])%O;
	}
	printf("%d\n",f[n]);
	return 0;
}
