#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#define A 10000010
using namespace std;
int fa[A];
int getroot(int x){
	if(fa[x]==0){
		return x;
	}
	return fa[x]=getroot(fa[x]);
}
int main(){
	memset(fa,0,sizeof(fa));
	int n,a,b,ans=0;
	scanf("%d",&n);
	n<<=1;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		a=getroot(a),b=getroot(b);
		if(a!=b){
			fa[a]=b;
			ans++;
		}
	}
	printf("%d",min(ans,n>>1));
}
