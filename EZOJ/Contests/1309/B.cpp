#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
	if(b<a){a=b;}
}
const int N=55,MOD=998244353;
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
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int rev(int x){
	return fpow(x,MOD-2);
}
struct Poly{
	int a[N],n;
	Poly(int a0=0,int a1=0){
		memset(a,0,sizeof(a));
		a[0]=a0,a[1]=a1;
		n=a1?2:1;
	}
	inline void operator += (const Poly &b){
		apmax(n,b.n);
		for(int i=0;i<n;i++){
			apadd(a[i],b.a[i]);
		}
	}
	inline void operator *= (const int &b){
		for(int i=0;i<n;i++){
			apmul(a[i],b);
		}
	}
	inline friend Poly operator * (const Poly &a,const Poly &b){
		Poly c;
		c.n=a.n+b.n-1;
		for(int i=0;i<a.n;i++){
			for(int j=0;j<b.n;j++){
				apadd(c.a[i+j],mul(a.a[i],b.a[j]));
			}
		}
		return c;
	}
	inline int eval(int x){
		int ans=0,mx=1;
		for(int i=0;i<n;i++){
			apadd(ans,mul(mx,a[i]));
			apmul(mx,x);
		}
		return ans;
	}
};
bool con[N][N];
int mat[N][N],f[N],deg[N];
inline int det(int n){
	int ans=1;
	for(int i=1,j;i<n;i++){
		for(j=i;j<n&&mat[i][j]==0;j++);
		if(j==n){
			return 0;
		}
		if(i!=j){
			ans=sub(0,ans);
			for(int k=i;k<n;k++){
				swap(mat[i][k],mat[j][k]);
			}
		}
		apmul(ans,mat[i][i]);
		int r=rev(mat[i][i]);
		for(j=i;j<n;j++){
			apmul(mat[i][j],r);
		}
		for(j=i+1;j<n;j++){
			if(mat[j][i]){
				r=mat[j][i];
				for(int k=i;k<n;k++){
					apsub(mat[j][k],mul(mat[i][k],r));
				}
				assert(mat[j][i]==0);
			}
		}
	}
	return ans;
}
int main(){
	int n=ni,k=ni;
	memset(deg,0,sizeof(deg));
	for(int i=1;i<n;i++){
		int j=ni;
		con[i][j]=con[j][i]=true;
		deg[i]++,deg[j]++;
	}
	Poly poly;
	for(int x=1;x<=n;x++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i==j){
					mat[i][j]=add(deg[i],mul(x,n-1-deg[i]));
				}else{
					mat[i][j]=sub(0,con[i][j]?1:x);
				}
			}
		}
		int k=1;
		Poly cur(1);
		for(int i=1;i<=n;i++){
			if(x!=i){
				cur=cur*Poly(sub(0,i),1);
				apmul(k,sub(x,i));
			}
		}
		cur*=mul(rev(k),det(n));
		poly+=cur;
	}
	int ans=0;
	for(int i=0;i<=k;i++){
		apadd(ans,poly.a[i]);
	}
	printf("%d\n",ans);
}