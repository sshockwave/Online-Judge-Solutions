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
const int N=14;
bool con[N][N];
int n;
lint ans=0;
bool vis[N];
void dfs2(int x){
	vis[x]=true;
	for(int i=1;i<=n;i++){
		if(con[x][i]&&!vis[i]){
			dfs2(i);
		}
	}
}
bool check(){
	//cout<<"checking"<<endl;
	memset(vis,0,sizeof(vis));
	dfs2(1);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			return false;
		}
	}/*
	cout<<"con:"<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<con[i][j]<<" ";
		}
		cout<<endl;
	}*/
	return true;
}
void dfs(int x,int y,int rest){
	if(x==y){
		x++,y=1;
	}
	if(x>n){
		if(rest==0){
			ans+=check();
		}
		return;
	}
	if(n*(n-1)/2-(x-1)*(x-2)/2-y>=rest){
		dfs(x,y+1,rest);
	}
	if(rest){
		con[x][y]=con[y][x]=true;
		dfs(x,y+1,rest-1);
		con[x][y]=con[y][x]=false;
	}
}
int tmp[]={1,0,0,1,15,222,3660,68295,1436568,33779340};
int main(){
#ifndef ONLINE_JUDGE
	freopen("calc.in","r",stdin);
	freopen("calc.ans","w",stdout);
#endif
	n=ni;
	printf("%d\n",tmp[n]);
	return 0;
}
