#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=2010,INF=0x7f7f7f7f;
struct coor{
	int x,y;
};
typedef vector<coor>vi;
char mat[N][N];
int dis[N][N];
bool vis[N][N];
struct state{
	int x,y,d;
	inline friend bool operator < (const state &a,const state &b){
		return a.d>b.d;
	}
};
priority_queue<state>q;
vi que[N*2];
char ansstr[N*2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni,k=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	memset(dis,127,sizeof(dis));
	dis[1][1]=mat[1][1]!='a';
	q.push((state){1,1,mat[1][1]!='a'});
	int tdis=1;
	for(;!q.empty();){
		int x=q.top().x,y=q.top().y,d=q.top().d;
		q.pop();
		if(d>k||d>dis[x][y])continue;
		vis[x][y]=true;
		apmax(tdis,x+y);
		if(x<n&&dis[x+1][y]>d+(mat[x+1][y]!='a')){
			dis[x+1][y]=d+(mat[x+1][y]!='a');
			q.push((state){x+1,y,dis[x+1][y]});
		}
		if(y<n&&dis[x][y+1]>d+(mat[x][y+1]!='a')){
			dis[x][y+1]=d+(mat[x][y+1]!='a');
			q.push((state){x,y+1,dis[x][y+1]});
		}
	}
	memset(ansstr,'z',sizeof(ansstr));
	for(int i=2;i<=tdis;i++){
		ansstr[i]='a';
	}
	if(tdis==1){
		que[2].push_back((coor){1,1});
		ansstr[2]=mat[1][1];
		tdis=2;
	}else for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(vis[i][j]&&i+j==tdis){
				que[tdis].push_back((coor){i,j});
			}
		}
	}
	for(int len=tdis;len<n*2;len++){
		for(int i=0,ti=que[len].size();i<ti;i++){
			int x=que[len][i].x,y=que[len][i].y;
			if(x<n){
				apmin(ansstr[len+1],mat[x+1][y]);
			}
			if(y<n){
				apmin(ansstr[len+1],mat[x][y+1]);
			}
		}
		for(int i=0,ti=que[len].size();i<ti;i++){
			int x=que[len][i].x,y=que[len][i].y;
			if(mat[x+1][y]==ansstr[len+1]&&!vis[x+1][y]){
				que[len+1].push_back((coor){x+1,y});
				vis[x+1][y]=true;
			}
			if(mat[x][y+1]==ansstr[len+1]&&!vis[x][y+1]){
				que[len+1].push_back((coor){x,y+1});
				vis[x][y+1]=true;
			}
		}
	}
	ansstr[n*2+1]=0;
	printf("%s\n",ansstr+2);
	return 0;
}
