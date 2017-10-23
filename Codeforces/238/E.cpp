#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b){a=b;}}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a){a=b;}}
const int N=110,INF=0x7f7f7f7f;
int n,m;
bool con[N][N];
int dis[N][N],sline[N],tline[N],reach[N][N];
bool mark[N][N];
bool vis[N];
inline void markkey(int id){
	int u=sline[id],v=tline[id];
	queue<int>q;
	memset(vis+1,0,n);
	vis[u]=true,q.push(u);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		if(q.empty()){
			mark[id][x]=true;
		}
		for(int i=1;i<=n;i++){
			if(con[x][i]&&dis[i][v]==dis[x][v]-1&&!vis[i]){
				vis[i]=true,q.push(i);
			}
		}
	}
}
inline void relax(){
	for(int i=1;i<=n;i++){
		int allmin=INF;
		for(int j=1;j<=m;j++){
			int t=-INF;
			for(int k=1;k<=n;k++){
				if(con[i][k]&&dis[i][tline[j]]==dis[k][tline[j]]+1){
					apmax(t,reach[k][j]);
				}
			}
			if(t>-INF){
				apmin(reach[i][j],t);
			}
			if(mark[j][i]){
				apmin(allmin,reach[i][j]);
			}
		}
		allmin++;
		for(int j=1;j<=m;j++){
			apmin(reach[i][j],allmin);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("meet.in","r",stdin);
	freopen("meet.out","w",stdout);
#endif
	n=ni;
	int tot=ni,s=ni,t=ni;
	memset(dis,127,sizeof(dis));
	for(int u,v;tot--;u=ni,v=ni,dis[u][v]=con[u][v]=1);
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(dis[i][k]<INF){
				for(int j=1;j<=n;j++){
					if(dis[k][j]<INF){
						apmin(dis[i][j],dis[i][k]+dis[k][j]);
					}
				}
			}
		}
	}
	m=ni;
	for(int i=1;i<=m;i++){
		sline[i]=ni,tline[i]=ni;
		if(dis[sline[i]][tline[i]]<INF){
			markkey(i);
		}else{
			i--,m--;
		}
	}
	memset(reach,127,sizeof(reach));
	for(int i=1;i<=m;i++){
		reach[t][i]=1;
	}
	for(int i=1;i<=n;i++){
		relax();
	}
	int ans=INF;
	for(int i=1;i<=m;i++){
		if(mark[i][s]){
			apmin(ans,reach[s][i]);
		}
	}
	printf("%d\n",ans<INF?ans:-1);
	return 0;
}
