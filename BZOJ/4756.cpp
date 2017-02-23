#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#define N 100010
#define D (N*18)
#define lson(x) son[x][0]
#define rson(x) son[x][1]
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int to[N],bro[N],val[N],head[N],etop=0,son[D][2],sum[D],ntop=0,rlist[N],rank[N],n,ans[N];
inline void add_edge(int u,int v){
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
inline void push_up(int x){
	sum[x]=0;
	if(~lson(x)){
		sum[x]+=sum[lson(x)];
	}
	if(~rson(x)){
		sum[x]+=sum[rson(x)];
	}
}
void merge(int &u,int v){//u<--v
	if(u==-1){
		u=v;
		return;
	}else if(v==-1){
		return;
	}
	merge(lson(u),lson(v));
	merge(rson(u),rson(v));
	push_up(u);
}
void set(int &x,int l,int r,int val){
	if(x==-1){
		x=ntop++;
	}
	if(l==r){
		sum[x]=1;
		return;
	}
	sum[x]++;
	int mid=(l+r)>>1;
	if(val<=mid){
		set(lson(x),l,mid,val);
	}else{
		set(rson(x),mid+1,r,val);
	}
}
int query(int x,int l,int r,int a,int b){
	if(x==-1){
		return 0;
	}
	if(l==a&&r==b){
		return sum[x];
	}
	int mid=(l+r)>>1;
	if(b<=mid){
		return query(lson(x),l,mid,a,b);
	}else if(a>mid){
		return query(rson(x),mid+1,r,a,b);
	}else{
		return query(lson(x),l,mid,a,mid)+query(rson(x),mid+1,r,mid+1,b);
	}
}
int dfs(int x){
	int root=-1;
	for(int i=head[x];~i;i=bro[i]){
		merge(root,dfs(to[i]));
	}
	ans[x]=query(root,1,n,rank[x],n);
	set(root,1,n,rank[x]);
	return root;
}
bool rlistcmp(int a,int b){
	return val[a]<val[b];
}
int main(){
//	freopen("4756.in","r",stdin);
	memset(head,-1,sizeof(head));
	n=next_int();
	for(int i=1;i<=n;i++){
		val[i]=next_int();
		rlist[i]=i;
	}
	sort(rlist+1,rlist+1+n,rlistcmp);
	rank[rlist[1]]=1;
	for(int i=2;i<=n;i++){
		add_edge(next_int(),i);
		rank[rlist[i]]=i;
	}
	memset(son,-1,sizeof(son));
	dfs(1);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
}
