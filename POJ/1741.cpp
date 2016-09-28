#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 10010
#define INF 2147483647
using namespace std;
int to[N<<1],bro[N<<1],len[N<<1],head[N],ntop,cnt,
	bal[N],size[N],k,depth[N],fa[N],dtop,g;
bool vis[N];
inline void add_edge(int u,int v,int val){
	to[ntop]=v;
	len[ntop]=val;
	bro[ntop]=head[u];
	head[u]=ntop++;
}
int dfs_depth(int x,int add){
//	cout<<"\t\tGetting:"<<x<<"\tdepth="<<add<<endl;
	depth[dtop++]=add;
	size[x]=1;
	for(int i=head[x];i;i=bro[i]){
		if(!vis[to[i]]&&to[i]!=fa[x]){
			fa[to[i]]=x;
			size[x]+=dfs_depth(to[i],add+len[i]);
		}
	}
	return size[x];
}
void dfs_cent(int x,int sz){
	size[x]=1;
	bal[x]=0;
	for(int i=head[x];i;i=bro[i]){
		if(!vis[to[i]]&&to[i]!=fa[x]){
			fa[to[i]]=x;
			dfs_cent(to[i],sz);
			size[x]+=size[to[i]];
			if(size[to[i]]>bal[x]){
				bal[x]=size[to[i]];
			}
		}
	}
	if(sz-size[x]>bal[x]){
		bal[x]=sz-size[x];
	}
	if(bal[x]<bal[g]){
		g=x;
	}
}
inline int cntpair(int x,int add){
	dtop=0;
	dfs_depth(x,add);
	sort(depth,depth+size[x]);
//	cout<<"\t\t\tSorting:";
//	for(int i=0;i<size[x];i++){
//		cout<<depth[i]<<" ";
//	}
//	cout<<endl;
	int sum=0;
	for(int i=0,j=size[x]-1;i<j;){
		if(depth[i]+depth[j]>k){
			j--;
		}else{
			sum+=j-i;
			i++;
		}
	}
//	cout<<"\t\t\tResult="<<sum<<endl;
	return sum;
}
void solve(int x,int sz){
//	cout<<"SOLVING "<<x<<endl;
	g=0;
	dfs_cent(x,sz);
	x=g;
//	cout<<"\tCenter:"<<x<<endl;
	vis[x]=true;
	fa[x]=x;
	cnt+=cntpair(x,0);
//	cout<<"\t\tTotal count->"<<cnt<<endl;
	for(int i=head[x];i;i=bro[i]){
		if(!vis[to[i]]){
//			cout<<"\t"<<to[i]<<endl;
			fa[to[i]]=x;
			cnt-=cntpair(to[i],len[i]);
//			cout<<"\t\tTotal count->"<<cnt<<endl;
			solve(to[i],size[to[i]]);
		}
	}
//	cout<<"Ended"<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
//	freopen("POJ1741.in","r",stdin);
	int n,a,b,v;
	bal[0]=INF;
	while(cin>>n>>k,n!=0||k!=0){
		cnt=dtop=0;
		ntop=1;
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
		memset(fa,0,sizeof(fa));
		for(int i=1;i<n;i++){
			cin>>a>>b>>v;
			add_edge(a,b,v);
			add_edge(b,a,v);
		}
		solve(1,n);
		cout<<cnt<<endl;
	}
}
