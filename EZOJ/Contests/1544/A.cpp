#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef vector<int>vi;
typedef unsigned int uint;
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
const static int n=16,sn=(1<<n)-1;
vi encode(vi _arr,int){
	vi ans;
	uint arr[n];
	for(int i=0;i<(n>>1);i++){
		arr[i<<1]=uint(_arr[i])>>n;
		arr[(i<<1)|1]=uint(_arr[i])&sn;
	}
	for(int i=0;i<n;i++){
		arr[i]=(arr[i]<<n)|(1u<<i);
	}
	for(int tot=1000;tot--;){
		uint cur=0;
		for(int i=0;i<n;i++){
			if(rand()&1){
				cur^=arr[i];
			}
		}
		ans.push_back(cur);
	}
	return ans;
}
vi decode(int(*const arr)(int),int tot,int lim){
	uint lb[n];
	mset(lb,0,n);
	int rnk=0;
	for(int tt=0;tt<lim;tt++){
		uint x=arr(rand()%tot);
		for(int i=0;i<n;i++){
			if(((x>>i)&1)==0)continue;
			if(lb[i]){
				x^=lb[i];
			}else{
				lb[i]=x;
				++rnk;
				break;
			}
		}
		if(rnk==n){
			vi ans;
			for(int i=n-1;i>=0;i--){
				for(int j=i-1;j>=0;j--){
					if((lb[j]>>i)&1){
						lb[j]^=lb[i];
					}
				}
			}
			for(int i=0;i<n;i++){
				lb[i]>>=n;
			}
			for(int i=0;i<(n>>1);i++){
				ans.push_back((lb[i<<1]<<n)|lb[(i<<1)|1]);
			}
			return ans;
		}
	}
	return vi(n>>1);
}
