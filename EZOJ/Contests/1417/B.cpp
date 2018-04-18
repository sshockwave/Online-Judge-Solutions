#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=1010;
int n,f,R,r;
int s1[N];
db s2[N],lend[N],rend[N];
inline db calc(db x){
	db ans=0;
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
		if(s1[i]==f){
			cnt1++;
		}else if(s1[i]>f&&(lend[i]<x&&x<rend[i])){
			cnt2++;
		}else{
			ans+=sqr(s2[i]/(s2[i]-x));
		}
	}
	return (ans+cnt1)*sqr(r)/sqr(R)+cnt2;
}
inline db Main(){
	n=ni,f=ni,R=ni,r=ni;
	if(r>=R)return n;
	for(int i=1;i<=n;i++){
		s1[i]=-ni;
		s2[i]=(db)s1[i]/(s1[i]-f)*f;
		if(s1[i]>f){
			lend[i]=s2[i]*(1-(db)r/R);
			rend[i]=s2[i]*(1+(db)r/R);
		}
	}
	db ans=calc(0);
	for(int i=1;i<=n;i++){
		if(s1[i]>f){
			apmax(ans,calc(lend[i]));
			apmax(ans,calc(rend[i]));
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("physics.in","r",stdin);
	freopen("physics.out","w",stdout);
#endif
	printf("%.10Lf\n",Main());
	return 0;
}
