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
const int MOD=123456789,N=610;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
int n,m,ans=0,mx[8]={-2,-1,1,2,2,1,-1,-2},my[8]={1,2,2,1,-1,-2,-2,-1};
bool mat[N][N];
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline bool valid2(int x,int y){
	bool res=mat[x][y];
	for(int i=0;i<8;i++){
		int tx=x+mx[i],ty=y+my[i];
		if(valid(tx,ty)){
			res^=mat[tx][ty];
		}
	}
	return res;
}
void check(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!valid2(i,j)){
				return;
			}
		}
	}
	apadd(ans,1);
}
void dfs(int x,int y){
	if(y>m){
		x++;
		y=1;
	}
	if(x>n){
		check();
		return;
	}
	mat[x][y]=false;
	dfs(x,y+1);
	mat[x][y]=true;
	dfs(x,y+1);
}
int main(){
	n=ni(),m=ni();
	dfs(1,1);
	printf("%d\n",ans);
}
