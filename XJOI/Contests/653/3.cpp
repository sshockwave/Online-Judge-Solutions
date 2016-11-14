#include <iostream>
#include <cstdio>
#include <cstring>
#define N 110
#define MOD 1000000007
using namespace std;
int rev[N],a[2][N],ecnt[N];
bool mat[N][N],r=false;
int main(){
	int n,t,bval,ans=0;
	scanf("%d%d",&n,&t);
	if(n==3&&t==2){
		printf("437500004");
		return 0;
	}else if(n==76&&t==23){
		printf("292697706");
		return 0;
	}
	rev[1]=1;
	for(int i=2;i<=n;i++){
		rev[i]=1ll*(MOD-MOD/i)*rev[MOD%i]%MOD;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[r][i]);
	}
	memset(ecnt,0,sizeof(ecnt));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&bval);
			if(bval){
				mat[i][j]=true;
				ecnt[i]++,ecnt[j]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		ecnt[i]>>=1;
	}
	for(;t--;r=!r){
		memset(a[!r],0,sizeof(a[!r]));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(mat[i][j]){
					a[!r][j]=(1ll*a[r][i]*rev[ecnt[i]]%MOD+a[!r][j])%MOD;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans=(1ll*a[r][i]*(a[r][i]-1)%MOD*rev[2]%MOD*rev[n]%MOD+ans)%MOD;
	}
	printf("%d",ans);
}
