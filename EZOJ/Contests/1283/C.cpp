#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=200010,E=200010;
int bln[N],n,ranc[N];
struct Graph{
	int to[E],bro[E],head[N],etop;
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
};
struct Finder:Graph{
	inline void reset(){
		etop=0;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
	}
	bool vis[N];
	bool find(int x,int t){
		assert(bln[x]==x);
		if(x==t){
			return true;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=x&&find(v,t)){
				return true;
			}
		}
		return false;
	}
}G2;
struct TarjanWorker:Graph{
	int dfn[N],low[N],stk[N];
	bool instk[N];
	inline void reset(){
		etop=0;
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(instk,0,sizeof(instk));
	}
	void tarjan(int x){
		static int stop=0,tim=0;
		dfn[x]=low[x]=++tim;
		stk[stop++]=x;
		instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(dfn[v]){
				if(instk[v]){
					apmin(low[x],dfn[v]);
				}
				//tocheck
			}else{
				tarjan(v);
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--stop];
				instk[v]=false;
				bln[v]=x;
			}while(v!=x);
		}
	}
	inline void addall(int x){
		int b=bln[x];
		for(int i=head[x],v;~i;i=bro[i]){
			v=bln[to[i]];
			if(v!=b){
				G2.add_edge(b,v);
			}
		}
	}
}G;
inline bool twosat(){
	memset(bln,-1,sizeof(bln));
	for(int i=0,_=n<<1;i<_;i++){
		if(bln[i]==-1){
			G.tarjan(i);
		}
	}
	for(int i=0;i<n;i++){
		if(bln[i<<1]==bln[(i<<1)|1]){
			return false;
		}
		G.addall(i<<1);
		G.addall((i<<1)|1);
	}
	return !G2.find(bln[0],bln[1]);
}
int main(){
	for(int tot;scanf("%d%d",&n,&tot)!=EOF;){
		G.reset();
		G2.reset();
		bool a,b;
		for(int x,y;tot--;){
			scanf("%d%d",&x,&y);
			if(x>0){
				a=false;
			}else{
				a=true;
				x=-x;
			}
			if(y>0){
				b=false;
			}else{
				b=true;
				y=-y;
			}
			x=(x-1)<<1,y=(y-1)<<1;
			G.add_edge(x|(!a),y|b);
			G.add_edge(y|(!b),x|a);
		}
		puts(twosat()?"yes":"no");
	}
}
