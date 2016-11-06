#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
using namespace std;
int h[N];
int main(){
	int n,cnt=1;
	bool d;//true:up false:down
	scanf("%d",&n);
	if(n==1){
		printf("1");
		return 0;
	}
	for(int i=0;i<n;i++){
		scanf("%d",h+i);
	}
	d=h[1]<h[0];
	for(int i=0;i<n-1;i++){
		if(h[i+1]!=h[i]&&(h[i+1]>h[i])!=d){
			cnt++;
			d=h[i+1]>h[i];
		}
	}
	printf("%d",cnt);
}
