#include <iostream>
#include <cstdio>
#include <cstring>
#define N 110
using namespace std;
int h[N],b[N];
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
int main(){
	int k,n,ans,btop,l,r,mid;
	for(scanf("%d",&k);k--;){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",h+i);
		}
		ans=0;
		for(int i=0;i<n;i++){
			//go right
			btop=0;
			memset(b,0,sizeof(b));
			for(int j=i;j<n;j++){
				l=0,r=btop;
				while(l<r){
					mid=(l+r>>1)+1;
					if(b[mid]>h[j]){
						l=mid;
					}else{
						r=mid-1;
					}
				}
				l++;
				if(l>btop){
					btop++;
				}
				apmax(b[l],h[j]);
			}
			apmax(ans,btop);
			//go left
			btop=0;
			memset(b,0,sizeof(b));
			for(int j=i;j>=0;j--){
				l=0,r=btop;
				while(l<r){
					mid=(l+r>>1)+1;
					if(b[mid]>h[j]){
						l=mid;
					}else{
						r=mid-1;
					}
				}
				l++;
				if(l>btop){
					btop++;
				}
				apmax(b[l],h[j]);
			}
			apmax(ans,btop);
		}
		printf("%d\n",ans);
	}
}
