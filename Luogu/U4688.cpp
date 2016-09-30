#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1010
using namespace std;
int diff[N];
struct rec{
	int x,l,r,op;
}cover[N];
bool recsort(const rec &a,const rec &b){
	return a.x<b.x;
}
int main(){
	memset(diff,0,sizeof(diff));
	int n,m,x1,x2,y1,y2,sum;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		cover[i<<1].x=x1,cover[(i<<1)+1].x=x2+1;
		cover[i<<1].l=cover[(i<<1)+1].l=y1;
		cover[i<<1].r=cover[(i<<1)+1].r=y2;
		cover[i<<1].op=1,cover[(i<<1)+1].op=-1;
	}
	sort(cover,cover+(m<<1),recsort);
	cover[m<<1].x=0;
	for(int i=1,p=0;i<=n;i++){
		for(;cover[p].x==i;p++){
			diff[cover[p].l]+=cover[p].op;
			diff[cover[p].r+1]-=cover[p].op;
		}
		sum=0;
		for(int j=1;j<=n;j++){
			sum+=diff[j];
			printf("%d ",sum);
		}
		printf("\n");
	}
}
