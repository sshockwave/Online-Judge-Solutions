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
const int N=100010,SH=18;
char s[N];
int nxtdiff[N][SH],lb[N];
inline bool Main(){
	int l=ni-1,r=ni-1;
	return r<nxtdiff[l][lb[r-l+1]];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("king.in","r",stdin);
	freopen("king.out","w",stdout);
#endif
	int n=ni,tot=ni;
	scanf("%s",s);
	for(int i=1;i<=n;i++){
		lb[i]=(i&1)==0?lb[i>>1]+1:0;
	}
	for(int j=0;(1<<j)<=n;j++){
		for(int i=n-(1<<j);i>=0;i--){
			nxtdiff[i][j]=s[i]==s[i+(1<<j)]?nxtdiff[i+1][j]:(i+(1<<j));
		}
	}
	for(;tot--;puts(Main()?"ephemeral":"endless"));
	return 0;
}
