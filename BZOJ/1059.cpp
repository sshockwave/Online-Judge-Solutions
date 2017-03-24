#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int N=210;
int n,linker[N];
bool mat[N][N],vis[N];
bool hung(int x){
	for(int i=0;i<n;i++){
		if(mat[x][i]&&!vis[i]){
			vis[i]=true;
			if(linker[i]==-1||hung(linker[i])){
				linker[i]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	for(int tot=ni();tot--;){
		n=ni();
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				mat[i][j]=ni();
			}
		}
		memset(linker,-1,sizeof(linker));
		int cnt=0;
		for(int i=0;i<n;i++){
			memset(vis,0,sizeof(vis));
			if(hung(i)){
				cnt++;
			}
		}
		puts(n==cnt?"Yes":"No");
	}
}
