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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=5,M=8,O=12345678;
char mat[N][M];
bool vis[N*M];
int num[N][M];
lint ans=0;
int n,m;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline bool check(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			bool flag=false;
			for(int ti=i-1;ti<=i+1;ti++){
				for(int tj=j-1;tj<=j+1;tj++){
					if((ti!=i||tj!=j)&&valid(ti,tj)){
						flag|=num[ti][tj]<num[i][j];
					}
				}
			}
			if(flag!=(mat[i][j]=='.')){
				return false;
			}
		}
	}
	return true;
}
void dfs(int x,int y){
	if(y>m){
		x++,y=1;
	}
	if(x>n){
		ans+=check();
		return;
	}
	for(int i=1;i<=n*m;i++){
		if(!vis[i]){
			vis[i]=true;
			num[x][y]=i;
			dfs(x,y+1);
			vis[i]=false;
		}
	}
}
inline int Main(){
	ans=0;
	n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	dfs(1,1);
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("garden.in","r",stdin);
	freopen("garden.out","w",stdout);
#endif
	memset(vis,0,sizeof(vis));
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
