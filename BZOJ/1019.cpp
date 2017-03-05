#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 33
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
long long f[3][N];
int g[3][N];
char s[5];
int main(){
	int n=ni();
	memset(g,-1,sizeof(g));
	for(int i=0;i<6;i++){
		scanf("%s",s);
		if(g[s[0]-'A'][1]==-1){
			g[s[0]-'A'][1]=s[1]-'A';
		}
	}
	f[0][1]=f[1][1]=f[2][1]=1;
	for(int j=2;j<=n;j++){
		for(int i=0;i<3;i++){
			if(g[g[i][j-1]][j-1]==i){
				f[i][j]=f[i][j-1]*2+f[g[i][j-1]][j-1]+2;
				g[i][j]=g[i][j-1];
			}else{
				f[i][j]=f[i][j-1]+f[g[i][j-1]][j-1]+1;
				g[i][j]=3^i^g[i][j-1];
			}
		}
	}
	printf("%lld",f[0][n]);
}
