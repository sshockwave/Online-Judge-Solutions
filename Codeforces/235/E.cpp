#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define cout cerr
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
const int N=5010;
uint prime[N],ps=0;
bool np[N];
uint mu[N],_mu[N][N],R[N],mnp[N],lnk[N];
inline uint getR(int n){
	uint ans=0;
	for(int l=1,x,r;l<=n;l=r+1){
		x=n/l,r=n/x;
		ans+=x*(r-l+1);
	}
	return ans;
}
inline void sieve(uint n){
	memset(np,0,sizeof(np));
	mu[1]=R[1]=1;
	for(uint i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mnp[i]=i,mu[i]=-1,lnk[i]=1;
		}
		R[i]=getR(i);
		for(uint j=0,cur=2,num=i<<1;j<ps&&num<=n;num=i*(cur=prime[++j])){
			np[num]=true,mnp[num]=cur;
			if(i%cur==0){
				mu[num]=0,lnk[num]=lnk[i];
				break;
			}else{
				mu[num]=-mu[i],lnk[num]=i;
			}
		}
	}
	for(uint i=1;i<=n;i++){
		_mu[i][1]=mu[i];
		for(uint j=2;i*j<=n;j++){
			_mu[i][j]=_mu[i][j-1]+mu[i*j];
		}
	}
}
uint A,B,C;
uint vec[32];
inline uint fact(int x){
	int qt=0;
	vec[qt++]=1;
	for(;x!=1;x=lnk[x]){
		for(int i=0,p=mnp[x],tn=qt;i<tn;i++){
			vec[qt++]=vec[i]*p;
		}
	}
	return qt;
}
inline uint F(int n,int x){
	uint ans=0;
	for(int i=0,tn=fact(x);i<tn;i++){
		ans+=mu[vec[i]]*R[n/vec[i]];
	}
	return ans;
}
inline uint G(uint B,uint C,uint i,uint d){
	uint ans=0;
	for(uint l=1,x1,x2,r;l<=B;l=r+1){
		x1=B/l,x2=C/l,r=min(B/x1,C/x2);
		ans+=(_mu[d][r]-_mu[d][l-1])*F(x1,i)*F(x2,i);
	}
	return ans;
}
uint gcd(uint a,uint b){
	return b==0?a:gcd(b,a%b);
}
inline uint H(int i){
	uint ans=0;
	for(int j=0,tn=fact(i);j<tn;j++){
		ans+=G(B/vec[j],C/vec[j],i,vec[j])*mu[vec[j]];
	}
	return ans;
}
inline void sortabc(){
	if(A>B){swap(A,B);}
	if(B>C){swap(B,C);}
	if(A>B){swap(A,B);}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("skyfall.in","r",stdin);
	freopen("skyfall.out","w",stdout);
#endif
	A=ni,B=ni,C=ni,sortabc(),sieve(C);
	uint ans=0;
	for(uint i=1;i<=A;i++){
		ans+=A/i*H(i);
	}
	printf("%u\n",ans&((1<<30)-1));
}
