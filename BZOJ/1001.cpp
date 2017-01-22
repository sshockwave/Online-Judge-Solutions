#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define R 1010
#define C 1010
#define E (R*C*3)
#define V (E-R*C+2)
using namespace std;
int to[E],val[E],bro[E],head[V],etop=0,ntop=0,ld[R][C],ur[R][C],que[V],qhead=0,qtail=0,dis[V];
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
inline int new_node(){
	return ntop++;
}
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
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
	memset(head,-1,sizeof(head));
	for(int i=1;i<=r;i++){
		for(int j=1;j<c;j++){
			add_edge(ld[i-1][j],ur[i][j],nextInt());
		}
	}
	for(int i=1;i<r;i++){
		for(int j=1;j<=c;j++){
			add_edge(ur[i][j-1],ld[i][j],nextInt());
		}
	}
	for(int i=1;i<r;i++){
		for(int j=1;j<c;j++){
			add_edge(ld[i][j],ur[i][j],nextInt());
		}
	}
	memset(inque,0,sizeof(inque));
	memset(dis,127,sizeof(dis));
	que[qtail++]=s;
	inque[s]=true;
	dis[s]=0;
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
	printf("%d",dis[t]);
}
