#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 200010
using namespace std;
int to[M],bro[M],head[N],que[N],qhead,qend,rto[M],rbro[M],rhead[N],dis[N];
bool inque[N],con[N],valid[N];
int main(){
	memset(head,-1,sizeof(head));
	memset(rhead,-1,sizeof(rhead));
	int n,m,x,s,t;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",rto+i,to+i);
		bro[i]=head[rto[i]];
		rbro[i]=rhead[to[i]];
		head[rto[i]]=i;
		rhead[to[i]]=i;
	}
	scanf("%d%d",&s,&t);
	//bfs 1
	memset(con,0,sizeof(con));
	qhead=qend=0;
	que[qend++]=t;
	con[t]=true;
	while(qhead<qend){
		x=que[qhead++];
		for(int i=rhead[x];~i;i=rbro[i]){
			if(!con[rto[i]]){
				que[qend++]=rto[i];
				con[rto[i]]=true;
			}
		}
	}
	//valid points check
	for(int x=1;x<=n;x++){
		valid[x]=con[x];
		if(!con[x]){
			continue;
		}
		for(int i=head[x];~i;i=bro[i]){
			if(!con[to[i]]){
				valid[x]=false;
				break;
			}
		}
	}
	//spfa
	memset(inque,0,sizeof(inque));
	memset(dis,-1,sizeof(dis));
	qhead=qend=0;
	if(!valid[s]){
		cout<<"-1";
		return 0;
	}
	que[qend++]=s;
	inque[s]=true;
	dis[s]=0;
	while(qhead<qend){
		x=que[qhead++];
		inque[x]=false;
		for(int i=head[x];~i;i=bro[i]){
			if(valid[to[i]]){
				if(dis[to[i]]==-1||dis[to[i]]>dis[x]+1){
					dis[to[i]]=dis[x]+1;
					if(!inque[to[i]]){
						que[qend++]=to[i];
						inque[to[i]]=true;
					}
				}
			}
		}
	}
	printf("%d",dis[t]);
}
