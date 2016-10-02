#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1000010
using namespace std;
int rest[N],l[N*3],r[N*3],mid[N*3],lson[N*3],rson[N*3],val[N*3],delta[N*3],ntop=1;
void build(int &x,int left,int right){
	x=ntop++;
	l[x]=left,r[x]=right,mid[x]=(l[x]+r[x])>>1;
	delta[x]=0;
	if(l[x]==r[x]){
		val[x]=rest[l[x]];
	}else{
		build(lson[x],l[x],mid[x]);
		build(rson[x],mid[x]+1,r[x]);
		val[x]=min(val[l[x]],val[r[x]]);
	}
}
void update(int x,int a,int b,int v){
	if(l[x]==r[x]){
		val[x]+=v;
		return;
	}
	if(delta[x]){
		delta[l[x]]+=delta[x],val[l[x]]+=delta[x];
		delta[r[x]]+=delta[x],val[r[x]]+=delta[x];
		delta[x]=0;
	}
	if(l[x]==a&&r[x]==b){
		val[x]+=v;
		delta[x]+=v;
	}else{
		if(a>mid[x]){
			update(rson[x],a,b,v);
		}else if(b<=mid[x]){
			update(lson[x],a,b,v);
		}else{
			update(lson[x],a,mid[x],v);
			update(rson[x],mid[x]+1,b,v);
		}
		val[x]=min(val[l[x]],val[r[x]]);
	}
}
int main(){
	int n,m,root,d,s,t;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",rest+i);
	}
	build(root,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&d,&s,&t);
		update(root,s,t,-d);
		if(val[root]<0){
			cout<<-1<<endl<<i;
			return 0;
		}
	}
	cout<<0;
}
