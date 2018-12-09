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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=42;
char s[N];
int lima;
bool check(int n){
	int cnta=0,cntb=0;
	int pa=0,pb=n-1;
	for(int r=0;;r^=1){
		for(;s[pa]=='o';++cnta,pa++);
		for(;s[pb]=='x';++cntb,pb--);
		if(pa>pb)return cnta>cntb&&cnta>=lima;
		r==0?++pa:--pb;
	}
}
lint dfs(int x){
	if(s[x]==0)return check(x);
	if(s[x]=='?'){
		s[x]='o';
		lint ans=dfs(x+1);
		s[x]='x';
		ans+=dfs(x+1);
		s[x]='?';
		return ans;
	}
	return dfs(x+1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%s",s);
	lima=ni;
	printf("%lld\n",dfs(0));
	return 0;
}
