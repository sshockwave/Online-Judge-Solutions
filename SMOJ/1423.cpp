#include <iostream>
#include <cstdio>
#include <cstring>
#define D 1010
using namespace std;
int lo[D],hi[D],root;
int main(){
	freopen("1423.in","r",stdin);
	freopen("1423.out","w",stdout);
	int tot,n,m,d;
	for(scanf("%d",&tot);tot--;){
		scanf("%d%d%d",&n,&m,&d);
		for(int i=1;i<=d;i++){
			scanf("%d-%d",lo+i,hi+i);
		}
		for(int i=d;i>0;i--){
			if(lo[i]<=m){
				m+=hi[i]-lo[i]+1;
			}
		}
		if(m>n){
			m=-1;
		}
		printf("%d\n",m);
	}
//	printf("\n%dms",clock());
}
