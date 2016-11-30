#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 25
#define INF 2147483647
using namespace std;
int n,ans=INF,pre[M],m,sqrt[N];
void dfs(int layer,int rest,int r,int h,int sum){
	if(sum>ans){
		return;
	}
	if(layer<0){
		if(rest==0){
			ans=sum;
		}
		return;
	}
	if(rest<pre[layer]){
		return;
	}
	for(r=min(sqrt[rest-pre[layer]],r-1);r>layer;r--){
		for(int j=min((rest-pre[layer])/r,h-1);j>layer;j--){
			dfs(layer-1,rest-r*r*j,r,j,sum+2*r*j+(layer==m-1?r*r:0));
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	pre[0]=0;
	for(int i=1;i<=m;i++){
		pre[i]=pre[i-1]+i*i*i;
	}
	for(int i=1,j=0;j<=n;j++){
		if(j>=i*i){
			i++;
		}
		sqrt[j]=i-1;
	}
	dfs(m-1,n,INF,INF,0);
	if(ans==INF){
		ans=0;
	}
	printf("%d",ans);
}
