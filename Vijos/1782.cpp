#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1000010
using namespace std;
int rest[N],diff[N],d[N],s[N],t[N];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",rest+i);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",d+i,s+i,t+i);
	}
	int l=1,r=m,mid,sum;
	bool flag;
	while(l<r){
		mid=(l+r>>1)+1;
		memset(diff,0,sizeof(diff));
		for(int i=1;i<=mid;i++){
			diff[s[i]]+=d[i],diff[t[i]+1]-=d[i];
		}
		flag=true;
		sum=0;
		for(int i=1;i<=n;i++){
			sum+=diff[i];
			if(sum>rest[i]){
				flag=false;
				break;
			}
		}
		if(flag){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	if(l==m){
		cout<<0;
	}else{
		cout<<-1<<endl<<l+1;
	}
}
