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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
const int N=100000;
char s[N];
inline bool check(){
	static char stk[N];
	int ss=0;
	for(int i=1;s[i];i++){
		if(ss&&stk[ss]==s[i]){
			ss--;
		}else{
			stk[++ss]=s[i];
		}
	}
	return ss==0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("swap.in","r",stdin);
	freopen("swap.out","w",stdout);
#endif
	scanf("%s",s+1);
	lint ans=0;
	for(int i=1;s[i];i++){
		for(int j=i;s[j];j++){
			if(s[i]==s[j])continue;
			swap(s[i],s[j]);
			ans+=check();
			swap(s[i],s[j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
