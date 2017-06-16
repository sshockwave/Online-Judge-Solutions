#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=110,INF=0x7f7f7f7f;
int n;
namespace G2{
	int dis[N][N];
	inline void init(){
		memset(dis,127,sizeof(dis));
		for(int i=1;i<=n;i++){
			dis[i][i]=0;
		}
	}
	inline void floyd(){
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
	}
}
namespace G1{
	bool con[N][N];
	inline void init(){
		memset(con,0,sizeof(con));
	}
	int dis[N],que[N];
	bool vis[N];
	inline void bfs1(int s){
		memset(dis,127,sizeof(dis));
		dis[s]=0;
		int qh=0,qt=0;
		que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=1;i<=n;i++){
				if(con[x][i]&&dis[i]==INF){
					dis[i]=dis[x]+1;
					que[qt++]=i;
				}
			}
		}
	}
	inline void bfs2(int t){
		int qh=0,qt=0;
		vis[t]=true;
		que[qt++]=t;
		while(qh<qt){
			int x=que[qh++];
			for(int i=1;i<=n;i++){
				if(con[i][x]&&dis[i]+1==dis[x]){
					vis[i]=true;
					que[qt++]=t;
				}
			}
		}
	}
	int pos[N];
	inline void work(int s,int t){
		bfs1(s),bfs2(t);
		memset(pos,0,sizeof(pos));
		for(int i=1;i<=n;i++){
			if(vis[i]){
				int &pt=pos[dis[i]];
				if(pt==0){
					pt=i;
				}else if(pt>0){
					pt=-1;
				}
			}
		}
		for(int i=0;i<n;i++){
			if(pos[i]>0){
				for(int j=i+1;j<n;j++){
					if(pos[j]>0){
						assert(pos[i]!=pos[j]);
						G2::dis[pos[i]][pos[j]]=1;
					}
				}
			}
		}
	}
}
int main(){
	int s,t;
	{
		n=ni;
		int tot=ni;
		s=ni,t=ni;
		G1::init();
		while(tot--){
			int u=ni,v=ni;
			G1::con[u][v]=true;
		}
	}
	{
		G2::init();
		for(int tot=ni;tot--;){
			int s=ni,t=ni;
			G1::work(s,t);
		}
	}
	printf("%d",(G2::floyd(),G2::dis[s][t]));
}