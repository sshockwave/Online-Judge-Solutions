#include <iostream>
#include <cstdio>
#include <cstring>
#define N 41000
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
int mu[N],prime[N],ptop=0;
bool np[N];
inline long long cal(long long n){
	long long sum=0;
	for(long long i=1;i*i<=n;i++){
		sum+=mu[i]*n/(i*i);
	}
	return sum;
}
inline long long solve(long long x){
	long long l=1,r=1700000000ll,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(cal(mid)<x){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
int main(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
		}
		for(int j=0;j<ptop&&i*prime[j]<N;j++){
			np[i*prime[j]]=true;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}else{
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
	for(int tot=next_int();tot--;){
		printf("%d\n",solve(next_int()));
	}
}
