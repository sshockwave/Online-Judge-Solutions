#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
const int N=4000010;
int mu[N],prime[N],ptop=0;
bool np[N];
uint V[N],D[N],H[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	mu[1]=1,V[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
			V[i]=1-i;
		}
		for(int j=0,cur=2;j<ptop&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				V[i*cur]=V[i];
				break;
			}else{
				mu[i*cur]=-mu[i];
				V[i*cur]=V[i]*(1-cur);
			}
		}
	}
	memset(D,0,sizeof(D));
	for(int p=1,p2=1;p2<N;p++,p2=p*p){
		for(int t=p2;t<N;t+=p2){
			D[t]+=mu[p]*V[t/p2];
		}
	}
	H[0]=0;
	for(int i=1;i<N;i++){
		D[i]=D[i]*i+D[i-1];
		H[i]=(uint)i*((uint)i+1);
	}
}
inline uint work(int A,int B){
	if(A>B){
		swap(A,B);
	}
	uint ans=0;
	for(int l=1,r;l<=A;l=r+1){
		r=min(A/(A/l),B/(B/l));
		ans+=H[A/l]*H[B/l]*(D[r]-D[l-1]);
	}
	return ans;
}
int main(){
	sieve();
	for(int tot=ni;tot--;){
		printf("%u\n",work(ni,ni)>>2);
	}
}