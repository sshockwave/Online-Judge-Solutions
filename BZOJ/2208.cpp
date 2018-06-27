#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <bitset>
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
const int N=2010;
bitset<N>to[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("connect.in","r",stdin);
	freopen("connect.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		static char s[N];
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			if(s[j]-'0'){
				to[i].set(j);
			}
		}
		to[i].set(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j&&to[j].test(i)){
				to[j]|=to[i];
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=to[i].count();
	}
	printf("%d\n",ans);
	return 0;
}
