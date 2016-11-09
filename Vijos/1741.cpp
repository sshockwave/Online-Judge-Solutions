#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1010
#define M 10010
using namespace std;
long long ans=0;
struct route{
	int dis,amt;
}r[N];
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
bool operator < (route a,route b){
	return a.amt<b.amt;
}
int d[N],depart[N],arr[N],a[M],b[M],t[M];
int main(){
	int n,m,k,minus;
	memset(depart,0,sizeof(depart));
	memset(r,0,sizeof(r));
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<n;i++){
		scanf("%d",d+i);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",t+i,a+i,b+i);
		r[a[i]].amt++,r[b[i]].amt--;
		apmax(depart[a[i]],t[i]);
	}
	arr[1]=0;
	for(int i=1;i<n;i++){
		arr[i+1]=max(arr[i],depart[i])+d[i];
	}
	for(int i=1;i<=m;i++){
		ans+=arr[b[i]]-t[i];
	}
	r[0].amt=0;
	for(int i=1;i<n;i++){
		r[i].amt+=r[i-1].amt;
	}
	sort(r+1,r+n);
	for(int i=n-1;i>0&&k>0;i--){
		minus=min(d[i],k);
		ans-=minus*r[i].amt;
		k-=minus;
	}
	cout<<ans;
}
