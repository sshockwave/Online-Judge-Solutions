#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#define N 100010
#define M 7000010
#define NODE 14200039
#define INF 2147483647
using namespace std;
long long u,v;
int val[NODE],lson[NODE],rson[NODE],fa[NODE],etop,root,delta=0;
void build(int &x,int l,int r){
	if(l==r){
		x=l;
		return;
	}
	x=++etop;
	int mid=l+r>>1;
	build(lson[x],l,mid);
	build(rson[x],mid+1,r);
	fa[lson[x]]=fa[rson[x]]=x;
}
inline void update(int x){
	while(x!=root){
		x=fa[x];
		val[x]=max(val[lson[x]],val[rson[x]]);
	}
}
inline bool valcmp(const int &a,const int &b){
	return a>b;
}
int main(){
//	freopen("earthworm3.in","r",stdin);
	freopen("earthworm.in","r",stdin);
	freopen("earthworm.out","w",stdout);
	int n,m,q,t;
	memset(val,128,sizeof(val));
	scanf("%d%d%d%lld%lld%d",&n,&m,&q,&u,&v,&t);
	etop=n+m;
	build(root,1,n+m);
	for(int i=1;i<=n;i++){
		scanf("%d",val+i);
		update(i);
	}
	for(int i=1,x;i<=m;i++){
		x=root;
		while(x>n+m){
			if(val[lson[x]]==val[x]){
				x=lson[x];
			}else{
				x=rson[x];
			}
		}
		val[x]+=delta;
		if(i%t==0){
			printf("%d ",val[x]);
		}
		val[n+i]=val[x]-(u*val[x]/v);
		val[x]=u*val[x]/v;
		delta+=q;
		val[x]-=delta,val[n+i]-=delta;
		update(x),update(n+i);
	}
	printf("\n");
	sort(val+1,val+n+m+1,valcmp);
	for(int i=1,j=(n+m)/t;i<=j;i++){
		printf("%d ",val[i*t]+delta);
	}
	fclose(stdin);
	fclose(stdout);
}
