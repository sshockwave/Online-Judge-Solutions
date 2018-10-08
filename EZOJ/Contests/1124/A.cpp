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
const int N=9,O=998244353;
int n;
lint lim[N];
int f[1<<N];
inline void apadd(int &a,const int &b){
	a=(a+b)%O;
}
inline int work(){
	mset(f,0,1<<n);
	f[0]=1;
	const int sn=1<<n;
	for(int i=51;i>=0;i--){
		int bmask=0;
		for(int p=0;p<n;p++){
			bmask|=((lim[p]>>i)&1)<<p;
		}
		for(int j=sn-1;j>=0;j--){
			const int F=f[j];
			if(F==0)continue;
			f[j]=0;
			int dc=1<<n;
			for(int tt=0;tt<=n;tt++){
				dc>>=1;
				if((dc&(j|bmask))==dc){
					apadd(f[j|(dc^bmask)],F);
				}
			}
		}
	}
	lint ans=0;
	for(int j=0;j<sn;j++){
		ans+=f[j];
	}
	return ans%O;
}
lint liml[N],limr[N];
int solve(int n){
	if(n==0)return work();
	--n;
	lim[n]=limr[n];
	int ans=solve(n);
	if(liml[n]<=0)return ans;
	lim[n]=liml[n]-1;
	return (ans+O-solve(n))%O;
}
inline int Main(){
	n=ni;
	for(int i=0;i<n;i++){
		liml[i]=next_num<lint>()-1;
	}
	for(int i=0;i<n;i++){
		limr[i]=next_num<lint>()-1;
	}
	return solve(n);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("warm.in","r",stdin);
	freopen("warm.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
