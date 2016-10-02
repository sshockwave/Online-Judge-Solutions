#include <iostream>
#include <cstdio>
#include <cstring>
#define K 60
using namespace std;
int avail[K],lpos[K],total[K];
int main(){
	int n,k,p,color,price,lvalid=0,cnt=0;
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&color,&price);
		if(price<=p){
			lvalid=i;
		}
		if(lvalid>=lpos[color]){
			avail[color]=total[color];
		}
		cnt+=avail[color];
		total[color]++;
		lpos[color]=i;
	}
	cout<<cnt;
}
