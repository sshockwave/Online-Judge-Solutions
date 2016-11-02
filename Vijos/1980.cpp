#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 2147483647
using namespace std;
int card[14],f[14][14][14][14],ans;
inline int apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline bool invalid(int x){
	return a<0||a>13;
}
void getf(int a,int b,int c,int d){
	int cnt=0;
	for(;d>0&&b>1;d--,b-=2,ans++);
	for(;d>0&&a>1;d--,a-=2,ans++);
	for(;d>0&&b>0;d--,b--,ans++);
	for(;c>0&&b>0;c--,b--,ans++);
	for(;c>0&&a>0;c--,a--,ans++);
	apmin(ans,cnt+a+b+c+d);
}
int main(){
	memset(f,-1,sizeof(f));
	int tot,n,a,b;
	for(scanf("%d%d",&tot,&n);tot--;){
		memset(card,0,sizeof(card));
		ans=INF;
		for(int i=0;i<n;i++){
			scanf("%d%d",&a,&b);
			if(a==1){
				a=13;
			}else{
				a--;
			}
			card[a]++;
		}
		
	}
}
