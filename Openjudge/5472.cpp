#include <iostream>
#include <cstdio>
#include <cstring>
#define N 20010
using namespace std;
int num[N],ans,a[N],b[N];
void merge(int l,int r){
	if(l==r){
		return;
	}
	int mid=l+r>>1,pa=0,pb=0,p=l;
	merge(l,mid);
	merge(mid+1,r);
	for(int i=l;i<=mid;i++){
		a[i-l]=num[i];
	}
	for(int i=mid+1;i<=r;i++){
		b[i-mid-1]=num[i];
	}
	for(;pa<=mid-l&&pb<=r-mid-1;p++){
		if(a[pa]<=b[pb]){
			num[p]=a[pa++];
		}else{
			num[p]=b[pb++];
			ans+=mid-l+1-pa;
		}
	}
	if(pa<=mid-l){
		for(;pa<=mid-l;p++,pa++){
			num[p]=a[pa];
		}
	}else{
		for(;pb<=r-mid-1;p++,pb++){
			num[p]=b[pb];
		}
	}
}
int main(){
	int n;
	while(cin>>n,n){
		for(int i=0;i<n;i++){
			scanf("%d",num+i);
		}
		ans=0;
		merge(0,n-1);
		printf("%d\n",ans);
	}
}
