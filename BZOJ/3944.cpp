#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <cassert>
#define N 5000000
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int mu[N],prime[N],ptop=0;
map<int,int>pm;
map<int,long long>pp;
long long phi[N];
bool np[N];
int prem(int n){
	if(n<N){
		return mu[n];
	}
	map<int,int>::iterator it=pm.find(n);
	if(it!=pm.end()){
		return it->second;
	}
	int ret=1,l,r;
	for(unsigned int i=2;i<=n;i++){
		l=i,r=n/(n/l);
		ret-=prem(n/i)*(r-l+1);
		i=r;
	}
	return pm[n]=ret;
}
long long prep(long long n){
	if(n<N){
		return phi[n];
	}
	map<int,long long>::iterator it=pp.find(n);
	if(it!=pp.end()){
		return it->second;
	}
	long long ret=n*(n+1)/2;
	int l,r;
	for(unsigned int i=2;i<=n;i++){
		l=i,r=n/(n/l);
		ret-=prep(n/i)*(r-l+1);
		i=r;
	}
	return pp[n]=ret;
}
int main(){
	phi[1]=mu[1]=1;
	memset(np,0,sizeof(np));
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=0;j<ptop&&i*prime[j]<N;j++){
			np[i*prime[j]]=true;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}else{
				mu[i*prime[j]]=-mu[i];
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
			}
		}
		phi[i]+=phi[i-1];
		mu[i]+=mu[i-1];
	}
	for(int tot=ni(),n;tot--;){
		n=ni();
		printf("%lld %d\n",prep(n),prem(n));
	}
}
