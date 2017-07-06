#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=10000010;
uint prime[N],mnfac[N],mnexp[N],d[N],ps=0;
bool np[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	d[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ps++]=i;
			mnfac[i]=i;
			mnexp[i]=1;
		}
		d[i]=d[i/mnfac[i]]*(mnexp[i]+1);
		for(uint j=0,cur=2;j<ps&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mnfac[i*cur]=mnfac[i]*cur;
				mnexp[i*cur]=mnexp[i]+1;
				break;
			}else{
				mnfac[i*cur]=cur;
				mnexp[i*cur]=1;
			}
		}
	}
}
struct pti{
	int a,b,c;
	pti(int _a,int _b,int _c):a(_a),b(_b),c(_c){
		if(a>b){
			swap(a,b);
		}
		if(b>c){
			swap(b,c);
		}
		if(a>b){
			swap(a,b);
		}
	}
	inline friend bool operator < (const pti &a,const pti &b){
		return a.a==b.a?(a.b==b.b?(a.c<b.c):a.b<b.b):a.a<b.a;
	}
};
map<pti,uint>cache[N];
inline uint f(int a,int b,int c,int id){
	int p=prime[id];
	if(a<p&&b<p&&c<p){
		return 1;
	}
	pti hush(a,b,c);
	map<pti,uint>::iterator it=cache[id].find(hush);
	if(it!=cache[id].end()){
		return it->second;
	}
	uint ans=0;
	for(int i=1;i<=a;i*=p){
		for(int j=1;j<=b;j*=p){
			for(int k=1;k<=c;k*=p){
				ans+=f(a/i,b/j,c/k,id+1);
			}
		}
	}
	return cache[id][hush]=ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("skyfall.in","r",stdin);
	freopen("skyfall.out","w",stdout);
#endif
	sieve();
	int A=ni,B=ni,C=ni;
	if(A*B*C<N){
		uint ans=0;
		for(int i=1;i<=A;i++){
			for(int j=1;j<=B;j++){
				for(int k=1;k<=C;k++){
					ans+=d[i*j*k];
				}
			}
		}
		printf("%u\n",ans&((1u<<30)-1));
		return 0;
	}
	printf("%u\n",f(A,B,C,0)&((1u<<30)-1));
}
