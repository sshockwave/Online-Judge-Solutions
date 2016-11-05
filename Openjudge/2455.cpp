#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 200010
#define INF 2147483647
using namespace std;
int s[N],d[N],e[N],n;
inline int getsum(int t){
	int cnt=0;
	for(int i=0;i<n;i++){
		if(t>=s[i]){
			if(t<=e[i]){
				cnt+=(t-s[i])/d[i]+1;
			}else{
				cnt+=(e[i]-s[i])/d[i]+1;
			}
		}
	}
	return cnt;
}
int main(){
	int tot;
	for(scanf("%d",&tot);tot--;){
		int cnt=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d%d",s+i,e+i,d+i);
			cnt+=(e[i]-s[i])/d[i]+1;
		}
		if((cnt&1)==0){
			printf("Poor QIN Teng:(\n");
			continue;
		}
		int l=0,r=INF,mid;
		while(l<r){
			mid=(r-l>>1)+l;
			if(getsum(mid)&1){
				r=mid;
			}else{
				l=mid+1;
			}
		}
		
		printf("%d %d\n",l,getsum(l)-getsum(l-1));
	}
}
