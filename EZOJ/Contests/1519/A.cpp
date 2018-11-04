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
const int N=42,O=2333,logA=31;
int n;
struct Mat{
	int a[N][N];
	inline void clr(){
		for(int i=1;i<=n;i++){
			mset(a[i]+1,0,n);
		}
	}
	inline void getmul(const Mat &x,const Mat &y){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				lint ans=0;
				for(int k=1;k<=n;k++){
					ans+=x.a[i][k]*y.a[k][j];
				}
				a[i][j]=ans%O;
			}
		}
	}
	inline void mulvec(int b[]){
		static int c[N];
		for(int i=1;i<=n;i++){
			lint ans=0;
			for(int j=1;j<=n;j++){
				ans+=a[i][j]*b[j];
			}
			c[i]=ans%O;
		}
		mcpy(b+1,c+1,n);
	}
}pw[logA];
int vec[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("l.in","r",stdin);
	freopen("l.out","w",stdout);
#endif
	n=ni;
	pw[0].clr();
	for(int tot=ni;tot--;){
		const int u=ni,v=ni;
		pw[0].a[u][v]=1;
		pw[0].a[v][u]=1;
	}
	for(int i=1;i<logA;i++){
		pw[i].getmul(pw[i-1],pw[0]);
	}
	for(int tot=ni;tot--;){
		mset(vec+1,0,n);
		const int s=ni;
		vec[ni]=1;
		const int l=ni,r=ni;
		for(int j=0;j<logA;j++){
			if((l>>j)&1){
				pw[j].mulvec(vec);
			}
		}
		int ans=0;
		for(int i=l;i<=r;i++,pw[0].mulvec(vec)){
			ans+=vec[s];
		}
		printf("%d\n",ans%O);
	}
	return 0;
}
