#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define M 100010
using namespace std;
struct interval{
	int l,r;
}area[M];
bool icmp(interval a,interval b){
	return a.l<b.l;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",&area[i].l,&area[i].r);
	}
	sort(area,area+m,icmp);
	int reach=0,least=n,ans=area[0].l-1;
	for(int i=0;i<m;i++){
		if(area[i].l>least){
			ans+=1+max(0,area[i].l-reach-1);
			least=area[i].r;
		}else{
			least=min(least,area[i].r);
		}
		reach=max(reach,area[i].r);
	}
	ans+=n-reach+1;
	cout<<ans;
	return 0;
}
