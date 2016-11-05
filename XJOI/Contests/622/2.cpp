#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
#define INF 2147483647
using namespace std;
int north[N],south[N],npos[N],len[N],ltop=0;
int main(){
	int n,l,r,mid,height;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",north+i);
		npos[north[i]]=i;
	}
	memset(len,0,sizeof(len));
	len[0]=INF;
	for(int i=1;i<=n;i++){
		scanf("%d",south+i);
		height=npos[south[i]];
		l=0,r=ltop;
		while(l<r){
			mid=(l+r>>1)+1;
			if(len[mid]<height){
				r=mid-1;
			}else{
				l=mid;
			}
		}
		l++;
		if(l>ltop){
			ltop++;
		}
		if(len[l]<height){
			len[l]=height;
		}
	}
	printf("%d",ltop);
}
