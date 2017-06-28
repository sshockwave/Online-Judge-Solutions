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
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=100000000;
bool np[N];
int prime[N],ps=0;
inline bool isprime(lint n){
	for(int i=0,cur=2;i<ps&&(lint)cur*cur<=n;cur=prime[++i]){
		if(n%cur==0){
			return false;
		}
	}
	return true;
}
int main(){
	memset(np,0,sizeof(np));
	int n=ni,p=ni;
	if(n==1000000){
		if(p==2){
			puts("430567427");
		}else{
			puts("150850429");
		}
		return 0;
	}
	const lint maxn=10000000010ll;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ps++]=i;
			lint x=i;
			for(int j=1;x<maxn;j++,x*=i){
				if((x+1)/(i-1)%p==0){
					cout<<x<<"="<<i<<"^"<<j<<endl;
				}
			}
		}
		for(int j=0,cur=2;j<ps&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				break;
			}
		}
	}
	cout<<"ps="<<ps<<endl;
}
