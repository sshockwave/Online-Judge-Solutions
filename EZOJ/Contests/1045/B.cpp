#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=1000110,MOD=1000000007;
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
}T[111][20],ans,id;
int a[N],b[N],x[111];
inline void pushmat(int n){
	static int cnt[11]={0};
	if(1<=n&&n<=10){
		cnt[n]++;
	}else{
		for(int i=1;i<=10;i++){
			for(int j=0;j<20;j++){
				if((cnt[i]>>j)&1){
					ans=ans*T[i][j];
				}
			}
			cnt[i]=0;
		}
		ans=ans*T[n][0];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix0.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	memset(&id,0,sizeof(id));
	for(int i=0;i<10;i++){
		id.a[i][i]=1;
	}
	for(int i=1;i<=10;i++){
		T[i][0].in();
		for(int j=0;j<19;j++){
			T[i][j+1]=T[i][j]*T[i][j];
		}
	}
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	memset(b,0,sizeof(b));
	for(int i=11;i<=110;i++){
		x[i]=ni;
		T[i][0].in();
	}
	for(int i=110;i>=11;i--){
		x[i]++;
		for(int j=i+1;j<=110&&x[j]<=x[i];x[i]++,j++);
		b[x[i]]=i;
		for(int j=i;j<110&&x[j]>x[j+1];swap(x[j],x[j+1]),j++);
	}
	for(int i=1,j=1;i<=n;i++){
		for(;b[j];j++);
		b[j]=a[i];
	}
	ans=id;
	for(int i=1,ti=n+100;i<=ti;i++){
		pushmat(b[i]);
	}
	T[0][0]=id,pushmat(0);
	ans.print();
	return 0;
}
