#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=10000010;
int prime[N],ptop=0,mu[N],lambda[N],_lambda[N];
bool np[N];
int main(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	lambda[1]=_lambda[0]=_lambda[1]=0;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
			lambda[i]=1;
		}
		for(int j=0;j<ptop&&i*prime[j]<N;j++){
			np[i*prime[j]]=true;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				if((i/prime[j])%prime[j]==0){
					lambda[i*prime[j]]=0;
				}else{
					lambda[i*prime[j]]=mu[i];
				}
				break;
			}else{
				mu[i*prime[j]]=-mu[i];
				lambda[i*prime[j]]=mu[i]-lambda[i];
			}
		}
		_lambda[i]=_lambda[i-1]+lambda[i];
	}
	for(int tot=ni();tot--;){
		int n=ni(),m=ni();
		long long ans=0;
		for(int l=1,r,top=min(m,n);l<=top;l=r+1){
			r=min(top,min(n/(n/l),m/(m/l)));
			ans+=(long long)(n/l)*(m/l)*(_lambda[r]-_lambda[l-1]);
		}
		printf("%lld\n",ans);
	}
}
