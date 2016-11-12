#include <iostream>
#include <cstdio>
#include <cstring>
#define N 360
#define C 45
using namespace std;
int a[N],f[C][C][C][C],card[5];
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",a+i);
	}
	memset(f,0,sizeof(f));
	memset(card,0,sizeof(card));
	while(m--){
		int tmp;
		scanf("%d",&tmp);
		card[tmp]++;
	}
	for(int i=0;i<=card[1];i++){
		for(int j=0;j<=card[2];j++){
			for(int k=0;k<=card[3];k++){
				for(int l=0;l<=card[4];l++){
					int &cur=f[i][j][k][l];
					if(i>0){
						apmax(cur,f[i-1][j][k][l]);
					}
					if(j>0){
						apmax(cur,f[i][j-1][k][l]);
					}
					if(k>0){
						apmax(cur,f[i][j][k-1][l]);
					}
					if(l>0){
						apmax(cur,f[i][j][k][l-1]);
					}
					cur+=a[i+j*2+k*3+l*4];
				}
			}
		}
	}
	printf("%d",f[card[1]][card[2]][card[3]][card[4]]);
}
