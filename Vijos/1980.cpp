#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 2147483647
using namespace std;
int card[14],ans,len[4]={0,5,3,2};
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void getf(int cnt){
	int num[5]={0},a,b,c,d;
	for(int i=1;i<=13;i++){
		num[card[i]]++;
	}
	a=num[1],b=num[2],c=num[3],d=num[4];
	for(;d>0&&b>1;d--,b-=2,cnt++);
	for(;d>0&&a>1;d--,a-=2,cnt++);
	for(;d>0&&b>0;d--,b--,cnt++);
	for(;c>0&&b>0;c--,b--,cnt++);
	for(;c>0&&a>0;c--,a--,cnt++);
	apmin(ans,cnt+a+b+c+d);
}
void dfs(int cnt){
	if(cnt>=ans){
		return;
	}
	getf(cnt);
	for(int amt=3;amt>=1;amt--){
		for(int i=2;i+len[amt]-1<=13;i++){
			for(int j=i;j<=13;j++){
				card[j]-=amt;
				if(card[j]<0){
					for(;j>=i;j--){
						card[j]+=amt;
					}
					break;
				}
				if(j>=i+len[amt]-1){
					dfs(cnt+1);
				}
			}
		}
	}
}
int main(){
	int tot,n,a,b;
	for(scanf("%d%d",&tot,&n);tot--;){
		memset(card,0,sizeof(card));
		for(int i=0;i<n;i++){
			scanf("%d%d",&a,&b);
			if(a==1){
				a=13;
			}else if(a){
				a--;
			}
			card[a]++;
		}
		ans=INF;
		dfs(0);
		printf("%d\n",ans+(card[0]>0));
	}
}
