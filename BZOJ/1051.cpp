#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 10010
#define E 50010
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int to[E],bro[E],head[N],etop=0,dfn[N],low[N],dtop=1,stk[N],stop=0,bln[N],outd[N],ring[N];
inline void add_edge(int u,int v){//u<=v
	to[etop]=u;
	bro[etop]=head[v];
	head[v]=etop++;
}
int tarjan(int x){
	low[x]=dfn[x]=dtop++;
	stk[stop++]=x;
	for(int i=head[x],v;~i;i=bro[i]){
		v=to[i];
		apmin(low[x],dfn[v]?low[v]:tarjan(v));
	}
	if(low[x]==dfn[x]){
		do{
			bln[stk[--stop]]=x;
			ring[x]++;
		}while(stk[stop]!=x);
	}
	return low[x];
}
int main(){
	int n=ni(),tot=ni(),cnt=0,last;
	memset(head,-1,sizeof(head));
	while(tot--){
		add_edge(ni(),ni());
	}
	memset(dfn,0,sizeof(dfn));
	memset(ring,0,sizeof(ring));
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int x=1;x<=n;x++){
		for(int i=head[x];~i;i=bro[i]){
			if(bln[to[i]]!=bln[x]){
				outd[bln[x]]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(outd[i]==0){
			cnt++;
			last=ring[i];
		}
	}
	printf("%d",cnt==1?last:0);
}
