#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#define V 310
#define N 2010
#define INF 1e10
using namespace std;
int c[N],d[N],dis[V][V];
double k[N],f[N][N][2];
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void apmin(double &a,double b){
	if(a>b){
		a=b;
	}
}
int main(){
	freopen("1516.in","r",stdin);
	freopen("1516.out","w",stdout);
	memset(dis,16,sizeof(dis));
	int n,m,v,e,a,b,w;
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(int i=1;i<=n;i++){
		scanf("%d",c+i);
		dis[i][i]=0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",d+i);
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",k+i);
	}
	while(e--){
		scanf("%d%d%d",&a,&b,&w);
		apmin(dis[a][b],w);
		apmin(dis[b][a],w);
	}
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				apmin(dis[i][j],dis[i][t]+dis[t][j]);
				dis[j][i]=dis[i][j];
			}
		}
	}
	for(int i=0;i<=m;i++){
		f[1][i][0]=f[1][i][1]=0;
	}
	for(int i=2,dcc,ddc,dcd,ddd;i<=n;i++){
		dcc=dis[c[i-1]][c[i]];
		ddc=dis[d[i-1]][c[i]];
		dcd=dis[c[i-1]][d[i]];
		ddd=dis[d[i-1]][d[i]];
		f[i][m][0]=f[i-1][m][0]+dcc;
		f[i][m][1]=INF;
		for(int j=0;j<m;j++){
			f[i][j][0]=min(f[i-1][j][0]+dcc,f[i-1][j][1]+k[i-1]*ddc+(1-k[i-1])*dcc);
			f[i][j][1]=min(f[i-1][j+1][0]+k[i]*dcd+(1-k[i])*dcc,f[i-1][j+1][1]+k[i]*(k[i-1]*ddd+(1-k[i-1])*dcd)+(1-k[i])*(k[i-1]*ddc+(1-k[i-1])*dcc));
		}
	}
	double ans=INF,cur;
	for(int i=0;i<m;i++){
		apmin(ans,min(f[n][i][0],f[n][i][1]));
	}
	apmin(ans,f[n][m][0]);
	printf("%.2f",(double)round(ans*100)/100.0);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
