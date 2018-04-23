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
const int N=20010,DEP=41;
lint f[N][DEP][DEP];
int a[N],b[N],c[N];
int xcnt[N],ycnt[N];
int lson[N],rson[N];
inline lint ev(int p,int x,int y){
	if(p>0)return f[p][x][y];
	return p=-p,(lint)c[p]*(a[p]+x)*(b[p]+y);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
#endif
	int n=ni;
	xcnt[1]=ycnt[1]=0;
	for(int i=1;i<n;i++){
		lson[i]=ni,rson[i]=ni;
		if(lson[i]>0){
			xcnt[lson[i]]=xcnt[i]+1,ycnt[lson[i]]=ycnt[i];
		}
		if(rson[i]>0){
			xcnt[rson[i]]=xcnt[i],ycnt[rson[i]]=ycnt[i]+1;
		}
	}
	for(int i=1;i<=n;i++){
		a[i]=ni,b[i]=ni,c[i]=ni;
	}
	for(int i=n-1;i>=1;i--){
		for(int a=0;a<=xcnt[i];a++){
			for(int b=0;b<=ycnt[i];b++){
				lint va=ev(lson[i],a,b)+ev(rson[i],a,b+1);
				lint vb=ev(lson[i],a+1,b)+ev(rson[i],a,b);
				f[i][a][b]=min(va,vb);
			}
		}
	}
	printf("%lld\n",f[1][0][0]);
	return 0;
}
