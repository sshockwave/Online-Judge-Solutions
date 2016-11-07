#include <iostream>
#include <cstdio>
#include <cstring>
#define N 110
#define INF 2147483647
using namespace std;
int mat[N][N],pre[N][N],xl,xr;
inline int getsum(int x1,int y1,int x2,int y2){
	return pre[x2][y2]-pre[x2][y1-1]-pre[x1-1][y2]+pre[x1-1][y1-1];
}
inline int apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
int bchop(int l,int r){
	if(l==r){
		return getsum(xl,l,xr,r);
	}
	int mid=(l+r)/2,lmax=-INF,rmax=-INF;
	int ans=max(bchop(l,mid),bchop(mid+1,r));
	for(int i=mid;i>=l;i--){
		apmax(lmax,getsum(xl,i,xr,mid));
	}
	for(int j=mid+1;j<=r;j++){
		apmax(rmax,getsum(xl,mid+1,xr,j));
	}
	return max(ans,lmax+rmax);
}
int main(){
	memset(pre,0,sizeof(pre));
	int n,ans=-INF;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&mat[i][j]);
			pre[i][j]=mat[i][j]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
		}
		for(int j=1;j<=i;j++){
			xl=j,xr=i;
			apmax(ans,bchop(1,n));
		}
	}
	printf("%d",ans);
}
