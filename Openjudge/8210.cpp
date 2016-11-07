#include <iostream>
#include <cstdio>
#include <cstring>
#define N 50010
using namespace std;
int d[N];
int main(){
	int len,n,m;
	scanf("%d%d%d",&len,&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",d+i);
	}
	int l=0,r=len,mid,last,cnt;
	while(l<r){
		mid=(l+r)/2+1;
		last=cnt=0;
		for(int i=1;i<=n;i++){
			if(d[i]-last>=mid){
				cnt++;
				last=d[i];
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
