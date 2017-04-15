#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int N=100010,M=500010,E=N*2,MOD=1000000007,INF=2147483647;
int ans=0;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
int m[N];
struct Tree{
	int to[E],bro[E],val[E],head[N],bal[N];
	Tree(){
		memset(head,-1,sizeof(head));
		bal[0]=INF;
	}
	inline void add_edge(int u,int v,int w){
		static int etop=0;
		to[etop]=v;
		bro[etop]=head[u];
		val[etop]=w;
		head[u]=etop++;
	}
	void gcenter(int x,bool reset){
		static int g=0;
		if(reset){
			
		}
	} 
}T;
struct OneNode{
	int **dis,*l,*c;
	inline void init(int m){
		dis=new int[m][m];
		l=new int[m];
		c=new int[m];
		for(int i=1;i<m;i++){
			l[i]=ni();
		}
		for(int i=1;i<m;i++){
			c[i]=ni();
		}
		//floyd
	}
}node[N];
int main(){
	int n=ni();
	for(int i=1;i<n;i++){
		int u=ni(),v=ni(),w=ni();
		T.add_edge(u,v,w);
		T.add_edge(v,u,w);
	}
	for(int i=1;i<=n;i++){
		m[i]=ni();
		node[N].init(m[i]);
	}
	T.solve(1);
	printf("%d\n",ans);
}
