#include <iostream>
#include <cstdio>
#include <cstring>
#define N 33
using namespace std;
int choose[N][N];
long long f[N][N];
void dfs(int l,int r){
	if(l>r){
		return;
	}
	printf("%d ",choose[l][r]);
	dfs(l,choose[l][r]-1);
	dfs(choose[l][r]+1,r);
}
int main(){
	int n;
	long long cur;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i][i]);
		choose[i][i]=i;
	}
	for(int i=1;i<n;i++){
		for(int j=1;j+i<=n;j++){
			f[j][j+i]=0;
			choose[j][j+i]=j;
			for(int k=j;k<=j+i;k++){
				cur=1;
				if(j<=k-1){
					cur*=f[j][k-1];
				}
				if(k+1<=j+i){
					cur*=f[k+1][j+i];
				}
				cur+=f[k][k];
				if(cur>f[j][j+i]){
					f[j][j+i]=cur;
					choose[j][j+i]=k;
				}
			}
		}
	}
	printf("%d\n",f[1][n]);
	dfs(1,n);
}
