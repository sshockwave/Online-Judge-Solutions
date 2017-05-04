#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=1005,T=10000;
int n;
struct Matrix{
	unsigned int mat[N][N];
	Matrix(){
		memset(mat,0,sizeof(mat));
	}
}trans,ret,mulans;
inline void mul (const Matrix &a,const Matrix &b){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			mulans.mat[i][j]=0;
			for(int k=0;k<n;k++){
				mulans.mat[i][j]^=a.mat[i][k]&b.mat[k][j];
			}
		}
	}
}
unsigned int a[N],b[N],f[T];
inline unsigned int brute(int t){
	for(int i=1;i<=n;i++){
		f[i]=a[i-1];
	}
	for(lint i=n+1;i<=t;i++){
		for(int j=1;j<=n;j++){
			f[i]^=f[i-j]&b[j-1];
		}
	}
	return f[t];
}
inline void fpow(lint exp){
	memset(&ret,0,sizeof(ret));
	for(int i=0;i<n;i++){
		ret.mat[i][i]=0xffffffffu;
	}
	for(;exp;exp>>=1,mul(trans,trans),trans=mulans){
		if(exp&1){
			mul(ret,trans);
			ret=mulans;
		}
	}
}
int main(){
	n=ni();
	for(int i=0;i<n;i++){
		scanf("%u",a+i);
	}
	for(int i=0;i<n;i++){
		scanf("%u",b+i);
		trans.mat[0][i]=b[i];
	}
	lint t;
	scanf("%lld",&t);
	if(t<=n){
		printf("%u\n",a[t-1]);
		return 0;
	}
	if(t<=5000){
		printf("%u\n",brute(t));
		return 0;
	}
	for(int i=0,top=n-1;i<top;i++){
		trans.mat[i+1][i]=0xffffffffu;
	}
	fpow(t-n);
	unsigned int res=0;
	for(int i=0;i<n;i++){
		res^=ret.mat[0][i]&a[n-i-1];
	}
	printf("%d\n",res);
}
