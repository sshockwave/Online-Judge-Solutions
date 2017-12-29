#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=310,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int ns;
template<class T>inline int det(T mat){//[0,ns]
	for(int i=1;i<=ns;i++){
		for(int j=1;j<=ns;j++){
			if(mat[i][j]<0){
				mat[i][j]=mat[i][j]+O;
				assert(mat[i][j]>=0&&mat[i][j]<O);
			}
		}
	}
	int ans=1;
	for(int i=1,j;i<=ns;i++){
		for(j=i;j<=ns&&mat[j][i]==0;j++);
		if(j>ns)return 0;
		if(i!=j){
			ans=(O-ans)%O;
			for(int k=i;k<=ns;k++){
				swap(mat[i][k],mat[j][k]);
			}
		}
		ans=(lint)ans*mat[i][i]%O;
		int r=inv(mat[i][i]);
		for(int k=i;k<=ns;k++){
			mat[i][k]=(lint)mat[i][k]*r%O;
		}
		for(j=i+1;j<=ns;j++){
			if(mat[j][i]){
				r=mat[j][i];
				for(int k=i;k<=ns;k++){
					mat[j][k]=(mat[j][k]+O-(lint)mat[i][k]*r%O)%O;
				}
			}
		}
	}
	return ans;
}
char mat[N][N];
int n,m;
const static int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int node[N][N]; //-2:not okay -1:not vis >=0:belong to this
void dfs(int x,int y){
	node[x][y]=-2;
	int tx,ty;
	switch(mat[x][y]){
		case 'L':
			tx=x,ty=y-1;
			break;
		case 'R':
			tx=x,ty=y+1;
			break;
		case 'U':
			tx=x-1,ty=y;
			break;
		case 'D':
			tx=x+1,ty=y;
			break;
	}
	if(tx<1||tx>n||ty<1||ty>m){
		node[x][y]=0;
		return;
	}
	if(node[tx][ty]==-1){
		dfs(tx,ty);
	}
	node[x][y]=node[tx][ty];
}
int dis[N][N];
inline void ae(int u,int v){
	if(u!=v){
		dis[u][v]--;
		dis[u][u]++;
	}
}
inline int Main(){
	n=ni,m=ni;
	ns=0;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
		memset(node[i]+1,0,m<<2);
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='.'){
				node[i][j]=++ns;
			}else{
				node[i][j]=-1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(node[i][j]==-1){
				dfs(i,j);
				if(node[i][j]==-2)return 0;
			}
		}
	}
	for(int i=0;i<=ns;i++){
		memset(dis[i],0,(ns+1)<<2);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='.'){
				for(int d=0;d<4;d++){
					int x=i+dx[d],y=j+dy[d];
					if(x<1||x>n||y<1||y>m){
						ae(node[i][j],0);
					}else{
						ae(node[i][j],node[x][y]);
					}
				}
			}
		}
	}
	return det(dis);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dancestep.in","r",stdin);
	freopen("dancestep.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
