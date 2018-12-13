#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=210,B=52,T=3010,O=1e9+7;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
int a,b;
lint lst[T];
int ls=0;
int pw[N],ipw[N];
int g[N];
inline lint recalc(lint s,int n){
	static int ch[B],kmp[B];
	for(int i=1,j=0,c=0;i<=n;i++){
		if((s>>i)&1){
			const int k=i-j;
			for(;j<k;ch[++j]=++c);
			for(;j<i;++j,ch[j]=ch[j-k]);
		}
	}
	kmp[0]=-1;
	for(int i=0,j=-1;i<n;){
		if(j==-1||ch[i+1]==ch[j+1]){
			kmp[++i]=++j;
		}else{
			j=kmp[j];
		}
	}
	lint ts=1;
	for(int i=n;i;i=kmp[i]){
		ts|=1ll<<i;
	}
	return ts;
}
void dfs(lint s,int n,int kb){
	if(n==b)return lst[++ls]=s,void();
	for(int i=n+kb+1;i<=b;i++){
		const int len=i-n;
		lint ts=s;
		for(int j=i;j>=len;j-=len){
			ts|=1ll<<j;
		}
		if(recalc(ts,i)!=ts)continue;
		dfs(ts,i,n);
	}
}
inline bool subset(lint a,lint b){
	return (a&b)==a;
}
int f[T];
inline int Main(){
	a=ni,b=ni;
	pw[0]=ipw[0]=1;
	for(int i=1,w=ni,iw=inv_pow(w);i<=a;i++){
		pw[i]=(lint)pw[i-1]*w%O;
		ipw[i]=(lint)ipw[i-1]*iw%O;
	}
	dfs(1,0,0);
	sort(lst+1,lst+ls+1);
	for(int t=ls;t>=1;t--){
		const lint s=lst[t];
		int cnt=0;
		for(int i=1,j=0;i<=b;i++){
			if((s>>i)&1){
				cnt+=max(i-j-j,0);
				j=i;
			}
		}
		lint cur=0;
		for(int j=t+1;j<=ls;j++){
			assert(s!=lst[j]);
			if(t!=j&&subset(s,lst[j])){
				cur+=f[j];
			}
		}
		f[t]=(pw[cnt]+O-cur%O)%O;
	}
	int ans=0;
	for(int t=1;t<=ls;t++){
		int sum=0;
		const lint s=lst[t];
		for(int i=b;i<=a;i++){
			sum=(sum+(lint)g[i-b]*ipw[i-b])%O;
			lint cur=pw[i-b];
			for(int j=1;j<b;j++){
				if((s>>j)&1){
					cur=cur-g[i-b+j];
				}
			}
			g[i]=(cur-(lint)sum*pw[i-b])%O;
		}
		lint cur=0;
		for(int i=b;i<=a;i++){
			cur=(cur+(lint)(g[i]+O)*pw[a-i])%O;
		}
		ans=(ans+(lint)cur*f[t])%O;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
