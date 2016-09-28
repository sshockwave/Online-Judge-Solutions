#include <iostream>
#include <cstdio>
#include <cstring>
#define N 20010
#define INF 2147483647
using namespace std;
int ntop,to[N<<1],bro[N<<1],head[N],fa[N],bal[N],size[N],p,n;
inline void add_edge(int u,int v){
	to[ntop]=v;
	bro[ntop]=head[u];
	head[u]=ntop++;
}
inline void apmax(int &a,int b){
	if(b>a){
		a=b;
	}
}
void dfs(int x){
	size[x]=1;
	for(int i=head[x];i;i=bro[i]){
		if(to[i]!=fa[x]){
			fa[to[i]]=x;
			dfs(to[i]);
			size[x]+=size[to[i]];
			apmax(bal[x],size[to[i]]);
		}
	}
	apmax(bal[x],n-size[x]);
	if(bal[x]<bal[p]){
		p=x;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tot,a,b;
	for(cin>>tot;tot--;){
		p=0;
		ntop=1;
		memset(head,0,sizeof(head));
		memset(fa,0,sizeof(fa));
		memset(bal,-1,sizeof(bal));
		bal[p]=INF;
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>a>>b;
			add_edge(a,b);
			add_edge(b,a);
		}
		dfs(1);
		cout<<p<<" "<<bal[p]<<endl;
	}
}
