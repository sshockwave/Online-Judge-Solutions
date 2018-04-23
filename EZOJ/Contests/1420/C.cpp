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
const int N=250010;
lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace gen{
	lint A,B,Q,X;
	inline void init(){
		A=ni,B=ni,Q=ni,X=ni;
	}
	inline int nxt(){
		return X=(A*X+B)%Q;
	}
}
int *ver[N],*hor[N];
lint cst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ciiis.in","r",stdin);
	freopen("ciiis.out","w",stdout);
#endif
	int n=ni,m=ni;
	gen::init();
	for(int j=1;j<=m;j++){
		ver[j]=new int[n];
	}
	for(int j=1;j<m;j++){
		hor[j]=new int[n];
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			ver[j][i]=gen::nxt();
		}
	}
	for(int i=2;i<n;i++){
		for(int j=1;j<m;j++){
			hor[j][i]=gen::nxt();
		}
	}
	mset(cst+1,0,n-1);
	for(int j=1;j<m;j++){
		for(int i=1;i<n;i++){
			cst[i]+=ver[j][i];
			if(i>1){
				apmin(cst[i],cst[i-1]+hor[j][i]);
			}
		}
		for(int i=n-1;i>1;i--){
			apmin(cst[i-1],cst[i]+hor[j][i]);
		}
	}
	lint ans=LINF;
	for(int i=1;i<n;i++){
		apmin(ans,cst[i]+=ver[m][i]);
	}
	printf("%lld\n",ans);
	return 0;
}
