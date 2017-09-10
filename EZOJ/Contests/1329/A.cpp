#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1000010;
lint A[N],B[N];
int phi[N],prime[N],ps=0;
bool np[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	memset(B,0,sizeof(B));
	phi[1]=1,A[1]=1,B[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
		}
		A[i]=(lint)i*phi[i]/2;
		for(int j=i;j<N;j+=i){
			B[j]+=A[i];
		}
		(++B[i])*=i;
		for(int j=0,p=2;j<ps&&i*p<N;p=prime[++j]){
			np[i*p]=true;
			if(i%p==0){
				phi[i*p]=phi[i]*p;
				break;
			}else{
				phi[i*p]=phi[i]*phi[p];
			}
		}
	}
}
int main(){
	sieve();
	for(int tot=ni;tot--;){
		printf("%lld\n",B[ni]);
	}
}
