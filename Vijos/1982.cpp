#include <iostream>
#include <cstring>
#include <cstdio>
#define N 1010
#define M 210
#define MOD 1000000007
using namespace std;
long long f[N][M][2],g[N][M][2];
char a[N],b[M];
int main(){
	int n,m,t;
	cin>>n>>m>>t>>a+1>>b+1;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	for(int i=0;i<=n;i++){
		g[i][0][0]=1;
	}
	for(int k=1;k<=t;k++){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				f[i][j][k&1]=g[i][j][k&1]=0;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i]==b[j]){
					f[i][j][k&1]=f[i-1][j-1][k&1]+g[i-1][j-1][!(k&1)];
				}else{
					f[i][j][k&1]=0;
				}
				g[i][j][k&1]=f[i][j][k&1]+g[i-1][j][k&1];
			}
		}
	}
	cout<<g[n][m][t&1];
}
