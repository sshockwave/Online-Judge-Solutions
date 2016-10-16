#include <iostream>
#include <cstdio>
#include <cstring>
#define N 55
using namespace std;
int mat[N][N],f[N<<1][N][N];
inline int max(int &a,int &b){
	return a>b?a:b;
}
inline void work(int k,int i,int j){
	f[k][i][j]=max(//<=> f[i][k-i][j][k-j]
		max(
			f[k-1][i][j],
			f[k-1][i-1][j]
		),max(
			f[k-1][i][j-1],
			f[k-1][i-1][j-1]
		)
	)+mat[i][k-i]+mat[j][k-j];
//	cout<<"f["<<i<<"]["<<k-i<<"]["<<j<<"]["<<k-j<<"]="<<f[k][i][j]<<endl;
}
int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&mat[i][j]);
		}
	}
	memset(f,0,sizeof(f));
	for(int k=3;k<=m+n;k++){
		for(int i=1;i<=m&&i<k;i++){
			for(int j=i+1;j<=m&&j<k;j++){
				work(k,i,j);
			}
		}
	}
	work(m+n,m,m);
	printf("%d",f[m+n][m][m]);
}
