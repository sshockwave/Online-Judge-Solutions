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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,S=8,MOD=998244353;
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
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
int sh,m,k,n;
struct Matrix{
	int a[S][S];
	inline void id(){
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++){
			a[i][i]=1;
		}
	}
	inline int ans(){
		lint ans=0;
		for(int i=0;i<n;i++){
			ans+=a[i][0];
		}
		return ans%MOD;
	}
	inline friend Matrix operator * (const int &a,const Matrix &b){
		Matrix c;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				c.a[i][j]=mul(a,b.a[i][j]);
			}
		}
		return c;
	}
	inline friend Matrix operator * (const Matrix &a,const Matrix &b){
		Matrix c;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				lint tmp=0;
				for(int k=0;k<n;k++){
					tmp+=a.a[i][k]*b.a[k][j];
				}
				c.a[i][j]=tmp%MOD;
			}
		}
		return c;
	}
	inline friend Matrix operator + (const Matrix &a,const Matrix &b){
		Matrix c;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				c.a[i][j]=add(a.a[i][j],b.a[i][j]);
			}
		}
		return c;
	}
	inline void operator ^= (int n){
		static Matrix x;
		if(n==0){
			x=*this;
			id();
			return;
		}
		*this^=n>>1;
		*this=(*this)*(*this);
		if(n&1){
			*this=(*this)*x;
		}
	}
	inline friend ostream & operator << (ostream & out,const Matrix &a){
		for(int i=0;i<n;i++){
			out<<endl<<"[";
			for(int j=0;j<n;j++){
				out<<a.a[i][j]<<" ";
			}
			out<<"\b]";
		}
		return out;
	}
}a[3];
bool vis[3],mat[2][3],con[3];
void dfs(int x){
	if(vis[x]){
		return;
	}
	vis[x]=true,con[x]=false;
	if(x<sh-1&&mat[1][x+1]){
		dfs(x+1);
		con[x]|=con[x+1];
	}
	if(x&&mat[1][x-1]){
		dfs(x-1);
		con[x]|=con[x-1];
	}
	con[x]|=mat[0][x];
}
inline void geta(){
	memset(a,0,sizeof(a));
	for(int s0=0;s0<n;s0++){
		for(int i=0;i<sh;i++){
			mat[0][i]=(s0>>i)&1;
		}
		for(int s1=0;s1<n;s1++){
			for(int i=0;i<sh;i++){
				mat[1][i]=(s1>>i)&1;
				vis[i]=0;
			}
			int cnt=0;
			for(int i=0;i<sh;i++){
				if(!vis[i]&&mat[1][i]){
					dfs(i),cnt+=!con[i];
				}
			}
			a[cnt].a[s1][s0]=1;
		}
	}
}
Matrix f[N];
inline int work(){
	memset(f,0,sizeof(f));
	f[0].id();
	for(int i=1;i<=m;i++){
		for(int j=k;j>=0;j--){
			if(sh==3&&j+2<=k){
				f[j+2]=f[j+2]+f[j]*a[2];
			}
			if(j+1<=k){
				f[j+1]=f[j+1]+f[j]*a[1];
			}
			f[j]=f[j]*a[0];
		}
	}
	return f[k].ans();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
#endif
	sh=ni,m=ni,k=ni,n=1<<sh;
	geta();
	printf("%d\n",work());
}
