#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=510;
int n,m,rx[N],ry[N],dx[8]={-2,-1,1,2,2,1,-1,-2},dy[8]={1,2,2,1,-1,-2,-2,-1};
bool mat[N][N];
inline int gen(int l,int r){
	return rand()%(r-l+1)+l;
}
bool dfs(int x,int y,int rest){
	if(x<1||x>n||y<1||y>m||rest<0||mat[x][y]||(n-x)+(m-y)>rest*3||n-x>rest*2||m-y>rest*2){
		return false;
	}
	rx[rest]=x,ry[rest]=y;
	if(x==n&&y==m){
		return rest==0;
	}
	mat[x][y]=true;
	bool vis[8]={0};
	for(int i=0;i<10;i++){
		int d=gen(0,8);
		if(!vis[d]&&dfs(x+dx[d],y+dy[d],rest-1)){
			return true;
		}
		vis[d]=true;
	}
	for(int d=0;d<8;d++){
		if(!vis[d]&&dfs(x+dx[d],y+dy[d],rest-1)){
			return true;
		}
	}
	mat[x][y]=false;
	return false;
}
int main(){
	srand(time(NULL));
	rand();
	memset(mat,0,sizeof(mat));
	n=ni(),m=ni();
	int t=ni();
	if(!dfs(1,1,t)){
		cout<<"No can do"<<endl;
		return 0;
	}
	for(int i=t-1;i>=0;i--){
		printf("%d %d\n",rx[i],ry[i]);
	}
}
