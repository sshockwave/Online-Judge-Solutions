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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=3010,MOD=13999;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apsub(int &a,int b){
	a=sub(a,b);
}
inline void apmul(int &a,int b){
	a=mul(a,b);
}
int mat[N][N];
int inv[MOD];
inline void putmat(int n){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}
inline int gauss(int n){
	int ans=1;
	for(int i=1;i<=n;i++){
		int j=i;
		for(;j<=n&&mat[j][i]==0;j++);
		if(j>n){
			return 0;
		}
		if(j!=i){
			ans=MOD-ans;
			for(int k=i;k<=n;k++){
				swap(mat[i][k],mat[j][k]);
			}
		}
		apmul(ans,mat[i][i]);
		int r=inv[mat[i][i]];
		for(j=i;j<=n;j++){
			apmul(mat[i][j],r);
		}
		assert(mat[i][i]==1);
		for(int j=i+1;j<=n;j++){
			if(mat[j][i]){
				int v=mat[j][i];
				for(int k=i;k<=n;k++){
					apsub(mat[j][k],mul(v,mat[i][k]));
				}
			}
		}
	}
	return ans;
}
int main(){
	freopen("thefall1.in","r",stdin);
	inv[1]=1;
	for(int i=2;i<MOD;i++){
		inv[i]=(MOD-mul(inv[MOD%i],MOD/i))%MOD;
		assert(mul(inv[i],i)==1);
	}
	for(int tot=ni;tot--;){
		int n=ni;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				mat[i][j]=ni;
			}
		}
		cout<<gauss(n)<<endl;
	}
}
