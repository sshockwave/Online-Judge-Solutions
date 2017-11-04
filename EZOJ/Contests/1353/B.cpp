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
const int N=35,P=12,O=1000000007;
int prime[N],mu[N],ps;
bool np[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	ps=0;
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}
			mu[i*cur]=-mu[i];
		}
	}
}
int f[N][1<<P];
inline int Main(){
	int n=ni,k=ni;
	memset(f,0,sizeof(f));
	f[0][0]=1;
	sieve(n);
	for(int i=1;i<=n;i++){
		if(mu[i]){
			int sp=0;
			for(int j=0,cur=2;j<ps&&cur<=i;cur=prime[++j]){
				if(i%cur==0){
					sp|=1<<j;
				}
			}
			for(int j=min(k-1,i);j>=0;j--){
				for(int s=0,ts=1<<ps;s<ts;s++){
					if((s&sp)==0){
						(f[j+1][s|sp]+=f[j][s])%=O;
					}
				}
			}
		}
	}
	lint ans=0;
	for(int j=1;j<=k;j++){
		for(int s=0,ts=1<<ps;s<ts;s++){
			ans+=f[j][s];
		}
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mul.in","r",stdin);
	freopen("mul.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
