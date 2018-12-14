#include<bits/stdc++.h>
#include"unnamable.h"
using namespace std;
typedef double db;
typedef complex<db> cp;
const int n=16;
cp a[2][2],b[2][2];
inline cp w(int k){
	const db ang=2*M_PI*k/(1<<n);
	return cp(cos(ang),sin(ang));
}
cp SOL(int t){
	INI(n);
	{
		db v=1/sqrt(2);
		a[0][0]=v,a[0][1]=v;
		a[1][0]=v,a[1][1]=-v;
	}
	{
		b[0][0]=1,b[0][1]=0;
		b[1][0]=0,b[1][1]=1;
	}
	for(int i=0;i<n;i++){
		CR(i,i,a);
		CU(i,1<<(n-1-i));
		for(int j=0;j<i;j++){
			b[1][1]=w(-(1<<(n-1-(i-j))));
			CR(j,i,b);
		}
		CR(i,i,a);
	}
	return w(QR());
}
