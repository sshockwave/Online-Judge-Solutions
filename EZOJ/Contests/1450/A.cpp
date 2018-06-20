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
const int O=998244353;
lint ex_gcd(lint a,lint b,lint &x,lint &y){//ax+by==d
	if(b==0)return x=1,y=0,a;
	const lint d=ex_gcd(b,a%b,y,x);
	return y-=a/b*x,d;
}
lint a,b;
int solve(const lint u,const lint v){//f(a)==u,f(b)==v
	if(u==0||v==0)return u==0&&v==0;
	if(a==1&&b==1)return u==v?-1:0;
	if(a==b&&u!=v)return 0;
	lint k1,k2;
	lint d=ex_gcd(a,b,k1,k2);
	if((u-v)%d)return 0;
	k2=-k2;
	k1*=(u-v)/d,k2*=(u-v)/d;//cout
	{
		assert(a*k1-b*k2==u-v);
		lint q=0;
		if(k1<0){
			apmax(q,(-k1+b/d-1)/(b/d));
		}
		if(k2<0){
			apmax(q,(-k2+a/d-1)/(a/d));
		}
		k1+=b/d*q,k2+=a/d*q;
		assert(a*k1-b*k2==u-v);
	}
	for(;k1>=b/d&&k2>=a/d;k1-=b/d,k2-=a/d);
	lint ans=0;
	for(;k1*a<=u&&k2*b<=v;k1+=b/d,k2+=a/d){
		const int t=solve(k1,k2);
		if(t<0)return -1;
		ans+=t;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("polynomial.in","r",stdin);
	freopen("polynomial.out","w",stdout);
#endif
	lint c;
	for(;scanf("%lld%lld%lld",&a,&b,&c)!=EOF;){
		const int ans=solve(b,c);
		if(ans<0){
			puts("infinity");
		}else{
			printf("%d\n",ans);
		}
	}
	return 0;
}
