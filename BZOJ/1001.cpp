#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define R 1010
#define C 1010
#define E (R*C*3)
#define V (E-R*C+2)
using namespace std;
int to[E],val[E],bro[E],head[V],etop=0,ntop=1,ld[R][C],ur[R][C],que[V],qend,dis[V],qpos[V];
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline int new_node(){
	return ntop++;
}
inline void add_edge(int u,int v,int w,bool rev){
	if(rev){
		add_edge(v,u,w,false);
	}
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
inline int pop(int i,int j){
	while(i!=j){
		swap(que[i],que[j]);
		qpos[que[i]]=i;
		qpos[que[j]]=j;
		i=j;
		if((j<<1)<qend&&dis[que[j<<1]]<dis[que[i]]){
			i=(j<<1);
		}
		if(((j<<1)|1)<qend&&dis[que[(j<<1)|1]]<dis[que[i]]){
			i=(j<<1)|1;
		}
	}
	return que[qend];
}
inline void update(int x){
	for(x=qpos[x];x>1&&(que[x>>1]>que[x]);x>>=1){
		swap(que[x>>1],que[x]);
		qpos[que[x>>1]]=x>>1;
		qpos[que[x]]=x;
	};
	int y=x;
	if((x<<1)<qend&&dis[que[x<<1]]<dis[que[y]]){
		y=(x<<1);
	}
	if(((x<<1)|1)<qend&&dis[que[(x<<1)|1]]<dis[que[y]]){
		y=(x<<1)|1;
	}
	pop(x,y);
}
int main(){
	int s=new_node(),t=new_node(),r=nextInt(),c=nextInt();
	for(int i=1;i<r;i++){
		ld[i][c]=t;
		ur[i][0]=s;
	}
	for(int i=1;i<c;i++){
		ld[0][i]=t;
		ur[r][i]=s;
	}
	for(int i=1;i<r;i++){
		for(int j=1;j<c;j++){
			ld[i][j]=new_node();
			ur[i][j]=new_node();
		}
	}
	memset(head,-1,sizeof(head));
	for(int i=1;i<=r;i++){
		for(int j=1;j<c;j++){
			add_edge(ld[i-1][j],ur[i][j],nextInt(),true);
		}
	}
	for(int i=1;i<r;i++){
		for(int j=1;j<=c;j++){
			add_edge(ur[i][j-1],ld[i][j],nextInt(),true);
		}
	}
	for(int i=1;i<r;i++){
		for(int j=1;j<c;j++){
			add_edge(ld[i][j],ur[i][j],nextInt(),true);
		}
	}
	memset(dis,127,sizeof(dis));
	qend=ntop;
	for(int i=1;i<qend;i++){
		que[i]=i;
		qpos[i]=i;
	}
	dis[s]=0;
	while(qend>1){
		int x=pop(--qend,1);
		for(int i=head[x];~i;i=bro[i]){
			if(dis[to[i]]>dis[x]+val[i]){
				dis[to[i]]=dis[x]+val[i];
				update(to[i]);
			}
		}
	}
	printf("%d",dis[t]);
}
