#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define V 1010
#define E 2010
using namespace std;
int to[E*2],val[E*2],bro[E*2],head[V],etop=0,que[V],qhead=0,qtail=0,dis[V];
bool inque[V];
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
int main(){
	memset(head,-1,sizeof(head));
	int e=nextInt(),v=nextInt(),a,b,c;
	while(e--){
		a=nextInt(),b=nextInt(),c=nextInt();
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	memset(inque,0,sizeof(inque));
	memset(dis,127,sizeof(dis));
	dis[v]=0;
	que[qtail++]=v;
	inque[v]=true;
	while(qhead!=qtail){
		int x=que[qhead++];
		if(qhead==V){
			qhead=0;
		}
		for(int i=head[x];~i;i=bro[i]){
			if(dis[to[i]]>dis[x]+val[i]){
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
	printf("%d",dis[1]);
}
