#include <iostream>
#include <cstdio>
#include <cstring>
//#include <ctime>
#define N 50010
#define INF 2147483647
using namespace std;
int l[N],r[N],f[N][2];
inline int abs(int a){
	return a>0?a:-a;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int main(){
	freopen("1421.in","r",stdin);
	freopen("1421.out","w",stdout);
	int n,s,ans=INF;
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d%d",l+i,r+i);
	}
	l[n+1]=r[n+1]=s,f[n+1][0]=f[n+1][1]=0;
	for(int i=n;i>0;i--){
		f[i][0]=f[i][1]=INF;
		for(int j=n+1;j>i;j--){
			if(l[j]!=INF){
				apmin(f[i][0],abs(l[j]-l[i])+f[j][0]);
				apmin(f[i][1],abs(l[j]-r[i])+f[j][0]);
				if(l[i]<=l[j]&&l[j]<=r[i]){
					l[j]=INF;
				}
			}
			if(r[j]!=INF){
				apmin(f[i][0],abs(r[j]-l[i])+f[j][1]);
				apmin(f[i][1],abs(r[j]-r[i])+f[j][1]);
				if(l[i]<=r[j]&&r[j]<=r[i]){
					r[j]=INF;
				}
			}
		}
	}
	for(int i=n+1;i>0;i--){
		if(l[i]!=INF){
			apmin(ans,abs(l[i])+f[i][0]);
			apmin(ans,abs(l[i])+f[i][0]);
		}
		if(r[i]!=INF){
			apmin(ans,abs(r[i])+f[i][1]);
			apmin(ans,abs(r[i])+f[i][1]);
		}
	}
	printf("%d",ans);
//	printf("\n%dms",clock());
}
