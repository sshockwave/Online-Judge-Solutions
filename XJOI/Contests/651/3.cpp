#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
using namespace std;
int ripe[N],cur[N],day[N];
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int main(){
	memset(day,127,sizeof(day));
	memset(cur,0,sizeof(cur));
	int n,m,l,r,c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l,&r,&c);
		if(l<=r){
			for(int j=l;j<=r;j++){
				cur[j]+=
			}
		}else{
			
		}
	}
}
