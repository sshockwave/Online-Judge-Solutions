#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 0x7f7f7f7f
#define N 20
#define EPS 1e-10 
using namespace std;
double x[N],y[N];
int n,m,nxt[N][N],f[1<<N];
bool rise[N][N];
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline bool eqzero(double x){
	return x>=-EPS&&x<=EPS;
}
int main(){
	freopen("1519.in","r",stdin);
	freopen("1519.out","w",stdout);
	int tot;
	for(scanf("%d",&tot);tot--;){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%lf%lf",x+i,y+i);
		}
		memset(nxt,-1,sizeof(nxt));
		memset(rise,0,sizeof(rise));
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if((x[i]-x[j])*(y[i]*x[j]-y[j]*x[i])>=-EPS){
					rise[i][j]=true;
					continue;
				}
				for(int k=j+1;k<n;k++){
					if(x[i]==x[k]||x[j]==x[k]){
						continue;
					}
					if(eqzero(y[i]*x[j]*x[k]*(x[j]-x[k])+y[j]*x[i]*x[k]*(x[k]-x[i])+y[k]*x[i]*x[j]*(x[i]-x[j]))){
						nxt[i][j]=k;
						break;
					}
				}
			}
		}
		memset(f,127,sizeof(f));
		f[0]=0;
		for(int x=0,m=1<<n,cur,i;x<m-1;x++){
			if(f[x]==INF){
				continue;
			}
			for(i=0;i<n&&((x>>i)&1);i++);
			apmin(f[x|(1<<i)],f[x]+1);
			for(int j=i+1;j<n;j++){
				if((x>>j)&1||rise[i][j]){
					continue;
				}
				cur=x|(1<<i);
				for(int k=j;~k;k=nxt[i][k]){
					cur|=(1<<k);
				}
				apmin(f[cur],f[x]+1);
			}
		}
		printf("%d\n",f[(1<<n)-1]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
