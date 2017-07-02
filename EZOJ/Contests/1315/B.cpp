#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=510,R=510,MOD=998244353;
inline int mod(int x){
	return x>=MOD?x-MOD:x;
}
inline lint mod(lint x){
	return x>=MOD?x%MOD:x;
}
inline int add(const int &a,const int &b){
	return mod(a+b);
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return mod((lint)a*b);
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apsub(int &a,const int &b){
	a=sub(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
int n,r[N],f[N*R];
int main(){
#ifndef ONLINE_JUDGE
	freopen("hole.in","r",stdin);
	freopen("hole.out","w",stdout);
#endif
	n=ni;
	int s=ni,sum=0,fac=1;
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int i=1;i<=n;i++){
		r[i]=ni;
		apmul(fac,i);
		if(r[i]>=s){
			continue;
		}
		sum+=r[i];
		apmin(sum,s);
		for(int j=sum;j>=r[i];j--){
			apsub(f[j],f[j-r[i]]);
		}
	}
	lint ans=0;
	for(int i=0;i<=sum;i++){
		if(f[i]){
			ans+=mul(f[i],fpow(s-i,n));
		}
	}
	printf("%d\n",mul(ans%MOD,fpow(fac,MOD-2)));
}
