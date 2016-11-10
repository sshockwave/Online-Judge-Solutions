#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1010
#define M 10010
using namespace std;
int num[N],a[M],b[M],t[M],arr[N],last[N],d[N],off[N],n;
inline int apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void getarr(int i){
	for(;i<=n;i++){
		arr[i]=max(arr[i-1],last[i-1])+d[i-1];
	}
}
inline void getnum(int x){
	for(int i=n-1;i>=x;i--){
		num[i]=off[i+1];
		if(arr[i+1]>last[i]){
			num[i]+=num[i+1];
		}
	}
}
int main(){
	int m,k,x;
	long long ans=0;
	memset(last,0,sizeof(last));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<n;i++){
		scanf("%d",d+i);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",a+i,b+i,t+i);
		apmax(last[i],t[i]);
		off[b[i]]++;
	}
	arr[0]=d[0]=num[0]=last[0]=0;
	getarr(1);
	getnum(1);
	for(int i=1;i<=m;i++){
		ans+=arr[b[i]]-t[i];
	}
	while(k--){
		x=0;
		for(int i=1;i<=n;i++){
			if(num[i]>num[x]&&d[i]){
				x=i;
			}
		}
		d[x]--;
		ans-=num[x];
		getarr(x+1);
		getnum(x);
	}
	printf("%I64d",ans);
}
