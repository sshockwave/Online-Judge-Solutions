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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=33,N2=N*N,O=998244353;
namespace gmath{
	const int N=::N2;
	int inv[N];
	inline void main(int n){
		inv[1]=1;
		for(int i=2;i<=n;i++){
			inv[i]=O-(lint)O/i*inv[O%i]%O;
			assert((lint)i*inv[i]%O==1);
		}
	}
}
using gmath::inv;
int a[N],n,sum=0;
lint ans[N];
void dfs(int x,int prob){
	if(x==sum){
		for(int i=1;i<=n;i++){
			if(a[i]){
				ans[i]+=prob;
				break;
			}
		}
		return;
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]){
			++cnt;
		}
	}
	prob=(lint)prob*inv[cnt]%O;
	for(int i=1;i<=n;i++){
		if(a[i]){
			--a[i];
			dfs(x+1,prob);
			++a[i];
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cage.in","r",stdin);
	freopen("cage.ans","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		sum+=a[i];
	}
	gmath::main(sum);
	dfs(1,1);
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i]%O);
	}
	putchar('\n');
	return 0;
}
