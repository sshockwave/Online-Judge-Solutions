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
const int MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
struct Mat{
	const static int N=10;
	int a[N][N];
	inline void in(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				a[i][j]=ni;
			}
		}
	}
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				lint sum=0;
				for(int k=0;k<N;k++){
					sum+=mul(a.a[i][k],b.a[k][j]);
				}
				c.a[i][j]=sum%MOD;
			}
		}
		return c;
	}
	inline void print(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				printf("%d ",a[i][j]);
			}
			putchar('\n');
		}
	}
}T[111],ans;
int a[1000100];
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix0.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	for(int i=1;i<=10;i++){
		T[i].in();
	}
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=100;i++,n++){
		int x=ni+1;
		for(int j=n;j>=x;j--){
			a[j+1]=a[j];
		}
		a[x]=i+10;
		T[i+10].in();
	}
	ans=T[a[1]];
	for(int i=2;i<=n;i++){
		ans=ans*T[a[i]];
	}
	ans.print();
	return 0;
}
