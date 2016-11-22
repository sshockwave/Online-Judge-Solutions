#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
using namespace std;
long long a[N],b[N],c[N],digit[20];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		for(int j=0,t=a[i];t;j++,t>>=1){
			if(t&1){
				digit[j]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		b[i]=c[i]=0;
		for(int j=0;j<19;j++){
			if((a[i]>>j)&1){
				b[i]+=(digit[j]<<j);
				c[i]+=(n<<j);
			}else{
				c[i]+=(digit[j]<<j);
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",b[i]);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%d ",c[i]);
	}
}
