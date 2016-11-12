#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 510
using namespace std;
int mat[N][N],quex[N*N],quey[N*N],n,m,mx[4]={0,1,0,-1},my[4]={1,0,-1,0};
bool vis[N][N];
struct section{
	int l,r;
}s[N];
inline bool seccmp(const section &a,const section &b){
	return a.l<b.l;
}
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&mat[i][j]);
		}
	}
	int qhead=0,qtail=0,x,y,cnt=0,reach=0;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;i++){
		quex[qtail]=1,quey[qtail]=i,qtail++;
		vis[1][i]=true;
	}
	while(qhead!=qtail){
		x=quex[qhead],y=quey[qhead],qhead++;
		for(int i=0;i<4;i++){
			if(valid(x+mx[i],y+my[i])&&!vis[x+mx[i]][y+my[i]]){
				quex[qtail]=x+mx[i],quey[qtail]=y+my[i],qtail++;
				vis[x+mx[i]][y+my[i]]=true;
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(!vis[n][i]){
			cnt++;
		}
	}
	if(cnt){
		printf("0\n%d",cnt);
		return 0;
	}
	for(int i=1;i<=m;i++){
//		cout<<"Start BFS of "<<i<<endl;
		memset(vis,0,sizeof(vis));
		qhead=qtail=0;
		quex[qtail]=1,quey[qtail]=i,qtail++;
		vis[1][i]=true;
		while(qhead!=qtail){
			x=quex[qhead],y=quey[qhead],qhead++;
//			cout<<"\tCur: ("<<x<<","<<y<<")"<<endl;
			for(int j=0;j<4;j++){
				if(valid(x+mx[j],y+my[j])&&!vis[x+mx[j]][y+my[j]]){
					quex[qtail]=x+mx[j],quey[qtail]=y+my[j],qtail++;
					vis[x+mx[j]][y+my[j]]=true;
				}
			}
		}
		for(s[i].l=1;s[i].l<=m&&!vis[s[i].l];s[i].l++);
		for(s[i].r=m;s[i].r>=1&&!vis[s[i].r];s[i].r--);
//		cout<<"City "<<i<<": ("<<s[i].l<<","<<s[i].r<<")"<<endl;
	}
	sort(s+1,s+m+1,seccmp);
	cnt=0;
//	cout<<"Greedy"<<endl;
	int j=1;
	for(int i=1;i<=m&&j<=m;i++){
//		cout<<"Currently ("<<s[i].l<<","<<s[i].r<<")"<<endl;
		if(s[i].l>j){
			j=reach+1;
			cnt++;
		}
		if(s[i].r>reach){
//			cout<<"Reach->"<<s[i].r<<endl;
			reach=s[i].r;
		}
	}
	if(j<=m){
		cnt++;
	}
	printf("1\n%d",cnt);
}
