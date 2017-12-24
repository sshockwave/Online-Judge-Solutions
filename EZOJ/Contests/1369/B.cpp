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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=23,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int n;
int pool[2][N][1<<N];
template<class T>inline void dp(T F,T NF){
	for(int s=0,ts=1<<n;s<ts;s++){
		int x=n;
		for(int i=1;i<=n;i++){
			x-=(s>>(i-1))&1;
		}
		for(int i=1;i<=n;i++){
			if((s>>(i-1))&1)continue;
			lint cur=F[i][s];
			if(cur==0)continue;
			lint cur2=(cur<<1)%O;
			(NF[i][s]+=cur*((x-1)*(x-1)%O+(n-x)*(n-x)%O)%O)%=O;//ll rr
			for(int j=1;j<=n;j++){//lr
				if(i!=j&&((s>>(j-1))&1)==0){
					for(int k=1;k<=n;k++){
						if(s>>(k-1)&1){
							(NF[i][s^(1<<(j-1))^(1<<(k-1))]+=cur2)%=O;
						}
					}
				}
			}
			for(int j=1;j<=n;j++){//lx
				if(i==j){
					(NF[i][s]+=cur)%=O;
				}else{
					bool d=(s>>(j-1))&1;
					(NF[j][s^(d<<(i-1))^(d<<(j-1))]+=cur2)%=O;
				}
			}
		}
	}
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	memset(pool,0,sizeof(pool));
	bool r=0;
	for(int i=1;i<=n;i++){
		int mask=0;
		for(int j=1;j<=n;j++){
			mask|=(a[j]>a[i])<<(j-1);
		}
		pool[r][i][mask]=1;
	}
	for(int i=1;i<=tot;i++,r=!r){
		memset(pool[!r],0,sizeof(pool[!r]));
		dp(pool[r],pool[!r]);
		cout<<"i="<<i<<"\tcomplete"<<endl;
	}
	lint ans=0;
	for(int s=0,ts=1<<n;s<ts;s++){
		for(int i=1;i<=n;i++){
			if((s>>(i-1))&1)break;
			ans+=pool[r][i][s];
		}
	}
	printf("%lld\n",ans%O*fpow(inv(n*n),tot)%O);
	return 0;
}
