#include <iostream>
#include <cstdio>
#include <cstring>
#define N 2000010
using namespace std;
bool vis[N];
int main(){
	int t,l,r,logt;
	long long ans,cnt;
	for(scanf("%d",&t);t--;){
		scanf("%d%d",&l,&r);
		memset(vis,0,sizeof(vis));
		logt=1;
		for(int tmp=l/10;tmp;logt*=10,tmp/=10);
		ans=0;
		for(int i=l;i<=r;i++){
			if(!vis[i]){
				cnt=1;
				vis[i]=true;
				for(int x=i;x=(x%10*logt+x/10),x!=i;){
					if(l<=x&&x<=r){
						cnt++;
						vis[x]=true;
					}
				}
				ans+=cnt*(cnt-1)/2;
			}
		}
		printf("%d\n",ans);
	}
}
