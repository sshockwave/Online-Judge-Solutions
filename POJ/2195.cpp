#include <iostream>
#include <cstdio>
#include <cstring>
#define C 110
#define N 110
#define V 210
#define E 25000
#define INF 0x7f7f7f7f
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline int abs(int a){
	return a>0?a:-a;
}
struct point{
	int x,y,i;
}men[N],house[N];
int to[E],val[E],cap[E],bro[E],head[V],dis[V],etop,ntop,s,t;
inline void add_edge(int u,int v,int w,int c,bool ori){//zero is original
	to[etop]=v;
	val[etop]=w;
	cap[etop]=c;
	bro[etop]=head[u];
	head[u]=etop++;
	if(ori){
		add_edge(v,u,-w,0,0);
	}
}
inline int new_node(){
	return ntop++;
}
inline void reset(){
	memset(head,-1,sizeof(head));
	etop=ntop=0;
}
char str[110];
inline void problem(int r,int c){
	int mcnt=0,hcnt=0;
	s=new_node(),t=new_node();
	for(int i=0;i<r;i++){
		scanf("%s",str);
		for(int j=0;j<c;j++){
			if(str[j]=='H'){
				house[hcnt]=(point){i,j,new_node()};
				add_edge(house[hcnt++].i,t,0,1,1);
			}else if(str[j]=='m'){
				men[mcnt]=(point){i,j,new_node()};
				add_edge(s,men[mcnt++].i,0,1,1);
			}
		}
	}
	for(int i=0;i<mcnt;i++){
		for(int j=0;j<hcnt;j++){
			add_edge(men[i].i,house[j].i,abs(men[i].x-house[i].x)+abs(men[i].y-house[i].y),1,1);
		}
	}
}
int que[V],qhead,qtail;
bool inque[V];
inline void spfa(){
	memset(inque,0,sizeof(inque));
	memset(dis,127,sizeof(dis));
	qhead=qtail=0;
	dis[s]=0;
	que[qtail++]=s;
	inque[s]=true;
	while(qhead!=qtail){
		int x=que[qhead++];
		if(qhead==V){
			qhead=0;
		}
		for(int i=head[x];~i;i=bro[i]){
			if(cap[i]&&dis[to[i]]>dis[x]+val[i]){
				dis[to[i]]=dis[x]+val[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					que[qtail++]=to[i];
					if(qtail==V){
						qtail=0;
					}
				}
			}
		}
		inque[x]=false;
	}
}
int flow(int x,int allo){
	int sum=0,inc;
	for(int i=head[x];~i;i=bro[i]){
		if(cap[i]&&dis[to[i]]==dis[x]+val[i]){
			inc=flow(to[i],min(allo-sum,cap[i]));
			sum+=inc,cap[i]-=inc,cap[i^1]+=inc;
			if(sum==allo){
				break;
			}
		}
	}
	return sum;
}
inline int mcmf(){
	int sum=0;
	while(spfa(),dis[t]<INF){
		sum+=flow(s,INF)*dis[t];
	}
	return sum;
}
int main(){
	int r,c;
	while((r=next_int())&&(c=next_int())){
		reset();
		problem(r,c);
		printf("%d\n",mcmf());
	}
}
