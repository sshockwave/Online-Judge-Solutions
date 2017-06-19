#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010;
int uprime[N],prime[N],ps=0;
bool np[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	np[0]=np[1]=true;
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				break;
			}
		}
	}
}
class Underprimes{
	private:
	inline int cntfac(int x){
		int cnt=0;
		for(int i=0,cur=2;i*i<=x;cur=prime[++i]){
			for(;x%cur==0;x/=cur,cnt++);
		}
		if(x!=1){
			cnt++;
		}
		return cnt;
	}
	public:
	int howMany(int A,int B){
		sieve(B);
		int cnt=0;
		for(int i=A;i<=B;i++){
			if(!np[cntfac(i)]){
				cnt++;
			}
		}
		return cnt;
	}
};