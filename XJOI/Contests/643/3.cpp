#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue> 
#define N 1000010
using namespace std;
int n,m,ecnt[N],to[N],bro[N],head[N],etop=0,fa[N];
struct node{
	int x;
	node(int a){
		x=a;
	}
};
bool operator <(node a,node b){
	return ecnt[a.x]>ecnt[b.x];
}
priority_queue<node>q;
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
int main(){
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof(head));
	memset(ecnt,0,sizeof(ecnt));
	fa[1]=0;
	for(int i=2;i<=n;i++){
		scanf("%d",fa+i);
		ecnt[i]++,ecnt[fa[i]]++;
		add_edge(fa[i],i);
	}
	if(m==0){
		q.push(1);
		long long sum=0;
		for(int j=1;j<=n;j++){
			int x=q.top().x;
			q.pop();
			sum+=1ll*j*ecnt[x];
			for(int i=head[x];~i;i=bro[i]){
				q.push(node(to[i]));
			}
		}
		cout<<sum;
		return 0;
	}
	for(int t=1;t<=n;t++){
		memset(ecnt,0,sizeof(ecnt));
		for(;!q.empty();q.pop());
		for(int i=2;i<=t;i++){
			ecnt[i]++,ecnt[fa[i]]++;
		}
		q.push(1);
		long long sum=0;
		for(int j=1;j<=t;j++){
			int x=q.top().x;
			q.pop();
			sum+=1ll*j*ecnt[x];
			for(int i=head[x];~i;i=bro[i]){
				if(to[i]<=t){
					q.push(node(to[i]));
				}
			}
		}
		cout<<sum<<endl;
	}
}
