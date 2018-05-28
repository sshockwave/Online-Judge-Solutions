#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=12;
int a[N],n;
int mat[N][N];
void dfs(int l,int r,int sig){
	if(cabs(a[l])<cabs(a[r])){
		swap(l,r);
	}
	if(a[l]==0||a[r]==0){
		if(l!=1){
			int tmp=1;
			int &x=r==1?r:tmp;
			swap(x,l),swap(a[x],a[l]);
			dfs(l,r,-sig);
			for(int i=1;i<=n;i++){
				swap(mat[i][l],mat[i][x]);
			}
			return;
		}
		memset(mat,0,sizeof(mat));
		memcpy(mat[1]+1,a+1,n*sizeof(mat[1][0]));
		sig*=a[1];
		for(int i=2;i<n;i++){
			mat[i][i]=1;
		}
		mat[n][n]=sig;
		return;
	}
	const int q=a[l]/a[r];
	a[l]-=q*a[r];
	dfs(l,r,sig);
	for(int i=1;i<=n;i++){
		mat[i][l]+=mat[i][r]*q;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("final.in","r",stdin);
	freopen("final.out","w",stdout);
#endif
	n=ni;
	generate_n(a+1,n,next_num<int>);
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(gcd(a[i],a[j])==1){
				l=i,r=j;
				break;
			}
		}
		if(l)break;
	}
	dfs(l,r,1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",mat[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
