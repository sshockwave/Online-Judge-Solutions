#include <cstdio>
#define N 100010
using namespace std;
int fa[N],rank[N];
bool weak[N];
int findroot(int x){
	if(fa[x]==0){
		return x;
	}
	return fa[x]=findroot(fa[x]);
}
inline void uni(int x,int y){
	x=findroot(x),y=findroot(y);
	if(x==y){
		return;
	}
	if(rank[x]<rank[y]){
		int t=x;
		x=y;
		y=t;
	}
	fa[y]=x;
	if(weak[y]){
		weak[x]=true;
	}
	if(rank[x]==rank[y]){
		rank[x]++;
	}
}
int main(){
	int n,m,x,y,z,w,cnt=0;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d%d%d",&x,&y,&z,&w);
		if(z==w){
			uni(x,y);
		}else{
			weak[findroot(y)]=true;
		}
	}
	for(int i=1;i<=n;i++){
		if(!weak[findroot(i)]){
			cnt++;
		}
	}
	printf("%d",cnt);
}
