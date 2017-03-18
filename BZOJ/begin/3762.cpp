#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
struct matrix{
	int num[3][3];
	inline int* operator [] (int x){
		return num[x];
	}
}trans,id,ans;
int MOD,transi[3][3]={
	{1,1,0},
	{2,1,1},
	{0,1,0}
};
matrix operator * (matrix a,matrix b){
	matrix c;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			c[i][j]=0;
			for(int k=0;k<3;k++){
				c[i][j]=((long long)a[i][k]*b[k][j]%MOD+c[i][j])%MOD;
			}
		}
	}
	return c;
}
matrix tpow(int n){
	if(n==0){
		return id;
	}
	matrix ret=tpow(n>>1);
	ret=ret*ret;
	if(n&1){
		ret=ret*trans;
	}
	return ret;
}
int main(){
	int f0=ni(),f1=ni(),n;
	MOD=ni();
	n=ni();
	if(n==0){
		printf("%d",f0%MOD);
		return 0;
	}else if(n==1){
		printf("%d",f1%MOD);
		return 0;
	}
	long long t1=0;
	for(long long top=(long long)f0*f1+3;t1*t1<top;t1++);
	memset(&id,0,sizeof(id));
	for(int i=0;i<3;i++){
		id[i][i]=1;
		for(int j=0;j<3;j++){
			trans[i][j]=transi[i][j];
		}
	}
	ans=tpow(n-1);
	printf("%d",(t1*ans[1][0]%MOD+(long long)f1*ans[1][1]+(long long)f0*ans[1][2])%MOD);
}
