#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
using namespace std;
int a[N],b[N],g[N],k[N];
int main(){
	int n,x,y,id=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",a+i,b+i,g+i,k+i);
	}
	scanf("%d%d",&x,&y);
	for(int i=1;i<=n;i++){
		if(x>=a[i]&&y>=b[i]&&x<=a[i]+g[i]&&y<=b[i]+k[i]){
			id=i;
		}
	}
	cout<<id;
}
