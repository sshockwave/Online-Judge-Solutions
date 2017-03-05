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
//	freopen("1516.in","r",stdin);
//	freopen("1516.out","w",stdout);
	memset(dis,127,sizeof(dis));
	memset(f,127,sizeof(f));
	int n,m,v,e,a,b,w;
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(int i=1;i<=n;i++){
		scanf("%d",c+i);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",d+i);
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",k+i);
	}
	for(int i=1;i<=v;i++){
		dis[i][i]=0;
	} 
	while(e--){
		scanf("%d%d%d",&a,&b,&w);
		apmin(dis[a][b],w);
		apmin(dis[b][a],w);
	}
	for(int t=1;t<=v;t++){
		for(int i=1;i<=v;i++){
			for(int j=1;j<=v;j++){
				apmin(dis[i][j],dis[i][t]+dis[t][j]);
			}
		}
	}
	double d10,d01,d11;
	f[1][0][0]=0;
	f[1][1][1]=0;
	for(int i=2,dcc,ddc,dcd,ddd;i<=n;i++){
		dcc=dis[c[i-1]][c[i]];
		ddc=dis[d[i-1]][c[i]];
		dcd=dis[c[i-1]][d[i]];
		ddd=dis[d[i-1]][d[i]];
		f[i][0][0]=f[i-1][0][0]+dcc;
		cout<<"f["<<i<<"][0][0]="<<f[i][0][0]<<endl;
		cout<<"f["<<i<<"][0][1]="<<f[i][0][1]<<endl;
		d10=k[i-1]*ddc+(1-k[i-1])*dcc;
		d01=k[i]*dcd+(1-k[i])*dcc;
		d11=k[i-1]*(k[i]*ddd+(1-k[i])*ddc)+(1-k[i-1])*(k[i]*dcd+(1-k[i])*dcc);
		for(int j=1;j<=m&&j<=i;j++){
			f[i][j][0]=min(f[i-1][j][0]+dcc,f[i-1][j][1]+d10);
			f[i][j][1]=min(f[i-1][j-1][0]+d01,f[i-1][j-1][1]+d11);
			cout<<"f["<<i<<"]["<<j<<"][0]="<<f[i][j][0]<<endl;
			cout<<"f["<<i<<"]["<<j<<"][1]="<<f[i][j][1]<<endl;
		}
	}
	double ans=INF,cur;
	for(int i=0;i<=m;i++){
		apmin(ans,min(f[n][i][0],f[n][i][1]));
	}
	printf("%.2f",(double)round(ans*100)/100.0);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
