#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define M 300010
#define N 155
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
struct edge{
	int u,v;
}e[M];
int dfn[N],low[N],timer,bln[N],stk[N],stop=0,n,size[N];
bool con[N][N],vis[N],instk[N];
int tarjan(int x){
	dfn[x]=low[x]=timer++;
	stk[stop++]=x;
	vis[x]=true;
	instk[x]=true;
	for(int i=1;i<=n;i++){
		if(con[x][i]){
			if(instk[i]){
				apmin(low[x],low[i]);
			}else if(!vis[i]){
				apmin(low[x],tarjan(i));
			}
		}
	}
	if(dfn[x]==low[x]){
		do{
			stop--;
			bln[stk[stop]]=x;
			size[x]++;
		}while(stk[stop]!=x);
	}
	instk[x]=false;
	return low[x];
}
int main(){
	freopen("friend.in","r",stdin);
	freopen("friend.out","w",stdout);
	n=ni();
	int m=ni(),tot=ni();
	for(int i=1;i<=m;i++){
		e[i].u=ni(),e[i].v=ni();
	}
	while(tot--){
		int l=ni(),r=ni(),ans=0;
		memset(con,0,sizeof(con));
		for(int i=l;i<=r;i++){
			con[e[i].u][e[i].v]=true;
		}
		timer=0;
		memset(vis,0,sizeof(vis));
		memset(instk,0,sizeof(instk));
		memset(size,0,sizeof(size));
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				tarjan(i);
			}
		}
		for(int i=1;i<=n;i++){
			if(bln[i]==i&&size[i]>1){
				ans+=size[i]*(size[i]-1)/2;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
