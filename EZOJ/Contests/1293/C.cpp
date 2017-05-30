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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=2010,MOD=1000000007,S=100010;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apsub(int &a,const int &b){
	a=sub(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
inline int getrev(int x){
	return fpow(x,MOD-2);
}
int f[N],g[N],ways[N][N],ind[N];
struct Point{
	int x,y;
	inline friend bool operator <= (const Point &a,const Point &b){
		return a.x<=b.x&&a.y<=b.y;
	}
}pt[N];
int rev[S],fac[S],refac[S];
inline int c(int n,int k){
	return mul(fac[n],mul(refac[k],refac[n-k]));
}
int main(){
	rev[1]=fac[0]=fac[1]=refac[0]=refac[1]=1;
	for(int i=2;i<S;i++){
		rev[i]=mul(MOD-MOD/i,rev[MOD%i]);
		fac[i]=mul(fac[i-1],i);
		refac[i]=mul(refac[i-1],rev[i]);
	}
const int N=2010,MOD=1000000007,S=100010;
	int row=ni,col=ni,n=ni+1,s=ni;
	pt[0].x=pt[0].y=1;
	pt[n].x=row,pt[n].y=col;
	for(int i=1;i<n;i++){
		pt[i]=(Point){ni,ni};
	}
	memset(ind,0,sizeof(ind));
	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++){
			if(pt[j]<=pt[i]){
				ind[i]++;
			}
		}
		ind[i]--;
	}
	for(int i=1;i<n;i++){
		int j=i;
		for(;ind[j];j++);
		swap(pt[i],pt[j]);
		ind[j]=ind[i];
		for(j=1;j<n;j++){
			if(pt[i]<=pt[j]){
				ind[j]--;
			}
		}
	}
	memset(ways,0,sizeof(ways));
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++){
			if(pt[j]<=pt[i]){
				ways[j][i]=c(pt[i].x+pt[i].y-pt[j].x-pt[j].y,pt[i].x-pt[j].x);
			}
		}
	}
	int rest=ways[0][n],ans=0;
	memset(g,0,sizeof(g));
	for(;s>1;s=(s+1)/2){
		for(int i=1;i<=n;i++){
			f[i]=sub(ways[0][i],g[i]);
			for(int j=1;j<i;j++){
				if(pt[j]<=pt[i]){
					apsub(f[i],mul(f[j],ways[j][i]));
				}
			}
			g[i]+=f[i];
		}
		apadd(ans,mul(s,f[n]));
		apsub(rest,f[n]);
	}
	printf("%d\n",mul(ans+rest,getrev(ways[0][n])));
}