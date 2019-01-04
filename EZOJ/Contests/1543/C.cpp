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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=2010,B=500010;
namespace dp1{
	struct Item{
		int a,b,c;
		inline friend bool operator < (const Item &a,const Item &b){
			return a.c<b.c;
		}
	}item[N];
	int n=0;
	inline void init(){}
	inline void psh(int a,int b,int c){
		item[++n]=(Item){a,b,c};
	}
	lint f[N*4][2][2];
	int sum=0;
	int a,b,c,a2;
	inline void main(){
		memset(f,-1,sizeof(f));
		f[0][0][1]=0;
		sort(item+1,item+n+1);
		for(int i=n;i>=1;i--){
			a=item[i].a,b=item[i].b,c=item[i].c;
			a2=a<<1;
			for(int j=sum;j>=0;j--){
				lint tmpf[2][2];
				memcpy(tmpf,f[j],4*sizeof(tmpf[0][0]));
				memset(f[j],-1,4*sizeof(f[j][0][0]));
				for(int p1=0;p1<2;p1++){
					for(int p2=0;p2<2;p2++){
						const int F=tmpf[p1][p2];
						if(F<0)continue;
						for(int b1=0;b1<=b;b1++){
							const int b2=b-b1;
							assert(b1<=4*a-2&&b2<=4*a-2);
							int cnt=0;
							cnt+=b1>=a2||(b1==a2-1&&!p1);
							cnt+=b2>=a2||(b2==a2-1&&!p2);
							apmax(f[j+b1][p1^(b1==a2-1)][p2^(b2==a2-1)],F+cnt*c);
						}
					}
				}
			}
			sum+=item[i].b;
		}
	}
}
namespace dp2{
	int cnt[N],mxa=0;
	inline void init(){
		memset(cnt,0,sizeof(cnt));
	}
	inline void psh(int a,int v){
		cnt[a]+=v;
		apmax(mxa,a);
	}
	bool f[B];
	int sum=0;
	inline void main(){
		memset(f,0,sizeof(f));
		f[0]=true;
		for(int i=1;i<=mxa;i++){
			if(cnt[i]==0)continue;
			int allv=cnt[i]*i;
			sum+=allv;
			for(int j=0;j<i;j++){
				int p=-allv-1;
				for(int k=j;k<=sum;k+=i){
					if(f[k]){
						p=k;
					}
					f[k]=p>=k-allv;
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
#endif
	const int n=ni;
	dp1::init(),dp2::init();
	lint tmpsum=0;
	int sumb=0;
	for(int i=1;i<=n;i++){
		const int a=ni,b=ni,c=ni;
		sumb+=b;
		int buk=max((b-(2*a-1))/(2*a),0);
		tmpsum+=(lint)buk*c;
		dp1::psh(a,b-buk*(2*a),c);
		dp2::psh(a,buk);
	}
	sumb>>=1;
	dp1::main();
	dp2::main();
	lint ans=0;
	for(int i=0;i<=dp1::sum&&i<=sumb;i++){
		int tb=sumb-i;
		if(tb&1)continue;
		tb>>=1;
		if(dp2::f[tb]){
			assert(tb<=dp2::sum);
			apmax(ans,dp1::f[i][0][0]);
			apmax(ans,dp1::f[i][0][1]);
			apmax(ans,dp1::f[i][1][0]);
			apmax(ans,dp1::f[i][1][1]);
		}
	}
	ans+=tmpsum;
	printf("%lld\n",ans);
	return 0;
}
