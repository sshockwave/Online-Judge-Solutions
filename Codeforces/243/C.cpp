#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=2010,INF=-0x7f7f7f7f;
bool mat[N][N];
bool vis[N][N];
struct intv{
	int l,r;
	inline int len(){
		return r-l+1;
	}
}xlst[N],ylst[N];
int xs=0,ys=0;
struct Move{
	int d,l,x,y;
}q[N];
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
inline int getd(){
	char c;
	while(!isalpha(c=getchar()));
	return c=='U'?0:c=='R'?1:c=='U'?2:c=='D'?3:-1;
}
inline int binfind(intv lst[],int l,int r,int x){
	while(l<r){
		int m=(l+r)>>1;
		if(lst[m].l>x){
			l=m+1;
		}else{
			r=m;
		}
	}
	return l;
}
void dfs(int x,int y){
	vis[x][y]=true;
	for(int d=0;d<4;d++){
		int tx=x+dx[d],ty=y+dy[d];
		if(tx>=0&&tx<xs&&ty>=0&&ty<ys&&!vis[x][y]&&!mat[x][y]){
			dfs(tx,ty);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("potato.in","r",stdin);
	freopen("potato.out","w",stdout);
#endif
	int n=ni,x=0,y=0;
	set<int>sx,sy;
	sx.insert(0),sy.insert(0);
	for(int i=1;i<=n;i++){
		q[i]=(Move){getd(),ni,x,y};
		x+=dx[q[i].d]*q[i].l;
		y+=dy[q[i].d]*q[i].l;
		sx.insert(x),sy.insert(y);
	}
	q[n+1].x=x,q[n+1].y=y;
	int last=-INF;
	for(set<int>::iterator it=sx.begin();it!=sx.end();it++){
		if(last+1<*it){
			xlst[xs++]=(intv){last+1,*it-1};
		}
		last=*it;
		xlst[xs++]=(intv){*it,*it};
	}
	xlst[xs++]=(intv){last+1,INF};
	last=-INF;
	for(set<int>::iterator it=sy.begin();it!=sy.end();it++){
		if(last+1<*it){
			ylst[ys++]=(intv){last+1,*it-1};
		}
		last=*it;
		ylst[ys++]=(intv){*it,*it};
	}
	ylst[ys++]=(intv){last+1,INF};
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n;i++){
		int px=binfind(xlst,0,xs,q[i].x);
		int py=binfind(ylst,0,ys,q[i].y);
		for(;mat[px][py]=true,xlst[px].l!=q[i+1].x||ylst[py].l!=q[i+1].y;px+=dx[q[i].d],py+=dy[q[i].d]);
	}
	memset(vis,0,sizeof(vis));
	dfs(0,0);
	lint ans=0;
	for(int i=0;i<xs;i++){
		for(int j=0;j<ys;j++){
			if(!vis[i][j]){
				ans+=(lint)xlst[i].len()*ylst[j].len();
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
