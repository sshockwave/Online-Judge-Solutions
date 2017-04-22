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
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=110;
int n,MOD;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
struct Matrix{
	int mat[N][N];
	Matrix(){
		memset(mat,0,sizeof(mat));
	}
	inline friend Matrix operator * (const Matrix &a,const Matrix &b){
		Matrix c;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					apadd(c.mat[i][j],mul(a.mat[i][k],b.mat[k][j]));
				}
			}
		}
		return c;
	}
}trans,res;
inline void fpow(int exp){
	for(int i=1;i<=n;i++){
		res.mat[i][i]=1;
	}
	for(;exp;exp>>=1,trans=trans*trans){
		if(exp&1){
			res=trans*res;
		}
	}
}
int a[N],b[N];
int main(){
	n=ni,MOD=ni;
	int t=ni;
	for(int i=1;i<n;i++){
		a[i]=ni-1;
		static int minusone=MOD-1;
		trans.mat[i][i]=minusone;
		trans.mat[i][i+1]=2;
	}
	a[n]=ni-1;
	trans.mat[n][n]=MOD-1;
	trans.mat[n][1]=2;
	fpow(t);
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			apadd(b[i],mul(res.mat[i][j],a[j]));
		}
		printf("%d ",b[i]+1);
	}
}
