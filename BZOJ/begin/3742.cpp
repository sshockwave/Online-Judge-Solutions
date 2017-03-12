#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 10
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int n,MOD;
long long ans[N],cache[N][N]={
	{0},
	{0,1},
	{0,1,1},
	{0,2,2,4},
	{0,8,6,12,38},
	{0,64,32,48,152,728},
	{0,1024,320,320,760,3640,26704},
	{0,32768,6144,3840,6080,21840,160224,1866256},
};
bool con[N][N],vis[N];
int hamilton(int x){
	int ret=0;
	vis[x]=true;
	for(int i=1;i<=n;i++){
		if(con[x][i]&&!vis[i]){
			apmax(ret,hamilton(i));
		}
	}
	vis[x]=false;
	return ret+1;
}
inline void dfs(int i,int j){
	if(j==n+1){
		i++,j=i+1;
		if(i==n){
			(ans[hamilton(1)]+=1)%=MOD;
			return;
		}
	}
	con[i][j]=true;
	dfs(i,j+1);
	con[i][j]=false;
	con[j][i]=true;
	dfs(i,j+1);
	con[j][i]=false;
}
int main(){
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	n=ni(),MOD=ni();
	if(n<=7){
		for(int i=1;i<=n;i++){
			printf("%d\n",cache[n][i]%MOD);
		}
		return 0;
	}
	memset(vis,0,sizeof(vis));
	memset(ans,0,sizeof(ans));
	dfs(1,2);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]%MOD);
	}
	return 0;
}
