#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 1010
using namespace std;
int f[2][M],rise[N],drop[N],up[N],down[N];
bool pipe[N],r=false;
inline void apmin(int &a,int b){
	if(a>b||a==-1){
		a=b;
	}
}
int main(){
	int n,m,k,cnt=0;
	scanf("%d%d%d",&n,&m,&k);
	bool exist;
	for(int i=0;i<n;i++){
		scanf("%d%d",rise+i,drop+i);
		up[i]=m+1,down[i]=0;
	}
	memset(pipe,0,sizeof(pipe));
	for(int i=0,j;i<k;i++){
		scanf("%d",&j);scanf("%d%d",up+j,down+j);
		pipe[j]=true;
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<n;i++,r=!r){
		memset(f[r],-1,sizeof(f[r]));
		for(int j=down[i]+1;j<up[i];j++){
			if(j>rise[i-1]){
				if(f[!r][j-rise[i-1]]!=-1){
					apmin(f[r][j],f[!r][j-rise[i-1]]+1);
				}
				if(f[r][j-rise[i-1]]!=-1){
					apmin(f[r][j],f[r][j-rise[i-1]]+1);
				}
			}
		}
		for(int j=down[i]+1;j<up[i]&&j+drop[i-1]<up[i-1];j++){
			if(f[!r][j+drop[i-1]]!=-1){
				apmin(f[r][j],f[!r][j+drop[i-1]]);
			}
		}
		if(up[i]>m){
			for(int j=m-rise[i-1];j<=m;j++){
				if(f[!r][j]!=-1){
					apmin(f[r][m],f[!r][j]);
				}
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
			break;
		}
		if(pipe[i]){
			cnt++;
		}
	}
	if(exist){
		int minn=-1;
		r=-r;
		for(int i=1;i<m;i++){
			if(f[r][i]!=-1){
				apmin(minn,f[r][i]);
			}
		}
		cout<<1<<endl<<minn;
	}else{
		cout<<0<<endl<<cnt;
	}
}