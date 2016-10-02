#include <iostream>
#include <cstdio>
#include <cstring>
#define N 45
using namespace std;
int mat[N][N];
int main(){
	int n,x=1,y;
	scanf("%d",&n);
	y=(n+1)/2;
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n*n;i++){
		mat[x][y]=i;
		if(x==1){
			if(y==n){
				x++;
			}else{
				x=n,y++;
			}
		}else{
			if(y==n){
				x--,y=1;
			}else{
				if(mat[x-1][y+1]==0){
					x--,y++;
				}else{
					x++;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
}
