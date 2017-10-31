#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
const int N=101;
char mat[N][N];
short f[N][N][N][N],sum[N][N];
inline int asksum(int x1,int x2,int y1,int y2){
	return x1<=x2&&y1<=y2?sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1]:0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("exit.in","r",stdin);
	freopen("exit.out","w",stdout);
#endif
	int n=ni,m=ni,ex,ey;
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
		for(int j=1;j<=m;j++){
			sum[i][j]=(mat[i][j]=='o')+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			if(mat[i][j]=='E'){
				ex=i,ey=j;
			}
		}
	}
	for(int i=ex;i>=1;i--){
		for(int j=ex;j<=n;j++){
			for(int k=ey;k>=1;k--){
				for(int l=ey;l<=m;l++){
					short &F=f[i][j][k][l]=0;
					int xs=max(1+(j-ex),i),xt=min(n-(ex-i),j);
					int ys=max(1+(l-ey),k),yt=min(m-(ey-k),l);
					if(i<ex)apmax(F,f[i+1][j][k][l]+asksum(xs,i,ys,yt));
					if(j>ex)apmax(F,f[i][j-1][k][l]+asksum(j,xt,ys,yt));
					if(k<ey)apmax(F,f[i][j][k+1][l]+asksum(xs,xt,ys,k));
					if(l>ey)apmax(F,f[i][j][k][l-1]+asksum(xs,xt,l,yt));
				}
			}
		}
	}
	printf("%d\n",(int)f[1][n][1][m]);
	return 0;
}
