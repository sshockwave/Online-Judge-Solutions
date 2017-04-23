#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=19,E=N*N*2,INF=0x7f7f7f7f,NODE=500000;//debug
int to[E],bro[E],val[E],head[N];
inline void add_edge(int u,int v,int w){
	static int etop=0;
	to[etop]=v;
	bro[etop]=head[u];
	val[etop]=w;
	head[u]=etop++;
}
int dis[N][N];
struct Node{
	int state,u,v,disu,disv,cnt,pre;
}pool[NODE];
int n,mx,ptop;
struct qNode{
	int id;
	inline friend bool operator < (const qNode &a,const qNode &b){
		return pool[a.id].cnt<pool[b.id].cnt;
	}
};
priority_queue<qNode>q;
inline void pushq(int state,int u,int v,int disu,int disv,int pre){
	if(disu>mx||disv>mx){
		return;
	}
	int cnt=0;
	for(int i=0;i<n;i++){
		if((state>>i)&1){
			cnt++;
		}else{
			int x=i+1;
			if(disu+dis[u][x]>mx&&disv+dis[v][x]>mx){
				return;
			}
		}
	}
//	assert(ptop<NODE);
	if(ptop==NODE){
		return;
	}
	pool[ptop]=(Node){state,u,v,disu,disv,cnt,pre};
	q.push((qNode){ptop++});
}
inline bool check(){
	while(!q.empty()){
		q.pop();
	}
	ptop=0;
	pushq(1,1,1,0,0,-1);
	while(!q.empty()){
		int id=q.top().id;
		Node &x=pool[id];
		if(x.cnt==n){
			return true;
		}
		q.pop();
		for(int i=head[x.u];~i;i=bro[i]){
			pushq(x.state|(1<<(to[i]-1)),to[i],x.v,x.disu+val[i],x.disv,id);
		}
		for(int i=head[x.v];~i;i=bro[i]){
			pushq(x.state|(1<<(to[i]-1)),x.u,to[i],x.disu,x.disv+val[i],id);
		}
	}
	return false;
}
int route[NODE];
int main(){
	n=ni;
	if(n==1){
		puts("0");
		puts("0 1");
		puts("0 1");
		return 0;
	}
	int tot=ni,l=0,r=0,mid;
	memset(dis,127,sizeof(dis));
	memset(head,-1,sizeof(head));
	while(tot--){
		int u=ni,v=ni,w=ni;
		add_edge(u,v,w);
		add_edge(v,u,w);
		dis[u][v]=w;
		dis[v][u]=w;
		r+=w;
	}
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(dis[i][k]!=INF){
				for(int j=1;j<=n;j++){
					if(dis[k][j]!=INF){
						apmin(dis[i][j],dis[i][k]+dis[k][j]);
					}
				}
			}
		}
	}
	r*=n;
	while(l<r){
		mx=(l+r)>>1;
		if(check()){
			r=mx;
		}else{
			l=mx+1;
		}
	}
	printf("%d\n",mx=l);
	check();
	int rtop=0,ucnt=0,vcnt=0,lastu=0,lastv=0;
	assert(pool[q.top().id].cnt==n);
	for(int i=q.top().id;~i;i=pool[i].pre){
		route[++rtop]=i;
		if(pool[i].u!=lastu){
			ucnt++;
			lastu=pool[i].u;
		}
		if(pool[i].v!=lastv){
			vcnt++;
			lastv=pool[i].v;
		}
	}
	printf("%d",ucnt-1);
	lastu=0;
	for(int i=rtop,cur;i;i--){
		cur=pool[route[i]].u;
		if(lastu!=cur){
			printf(" %d",lastu=cur);
		}
	}
	putchar('\n');
	printf("%d",vcnt-1);
	lastv=0;
	for(int i=rtop,cur;i;i--){
		cur=pool[route[i]].v;
		if(lastv!=cur){
			printf(" %d",lastv=cur);
		}
	}
	putchar('\n');
}
