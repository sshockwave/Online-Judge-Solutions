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
const int N=12,M=10010;
int n,m;
int mat[N][M],tag[N][M];
int tim=0;
lint dis[N][M];
struct state{
	int x,y;
	lint d;
	inline friend bool operator < (const state &a,const state &b){
		return a.d>b.d;
	}
};
inline lint Main(){
	int sx=ni,sy=ni,tx=ni,ty=ni;
	tim++;
	priority_queue<state>q;
	q.push((state){sx,sy,mat[sx][sy]});
	for(;!q.empty();q.pop()){
		int x=q.top().x,y=q.top().y;
		if(tag[x][y]==tim){
			continue;
		}
		dis[x][y]=q.top().d;
		tag[x][y]=tim;
		if(x==tx&&y==ty){
			return dis[x][y];
		}
		static int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
		for(int i=0;i<4;i++){
			int tx=x+dx[i],ty=y+dy[i];
			if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&tag[tx][ty]!=tim){
				q.push((state){tx,ty,dis[x][y]+mat[tx][ty]});
			}
		}
	}
	return -1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
#endif
	memset(tag,0,sizeof(tag));
	n=ni,m=ni;
	int tot=ni;
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			mat[i][j]=ni;
		}
	}
	for(;tot--;printf("%lld\n",Main()));
	return 0;
}
