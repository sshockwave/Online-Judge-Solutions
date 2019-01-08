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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=30;
inline bool valid(lint n){
	static int stk[N];
	if(n<=0)return false;
	int ss=0;
	for(;n;stk[++ss]=n%10,n/=10);
	for(int i=1,j=ss;i<j;i++,j--){
		if(stk[i]!=stk[j])return false;
	}
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("number.in","r",stdin);
	freopen("number.ans","w",stdout);
#endif
	lint n=next_num<lint>();
	int ans=0;
	for(int i=1;i<n;i++){
		ans+=valid(i)&&valid(n-i);
	}
	printf("%d\n",ans);
	return 0;
}
