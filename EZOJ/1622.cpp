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
const int N=85,MOD=1000000007;
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
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
inline int inv(const int &x){
	return fpow(x,MOD-2);
}
int mat[N][N];
inline int det(int n){
	int ans=1;
	for(int i=1,j;i<=n;i++){
		for(j=i;j<=n&&mat[j][i]==0;j++);
		if(j>n){
			return 0;
		}
		if(i!=j){
			ans=MOD-ans;
			for(int k=i;k<=n;k++){
				swap(mat[i][k],mat[j][k]);
			}
		}
		int r=inv(mat[i][i]);
		apmul(ans,mat[i][i]);
		for(int k=i;k<=n;k++){
			apmul(mat[i][k],r);
		}
		for(j++;j<=n;j++){
			if(r=mat[j][i]){
				for(int k=i;k<=n;k++){
					apsub(mat[j][k],mul(r,mat[i][k]));
				}
			}
			assert(mat[j][i]==0);
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	memset(mat,0,sizeof(mat));
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		apadd(mat[u][u],1);
		apadd(mat[v][v],1);
		apsub(mat[u][v],1);
		apsub(mat[v][u],1);
	}
	printf("%d\n",det(n-1));
}
