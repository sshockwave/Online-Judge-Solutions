#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define clr(x) memset((x),0,sizeof(x))
#define N 510
using namespace std;
int height[N][N],m,n,mx[4]={0,1,0,-1},my[4]={1,0,-1,0},quex[N*N],quey[N*N],qhead,qtail;
bool vis[N][N];
struct area{
	int l,r;
}sec[N];
bool operator < (area a,area b){
	return a.l<b.l;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline bool valid(int x,int y){
	return x>0&&x<=n&&y>0&&y<=m&&!vis[x][y];
}
inline void push(int x,int y){
	quex[qtail]=x;
	quey[qtail]=y;
	qtail++;
	vis[x][y]=true;
}
inline void bfs(){
	int x,y;
	while(qhead<qtail){
		x=quex[qhead],y=quey[qhead];
		qhead++;
		for(int i=0;i<4;i++){
			if(valid(x+mx[i],y+my[i])&&height[x][y]>height[x+mx[i]][y+my[i]]){
				push(x+mx[i],y+my[i]);
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&height[i][j]);
		}
	}/*
	clr(vis);
	qhead=qtail=0;
	for(int i=1;i<=m;i++){
		push(1,i);
	}
	bfs();
	for(int i=1;i<=m;i++){
		if(!vis[n][i]){
			cnt++;
		}
	}
	if(cnt){
		printf("0\n%d",cnt);
		return 0;
	}*/
	int cnt=0,reach;
	clr(sec);
	for(int i=1;i<=m;i++){
		clr(vis);
		qhead=qtail=0;
		push(1,i);
		bfs();
		sec[i].l=1,sec[i].r=m;
		for(int &l=sec[i].l;l<=m&&!vis[n][l];l++);
		for(int &r=sec[i].r;r>=1&&!vis[n][r];r--);
	}
	sort(sec+1,sec+1+m);
	cnt=reach=0;
	for(int i=1,j=1;i<=m&&j<=m;i++){
		if(sec[i].l<=j){
			apmax(reach,sec[i].r);
		}else{
			j=reach+1;
			cnt++;
		}
	}
	printf("1\n%d",cnt);
}
