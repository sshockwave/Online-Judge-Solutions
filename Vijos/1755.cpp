#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int mat[9][9];
bool row[9][10],column[9][10],block[3][3][10];
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline int score(int x,int y){
	return 6+min(min(x,8-x),min(y,8-y));
}
int dfs(int x,int y){
	for(;y<9&&mat[x][y];x++,y+=x/9,x%=9);
	if(y==9){
		int ans=0;
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				ans+=mat[i][j]*score(i,j);
			}
		}
		return ans;
	}
	int ans=-1;
	bool *r=row[x],*c=column[y],*b=block[x/3][y/3];
	mat[x][y]=1;
	for(int &i=mat[x][y];i<=9;i++){
		if(!r[i]&&!c[i]&&!b[i]){
			r[i]=c[i]=b[i]=true;
			apmax(ans,dfs(x,y));
			r[i]=c[i]=b[i]=false;
		}
	}
	mat[x][y]=0;
	return ans;
}
int main(){
	memset(row,0,sizeof(row));
	memset(column,0,sizeof(column));
	memset(block,0,sizeof(block));
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			scanf("%d",&mat[i][j]);
			row[i][mat[i][j]]=true;
			column[j][mat[i][j]]=true;
			block[i/3][j/3][mat[i][j]]=true;
		}
	}
	printf("%d",dfs(0,0));
}
