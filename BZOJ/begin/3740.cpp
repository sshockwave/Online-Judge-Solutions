#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
#include <ctime>
#define M 710
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
struct coor{
	int x,y;
	coor(){
	}
	coor(int i,int j){
		x=i,y=j;
	}
}ship[M*M];
int mx[4]={-1,0,1,0},my[4]={0,1,0,-1},stat[M][M],stop=0;
bool vis[M][M],reach[M][M];
char mat[M][M];
queue<coor>q;
inline int trans(int x){
	return x+(M/2);
}
inline void push(int x,int y){
	if(!vis[trans(x)][trans(y)]){
		q.push(coor(x,y));
		vis[trans(x)][trans(y)]=true;
	}
}
int main(){
	freopen("sailing.in","r",stdin);
	freopen("sailing.out","w",stdout);
	int n=ni(),m=ni();
	for(int i=0;i<n;i++){
		gets(mat[i]);
	}
	memset(stat,0,sizeof(stat));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(mat[i][j]!='#'){
				if(mat[i][j]=='o'){
					ship[stop++]=coor(i,j);
				}
				for(int d=0,tx,ty;d<4;d++){
					tx=i+mx[d],ty=j+my[d];
					if(tx>=0&&tx<n&&ty>=0&&ty<m&&mat[tx][ty]!='#'){
						stat[i][j]|=1<<d;
					}
				}
			}
		}
	}
	memset(vis,0,sizeof(vis));
	memset(reach,0,sizeof(reach));
	push(0,0);
	while(!q.empty()){
		int x=q.front().x,y=q.front().y;
		q.pop();
		int ext=15;
		for(int i=0;i<stop;i++){
			reach[ship[i].x+x][ship[i].y+y]=true;
			ext&=stat[ship[i].x+x][ship[i].y+y];
		}
		for(int d=0;d<4;d++){
			if(ext&(1<<d)){
				push(x+mx[d],y+my[d]);
			}
		}
	}
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(reach[i][j]){
				ans++;
			}
		}
	}
	printf("%d",ans);
}
