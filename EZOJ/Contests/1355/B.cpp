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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
const int N=2000010;
int a[N<<1];
inline void Main(){
	int n=ni,k=ni,f=ni,mx=0;
	memset(a,0,sizeof(a));
	for(int i=1,v;i<=n;a[v=ni]++,apmax(mx,v),i++);
	for(int i=1,ti=mx+k;i<=ti;a[i]+=a[i-1],i++);
	for(int i=1;i<=k;i++){
		if(a[i-1]<=f){
			printf("%d ",i);
		}
	}
	for(int i=k+1;i<=mx;i++){
		int cnt=0;
		for(int j=i;j<=mx;j+=i){
			cnt+=a[j+k]-a[j-1];
		}
		if(n-cnt<=f){
			printf("%d ",i);
		}
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mogician.in","r",stdin);
	freopen("mogician.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
