#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int sum[129][129],mat[129][129];
inline int getsum(int x,int y){
	if(x<0||y<0){
		return 0;
	}
	if(x>128){
		x=128;
	}
	if(y>128){
		y=128;
	}
	return sum[x][y];
}
int main(){
	int d,n,x,y,k,maxn=0,cnt=0,cur;
	scanf("%d%d",&d,&n);
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&x,&y,&k);
		mat[x][y]=k;
	}
	for(int i=0;i<=128;i++){
		for(int j=0;j<=128;j++){
			sum[i][j]=mat[i][j]-getsum(i-1,j-1)+getsum(i-1,j)+getsum(i,j-1);
		}
	}
	for(int i=0;i<=128;i++){
		for(int j=0;j<=128;j++){
			cur=getsum(i+d,j+d)-getsum(i-d-1,j+d)-getsum(i+d,j-d-1)+getsum(i-d-1,j-d-1);
			if(cur==maxn){
				cnt++;
			}else if(cur>maxn){
				maxn=cur;
				cnt=1;
			}
		}
	}
	printf("%d %d",cnt,maxn);
}
