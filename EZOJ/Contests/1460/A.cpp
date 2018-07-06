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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,INF=0x7f7f7f7f;
int a[N];
char str[30];
inline int calc(const int n,const int g){
	int last=a[1];
	int cnt=1;
	for(int i=2;i<=n;i++){
		if(a[i]-last>g){
			++cnt;
			last=a[i];
		}
	}
	return cnt;
}
inline int Main(const int n){
	scanf("%s",str);
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	if(((n&1)&&str[0]=='s')||((n&1)==0&&str[0]=='l')){
		const int g=((n-2+(str[0]=='s'))>>1)+2;
		assert(g<=n);
		int mn=INF;
		for(int i=g;i<=n;i++){
			apmin(mn,a[i]-a[i-g+1]);
		}
		return mn;
	}
	int l=0,r=a[n]-a[1];
	while(l<r){
		const int m=(l+r)>>1;
		if(calc(n,m)<=((n+1)>>1)){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	int n;
	for(;scanf("%d",&n)!=EOF;){
		printf("%d\n",Main(n));
	}
	return 0;
}
