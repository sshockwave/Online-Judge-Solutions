#include <iostream>
#include <cstdio>
#include <cstring>
//#include <ctime>
#define N 310
#define M 14010
using namespace std;
int to[M<<1],bro[M<<1],val[M<<1],head[N],etop=0,
	lblue[N],lpur[N],lst[N],que[N*N],qhead,qtail,dis[N];
bool start[N],inq[N];//true:blue false:purple
inline bool curcolor(int x,int t){
	if(t<lst[x]){
		return start[x];
	}
	int tmp=(t-lst[x])%(lblue[x]+lpur[x]);
	if(start[x]){
		return tmp>=lpur[x];
	}else{
		return tmp<lblue[x];
	}
}
inline int changetime(int x,int t){
	if(t<lst[x]){
		return lst[x];
	}
	int tmp=t-(t-lst[x])%(lblue[x]+lpur[x]);
	if(start[x]){
		if(t-tmp>=lpur[x]){
			return tmp+lpur[x]+lblue[x];
		}else{
			return tmp+lpur[x];
		}
	}else{
		if(t-tmp<lblue[x]){
			return tmp+lblue[x];
		}else{
			return tmp+lblue[x]+lpur[x];
		}
	}
}
inline int cal(int u,int v,int t){//returns the first time(>=t) when u and v has the same color
	if(curcolor(u,t)==curcolor(v,t)){
		return t;
	}
	t=min(changetime(u,t),changetime(v,t));
	if(curcolor(u,t)==curcolor(v,t)){
		return t;
	}
	t=min(changetime(u,t),changetime(v,t));
	if(curcolor(u,t)==curcolor(v,t)){
		return t;
	}
	t=min(changetime(u,t),changetime(v,t));
	if(curcolor(u,t)==curcolor(v,t)){
		return t;
	}
	return -1;
}
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
int main(){
	freopen("1420.in","r",stdin);
	freopen("1420.out","w",stdout);
	memset(head,-1,sizeof(head));
	memset(inq,0,sizeof(inq));
	memset(dis,-1,sizeof(dis));
	int n,m,st,dest,u,v,w,x,tmp;
	char col;
	scanf("%d%d%d%d",&st,&dest,&n,&m);
	for(int i=1;i<=n;i++){
		cin>>col;
		scanf("%d%d%d",lst+i,lblue+i,lpur+i);
		start[i]=(col=='B');
	}
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	qhead=qtail=0;
	que[qtail++]=st;
	inq[st]=true;
	dis[st]=0;
	while(qhead!=qtail){
		x=que[qhead++];
//		cout<<"dis["<<x<<"]="<<dis[x]<<endl;
		inq[st]=false;
		for(int i=head[x];~i;i=bro[i]){
			tmp=cal(x,to[i],dis[x]);
//			cout<<"At "<<x<<" to "<<to[i]<<"\twait from "<<dis[x]<<" to "<<tmp<<endl;
			if(tmp!=-1&&(dis[to[i]]==-1||dis[to[i]]>tmp+val[i])){
				dis[to[i]]=tmp+val[i];
//				cout<<"\tDIS["<<to[i]<<"]="<<dis[to[i]]<<endl;
				if(!inq[to[i]]){
					inq[to[i]]=true;
					que[qtail++]=to[i];
				}
			}
		}
	}
	if(dis[dest]==-1){
		printf("0");
	}else{
		printf("%d",dis[dest]);
	}
//	printf("\n%dms",clock());
}
