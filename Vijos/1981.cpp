#include <iostream>
#include <cstdio>
#include <cstring>
#define N 50010
using namespace std;
int dis[N];
int main(){
	int len,m,n;
	scanf("%d%d%d",&len,&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",dis+i);
	}
	int l=0,r=len,mid,last,cnt;
	while(l<r){
		mid=(l+r>>1)+1;
		last=cnt=0;
		for(int i=0;i<n;i++){
			if(dis[i]-last>=mid){
				cnt++;
				last=dis[i];
			}
		}
		if(len-last<mid){
			cnt--;
		}
		if(n-cnt<=m){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	printf("%d",l);
}
