#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=510,O=1000000007;
int prime[N],mu[N],bfac[N],sp[N],ps;
bool np[N];
vector<int>vec[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	ps=0;
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
			bfac[i]=i;
		}
		if(mu[i]){
			vec[bfac[i]].push_back(i);
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			bfac[i*cur]=bfac[i];
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}
			mu[i*cur]=-mu[i];
		}
	}
	memset(sp,0,sizeof(sp));
	for(int i=1;i<=n;i++){
		for(int j=0;j<8;j++){
			if(i%prime[j]==0){
				sp[i]|=1<<j;
			}
		}
	}
}
const int SP=1<<8;
int f[N][SP];
inline int Main(){
	int n=ni,k=ni;
	memset(f,0,sizeof(f[0])*(k+1));
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		if(mu[i]&&bfac[i]<22){
			for(int j=k-1;j>=0;j--){
				for(int s=0;s<SP;s++){
					if((s&sp[i])==0){
						(f[j+1][s|sp[i]]+=f[j][s])%=O;
					}
				}
			}
		}
	}
	for(int i=8;prime[i]<=n;i++){
		vector<int>&cur=vec[prime[i]];
		for(int j=k-1;j>=0;j--){
			for(int s=0;s<SP;s++){
				for(vector<int>::iterator it=cur.begin();it!=cur.end()&&*it<=n;it++){
					if((s&sp[*it])==0){
						(f[j+1][s|sp[*it]]+=f[j][s])%=O;
					}
				}
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=k;i++){
		for(int s=0;s<SP;s++){
			ans+=f[i][s];
		}
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mul.in","r",stdin);
	freopen("mul.out","w",stdout);
#endif
	sieve(N-1);
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
