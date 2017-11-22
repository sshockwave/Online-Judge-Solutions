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
int a[N];
inline bool Main(){
	int n=ni,mx=0,mn=N;
	for(int i=1;i<=n;apmax(mx,a[i]=ni),apmin(mn,a[i]),i++);
	if(mx==mn)return mx==n-1||n>=(mx<<1);
	if(mn+1<mx)return false;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=a[i]==mn;
	}
	return mx>cnt&&n-cnt>=((mx-cnt)<<1);
}
int main(){
	puts(Main()?"Yes":"No");
	return 0;
}
