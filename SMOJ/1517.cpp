#include <iostream>
#include <cstdio>
#include <cstring>
#define N 2010
using namespace std;
int c[N][N],ans[N][N];//c[down][up]
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline int getans(int m,int n){
	apmin(n,m);
	return ans[m][n];
}
int main(){
//	freopen("problem1.in","r",stdin);
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	int t,MOD,n,m;
	scanf("%d%d",&t,&MOD);
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
			ans[i][j]=getans(i-1,j)-getans(i-1,j-1)+getans(i,j-1);
			if(c[i][j]==0){
				ans[i][j]++;
			}
		}
	}
	while(t--){
		scanf("%d%d",&n,&m);
		printf("%d\n",getans(n,m));
	}
	fclose(stdin);
	fclose(stdout);
}
