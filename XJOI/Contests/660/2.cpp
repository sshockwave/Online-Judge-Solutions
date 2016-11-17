#include <iostream>
#include <cstdio>
#include <cstring>
#define MOD 1000000007
using namespace std;
struct matrix{
	long long a11,a12,a21,a22;
	matrix operator * (matrix &b){
		return (matrix){
			(a11*b.a11%MOD+a12*b.a21%MOD)%MOD,(a11*b.a12%MOD+a12*b.a22%MOD)%MOD,
			(a21*b.a11%MOD+a22*b.a21%MOD)%MOD,(a21*b.a12%MOD+a22*b.a22%MOD)%MOD
		};
	}
}trans;
matrix fpow(long long n){
	if(n==0){
		return (matrix){1,0,0,1};
	}
	matrix tmp=fpow(n>>1);
	tmp=tmp*tmp;
	if(n&1){
		tmp=tmp*trans;
	}
	return tmp;
}
int main(){
	long long n,m;
	cin>>n>>m;
	if(n==1){
		cout<<m;
		return 0;
	}
	trans=(matrix){0,m-1,1,m-2};
	cout<<fpow(n-1).a12*m%MOD;
}
