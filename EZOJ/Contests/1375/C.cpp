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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=9,O=998244353;
lint mx[N],n,ts;
int f[2][1<<N];
inline void clr(int f[]){
	memset(f,0,ts<<2);
}
inline int solve(){
	int *f=::f[0],*nf=::f[1];
	clr(f);
	f[0]=1;
	sort(mx,mx+n);
	int sh=0;
	for(;(1ll<<sh)<=mx[n-1];sh++);
	for(int i=sh;i>=0;i--,swap(f,nf)){
		clr(nf);
		int mask=0;
		for(int j=0;j<n;j++){
			mask|=((mx[j]>>i)&1)<<j;
		}
		for(int s=0;s<ts;s++){
			int F=f[s];
			if(F==0)continue;
			(nf[s|mask]+=F)%=O;
			for(int j=0;j<n;j++){
				if((s>>j)&1){
					(nf[s|mask]+=F)%=O;
				}else if((mask>>j)&1){
					(nf[s|(mask^(1<<j))]+=F)%=O;
				}
			}
		}
	}
	lint ans=0;
	for(int s=0;s<ts;s++){
		ans+=f[s];
	}
	return ans%O;
}
lint a[N][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("village.in","r",stdin);
	freopen("village.out","w",stdout);
#endif
	n=ni,ts=1<<n;
	for(int i=0;i<n;i++){
		a[i][1]=next_num<lint>()-1;
		a[i][0]=next_num<lint>();
	}
	lint ans=0;
	for(int s=0;s<ts;s++){
		int cnt=0;
		for(int i=0;i<n;i++){
			cnt+=(s>>i)&1;
			mx[i]=a[i][(s>>i)&1]-1;
			if(mx[i]<0){
				cnt=-1;
				break;
			}
		}
		if(cnt==-1)continue;
		if(cnt&1){
			ans-=solve();
		}else{
			ans+=solve();
		}
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
