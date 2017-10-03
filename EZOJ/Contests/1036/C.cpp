#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
inline char nchar() {
	static const int bufl=1<<20;
	static char buf[bufl],*a,*b;
	return a==b && (b=(a=buf)+fread(buf,1,bufl,stdin),a==b)?EOF:*a++;
}
inline int ni() {
	int x=0,f=1;
	char c=nchar();
	for (;!isdigit(c);c=nchar()) if (c=='-') f=-1;
	for (;isdigit(c);c=nchar()) x=x*10+c-'0';
	return x*f;
}
const int N=210,M=410;
int mat[N][M],pos[N][N];
int cur[N],lnk[N];
void dfs(int x){
	for(;;cur[x]++){
		int v=mat[x][cur[x]],u=lnk[v];
		if(v&&(u==0||pos[u][v]<pos[x][v])){
			lnk[v]=x;
			if(u){
				dfs(u);
			}
			return;
		}
	}
}
inline void Main(){
	int n=ni(),m=ni();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			pos[i][mat[i][j]=ni()]=j;
		}
	}
	for(int i=1;i<=n;i++){
		cur[i]=1;
	}
	memset(lnk+1,0,n<<2);
	for(int i=1;i<=n;i++){
		dfs(i);
	}
	for(int i=1;i<=n;i++){
		printf("%d ",mat[i][cur[i]]);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	for(int tot=ni();tot--;Main());
	return 0;
}
