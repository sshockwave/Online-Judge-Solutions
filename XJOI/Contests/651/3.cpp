#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
#define INF 2147483647
using namespace std;
int val[N*3],lend[N*3],rend[N*3],mid[N*3],lson[N*3],rson[N*3],delta[N*3],ntop=0,//delta>0
	p[N],ans[N],day;
void build(int x,int l,int r){
	lend[x]=l,rend[x]=r,mid[x]=l+r>>1;
	if(l==r){
		val[x]=p[l];
	}else{
		build(lson[x]=ntop++,l,mid[x]);
		build(rson[x]=ntop++,mid[x]+1,r);
		val[x]=min(val[lson[x]],val[rson[x]]);
	}
}
inline void push_down(int x){
	if(delta[x]){
		if(lend[x]!=rend[x]){
			val[lson[x]]-=delta[x];
			delta[lson[x]]+=delta[x];
			val[rson[x]]-=delta[x];
			delta[rson[x]]+=delta[x];
		}
		delta[x]=0;
	}
}
void getans(int x){
	if(val[x]>0){
		return;
	}
	push_down(x);
	if(lend[x]==rend[x]){
		ans[mid[x]]=day;
		val[x]=INF;
		return;
	}
	while(val[x]<=0){
		getans(lson[x]);
		getans(rson[x]);
		val[x]=min(val[lson[x]],val[rson[x]]);
	}
}
void change(int x,int l,int r,int c){
	if(l==lend[x]&&r==rend[x]){
		val[x]-=c;
		delta[x]+=c;
		getans(x);
		return;
	}
	push_down(x);
	if(l>mid[x]){
		change(rson[x],l,r,c);
	}else if(r<=mid[x]){
		change(lson[x],l,r,c);
	}else{
		change(lson[x],l,mid[x],c);
		change(rson[x],mid[x]+1,r,c);
	}
}
int main(){
	int n,m,l,r,c,q,x;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",p+i);
	}
	build(ntop++,1,n);
	memset(ans,-1,sizeof(ans));
	memset(delta,0,sizeof(delta));
	for(day=1;day<=m;day++){
		scanf("%d%d%d",&l,&r,&c);
		if(l>r){
			change(0,l,n,c);
			change(0,1,r,c);
		}else{
			change(0,l,r,c);
		}
	}
	for(scanf("%d",&q);q--;){
		scanf("%d",&x);
		if(ans[x]==-1){
			printf("So sad\n");
		}else{
			printf("%d\n",ans[x]);
		}
	}
}
