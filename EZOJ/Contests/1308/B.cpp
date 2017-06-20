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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010,MOD=100003;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline int sqr(const int &x){
	return mul(x,x);
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
bool light[N];
int rev[MOD];
struct pii{
	int a,b;
	inline void operator *= (const int &c){
		apmul(a,c),apmul(b,c);
	}
}f[N];
bool flag[N];
int main(){
	{//get rev
		rev[0]=0;
		rev[1]=1;
		for(int i=2;i<MOD;i++){
			rev[i]=sub(0,mul(MOD/i,rev[MOD%i]));
			assert(mul(i,rev[i])==1);
			assert(rev[i]);
		}
	}
	int n=ni,k=ni,cnt=0;
	{//get cnt
		for(int i=1;i<=n;i++){
			light[i]=ni;
		}
		for(int i=n;i>=1;i--){
			for(int j=i<<1;j<=n;j+=i){
				light[i]^=light[j];
			}
		}
		for(int i=1;i<=n;i++){
			cnt+=light[i];
		}
		if(cnt<=k){
			printf("%d\n",cnt);
			return 0;
		}
	}
	{//dp
		memset(f,0,sizeof(f));
		f[n].a=f[n].b=1;
		for(int i=n-1;i>k;i--){
			f[i]=f[i+1],f[i]*=mul(n-i,rev[n]);
			int g=sub(1,f[i].a);
			f[i].a=mul(i,rev[n]);
			apadd(f[i].b,1);
			assert(g);
			f[i]*=rev[g];
		}
		f[k].b=k;
		for(int i=k+1;i<=n;i++){
			apadd(f[i].b,mul(f[i].a,f[i-1].b));
			f[i].a=0;
		}
		for(int i=k+1;i<=n;i++){
			assert(sub(f[i].b,1)==add(mul(f[i-1].b,mul(i,rev[n])),mul(f[i+1].b,mul(n-i,rev[n]))));
		}
	}
	int ans=f[cnt].b;
	{//get ans
		for(int i=1;i<=n;i++){
			apmul(ans,i);
		}
	}
	printf("%d\n",ans);
}