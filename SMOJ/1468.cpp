#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010 
using namespace std;
int val[N*3],pos[N];
void build(int x,int l,int r){
	if(l==r){
		pos[l]=x;
	}else{
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build((x<<1)+1,mid+1,r);
	}
}
inline void update(int x){
	for(;x;x>>=1){
		val[x]=max(val[x<<1],val[(x<<1)+1]);
	}
}
int main(){
	freopen("1468.in","r",stdin);
	freopen("1468.out","w",stdout);
	int n,m,flag,x,y;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		val[pos[i]]=x;
		update(pos[i]>>1);
	}
	while(m--){
		scanf("%d",&flag);
		if(flag==1){
			scanf("%d%d",&x,&y);
			x=pos[x];
			val[x]=y;
			update(x>>1);
		}else{
			printf("%d\n",val[1]);
		}
	}
	return 0;
}
