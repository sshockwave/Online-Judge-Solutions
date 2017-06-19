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
const int N=1000010;
bool np[N];
int prime[N],ps=0;
inline void sieve(int n){
	memset(np,0,sizeof(np));
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
inline int fpow(int n){
	int s=0;
	for(;(1<<s)<n;s++);
	return s;
}
class BigFatInteger{
	public:
	int minOperations(int A,int B){
		sieve(A);
		int cnt=0,muler=0;
		for(int i=0,p=2;i<ps;p=prime[++i]){
			int e=0;
			for(;A%p==0;A/=p,e++);
			if(e){
				cout<<p<<"^"<<e<<endl;
				cnt++;
				apmax(muler,fpow(e*B));
			}
		}
		return muler+cnt;
	}
};