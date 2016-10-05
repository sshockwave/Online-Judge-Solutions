#include <iostream>
#include <cstdio>
#include <cstring>
#define N 35
#define G 20
using namespace std;
double f[G][G][G][N];//win rate
int main(){
//	freopen("1425.in","r",stdin);
//	freopen("1425.out","w",stdout);
	int tot,n,g,r,b,ans;
	double rate;
	for(scanf("%d",&tot);tot--;){
		scanf("%d%d%d%d",&n,&g,&r,&b);
		memset(f,0,sizeof(f));
		for(int i=n-b;i<=n;i++){
			for(int j=0;j<=g;j++){
				for(int k=0;k<=r;k++){
					if(i==n-b&&j==0&&k==0){
						f[i][0][0][0]=1;
						for(int l=1;l<n;l++){
							f[0][0][0][l]=0;
						}
					}else{
						if(i-n+b>0){//black
							rate=(double)(i-n+b)/(double)(i-n+b+j+k);
							for(int l=1;l<i;l++){
								f[i][j][k][l]+=f[i-1][j][k][l-1]*rate;
							}
						}
						if(j>0){//green
							rate=(double)j/(double)(i-n+b+j+k);
							f[i][j][k][0]+=f[i][j-1][k][i-1]*rate;
							for(int l=1;l<i;l++){
								f[i][j][k][l]+=f[i][j-1][k][l-1]*rate;
							}
						}
						if(k>0){//red
							rate=(double)k/(double)(i-n+b+j+k);
							for(int l=0;l<i;l++){
								f[i][j][k][l]+=f[i][j][k-1][i-l-1]*rate;
							}
						}
					}
					for(int l=0;l<i;l++){
						cout<<"f["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]="<<f[i][j][k][l]<<endl;
					}
				}
			}
		}
		ans=0;
		for(int i=1;i<n;i++){
			if(f[n][g][r][i]>f[n][g][r][ans]){
				ans=i;
			}
		}
		printf("%d\n",ans);
	}
}
