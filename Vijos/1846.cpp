#include <iostream>
#include <cstdio>
#include <cstring>
#define N 35
#define S 810000
#define INF 2147483647
using namespace std;
bool mat[N][N];
int tx,ty,ans,dis[S],mx[4]={0,1,0,-1},my[4]={1,0,-1,0},n,m,q,qtop=1,qpos[S];
inline int abs(int a){
	return a>0?a:-a;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m&&mat[x][y];
}
struct state{
	int ex,ey,sx,sy,hash,exp;
	state(){}
	state(int a,int b,int c,int d){
		ex=a,ey=b,sx=c,sy=d;
		hash=sy-1+30*(sx-1+30*(ey-1+30*(ex-1)));
		exp=abs(tx-sx)+abs(ty-sy);
	}
}cur,que[S];
bool operator < (state a,state b){
	return dis[a.hash]+a.exp<dis[b.hash]+b.exp;
}
inline void maintain(int pos){
	for(;pos>1&&que[pos]<que[pos>>1];pos>>=1){
		qpos[que[pos>>1].hash]=pos;
		qpos[que[pos].hash]=pos>>1;
		swap(que[pos],que[pos>>1]);
	}
}
inline void push(state x){
	que[qtop]=x;
	qpos[x.hash]=qtop;
	qtop++;
}
inline state pop(){
	qtop--;
	int p=1,v=qtop;
	while(p!=v){
		qpos[que[p].hash]=v;
		qpos[que[v].hash]=q;
		swap(que[p],que[v]);
		v=p;
		if(que[p<<1]<que[v]){
			v=p<<1;
		}
		if(que[(p<<1)+1]<que[v]){
			v=(p<<1)+1;
		}
	}
	qpos[que[qtop].hash]=0;
	return que[qtop];
}
int main(){
	int qry,ex,ey,sx,sy,shash,tmp;
	scanf("%d%d%d",&n,&m,&qry);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&tmp);
			mat[i][j]=(tmp==1);
		}
	}
	while(qry--){
		scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&tx,&ty);
		memset(dis,127,sizeof(dis));
		memset(qpos,0,sizeof(qpos));
		dis[sy-1+30*(sx-1+30*(ey-1+30*(ex-1)))]=0;
		ans=-1;
		push(state(ex,ey,sx,sy));
		while(qtop>1){
			cur=pop();
			cout<<"ex="<<cur.ex<<"\tey="<<cur.ey<<"\tsx="<<cur.sx<<"\tsy="<<cur.sy<<"\tdis="<<dis[cur.hash]<<endl;
			if(sx==tx&&sy==ty){
				ans=dis[cur.hash];
				break;
			}
			for(int i=0;i<4;i++){
				ex=cur.ex+mx[i],ey=cur.ey+my[i];
				if(!valid(ex,ey)){
					continue;
				}
				if(ex==cur.sx&&ey==cur.sy){
					sx=cur.ex,sy=cur.ey;
				}else{
					sx=cur.sx,sy=cur.sy;
				}
				shash=sy-1+30*(sx-1+30*(ey-1+30*(ex-1)));
				if(dis[shash]>dis[cur.hash]+1){
					dis[shash]=dis[cur.hash]+1;
					if(qpos[shash]==0){
						push(state(ex,ey,sx,sy));
					}
					maintain(qpos[shash]);
				}
			}
		}
		printf("%d\n",ans);
	}
}
