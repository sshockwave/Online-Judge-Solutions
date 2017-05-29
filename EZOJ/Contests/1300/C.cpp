#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=1000000;
int mu[N],prime[N],ptop=0;
bool np[N];
inline int work(int m,int n){
	int sum=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			int d=gcd(i,j);
			if(mu[d]){
				sum+=i/d*j;
			}
		}
	}
	return sum;
}
int main(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
		}
		for(int j=0,cur=2;j<ptop&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
	}
	for(int tot=ni;tot--;){
		printf("%d\n",work(ni,ni)&((2<<30)-1));
	}
}