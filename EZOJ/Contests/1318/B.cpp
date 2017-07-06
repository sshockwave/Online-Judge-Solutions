#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=5010,sqrtN=75;
uint prime[N],mnexp[N],d[N],ps=0;
bool np[N];
inline void sieve(uint n){
	memset(np,0,sizeof(np));
	d[1]=1;
	for(uint i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			d[i]=mnexp[i]=1;
		}
		for(uint j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mnexp[i*cur]=mnexp[i]+1;
				d[i*cur]=d[i];
				break;
			}else{
				mnexp[i*cur]=1;
				d[i*cur]=d[i]*(mnexp[i]+1);
			}
		}
		d[i]*=mnexp[i]+1;
	}
}
struct mapper{
	int n,rt,ds,id[sqrtN<<1];
	inline int dfn(int x){
		assert(id[x<=rt?x:ds-n/x+1]==x);
		return x<=rt?x:ds-n/x+1;
	}
	inline void map(int _n){
		n=_n,ds=rt=0;
		for(;rt*rt<n;rt++);
		for(int l=1;l<=n;l++){
			l=n/(n/l);
			id[++ds]=l;
		}
	}
}A,B,C;
uint f[sqrtN<<1][sqrtN<<1][sqrtN<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("skyfall.in","r",stdin);
	freopen("skyfall.out","w",stdout);
#endif
	A.map(ni),B.map(ni),C.map(ni);
	sieve(max(max(A.n,B.n),C.n));
	for(int i=1;i<=A.ds;i++){
		for(int j=1;j<=B.ds;j++){
			for(int k=1;k<=C.ds;k++){
				f[i][j][k]=1;
			}
		}
	}
	for(int p=ps-1;p>=0;p--){
		int cur=prime[p];
		for(int i=A.ds;i>=1;i--){
			for(int j=B.ds;j>=1;j--){
				for(int k=B.ds;k>=1;k--){
					uint tmp=0;
					for(uint cnta=0,a=A.id[i];a>=1;cnta++,a/=cur){
						for(uint cntb=0,b=B.id[j];b>=1;cntb++,b/=cur){
							for(uint cntc=0,c=C.id[k];c>=1;cntc++,c/=cur){
								tmp+=(cnta+cntb+cntc+1)*f[A.dfn(a)][B.dfn(b)][C.dfn(c)];
							}
						}
					}
					f[i][j][k]=tmp;
				}
			}
		}
	}
	printf("%u\n",f[A.ds][B.ds][C.ds]&((1u<<30)-1));
}
