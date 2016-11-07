#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 1010
using namespace std;
int f[2][M],rise[N],drop[N],up[N],down[N];
bool pipe[N],r;
inline void apmin(int &a,int b){
	if(b!=-1&&(a>b||a==-1)){
		a=b;
	}
}
int main(){
	int n,m,k,cnt=0,ans=-1;
	scanf("%d%d%d",&n,&m,&k);
	bool exist;
	for(int i=0;i<n;i++){
		scanf("%d%d",rise+i,drop+i);
		up[i]=m+1,down[i]=0;
	}
	memset(pipe,0,sizeof(pipe));
	for(int i=0,j;i<k;i++){
		scanf("%d",&j);
		pipe[j]=true;
		scanf("%d%d",up+j,down+j);
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++,r=!r){
		memset(f[r],-1,sizeof(f[r]));
		for(int j=max(down[i],rise[i-1])+1;j<up[i];j++){
			apmin(f[r][j],f[!r][j-rise[i-1]]+1);
			apmin(f[r][j],f[r][j-rise[i-1]]+1);
		}
		for(int j=down[i]+1;j<up[i]&&j+drop[i-1]<up[i-1];j++){
			apmin(f[r][j],f[!r][j+drop[i-1]]);
		}
		if(up[i]>m){
			for(int j=m-rise[i-1];j<=m;j++){
				apmin(f[r][m],f[!r][j]);
			}
		}
		exist=false;
		for(int j=down[i]+1;j<up[i];j++){
			if(f[r][j]!=-1){
				exist=true;
				break;
			}
		}
		if(!exist){
			cout<<0<<endl<<cnt;
			return 0;
		}
		if(pipe[i]){
			cnt++;
		}
	}
	r=!r;
	for(int i=1;i<=m;i++){
		apmin(ans,f[r][i]);
	}
	cout<<1<<endl<<ans;
}
