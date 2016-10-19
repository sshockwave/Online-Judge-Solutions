#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
inline int abs(int &a){
	return max(a,-a);
}
int main(){
	freopen("1437.in","r",stdin);
	freopen("1437.out","w",stdout);
	int t,a,b,tx,ty,cntx,cnty,pos;
	for(scanf("%d",&t);t--;){
		scanf("%d%d%d%d",&a,&b,&tx,&ty);
		cntx=cnty=0;
		for(int i=0;i<tx;i++){
			scanf("%d",&pos);
			if(abs(pos)<=b){
				cntx++;
			}
		}
		for(int j=0;j<ty;j++){
			scanf("%d",&pos);
			if(abs(pos)<=b){
				cnty++;
			}
		}
		if(cntx>0&&cnty>0){
			printf("%d\n",(tx+1)*(ty+1)-(cntx-1)*(cnty-1));
		}else{
			printf("%d\n",(tx+1)*(ty+1)+max(0,cntx-1)+max(0,cnty-1));
		}
	}
}
