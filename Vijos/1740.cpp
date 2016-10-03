#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
using namespace std;
int w[N],v[N],lend[N],rend[N],num[N],n,m;
long long sum[N];
inline long long cal(int x){
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		num[i]=num[i-1];
		if(w[i]>=x){
			sum[i]+=v[i];
			num[i]++;
		}
	}
	long long cur=0;
	for(int i=1;i<=m;i++){
		cur+=(sum[rend[i]]-sum[lend[i]-1])*(num[rend[i]]-num[lend[i]-1]);
	}
	return cur;//Forgot to return cur
}
inline long long absl(long long a){
	return a>0?a:-a;
}
inline long long minl(long long a,long long b){
	return a<b?a:b;
}
int main(){
	long long s,l=2147483647,r=0,mid;
	scanf("%d%d",&n,&m);
	cin>>s;
	for(int i=1;i<=n;i++){
		scanf("%d%d",w+i,v+i);
		if(w[i]>r){
			r=w[i];
		}
		if(w[i]<l){
			l=w[i];
		}
	}
	l--,r++;
	for(int i=1;i<=m;i++){
		scanf("%d%d",lend+i,rend+i);
	}
	sum[0]=num[0]=0;
	while(l+1<r){
		cout<<"("<<l<<","<<r<<")"<<endl;
		mid=(l+r)>>1;
		if(cal(mid)>s){
			l=mid;
		}else{
			r=mid;
		}
	}
	cout<<min(absl(cal(l)-s),absl(cal(r)-s));
}
