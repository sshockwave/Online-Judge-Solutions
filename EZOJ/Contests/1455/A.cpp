#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <set>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010,O=998244353;
int a[N],sigma;
namespace pam{
	int cnt[N],tag[N],tim=0;
	int sum=0;
	inline void init(){
		++tim;
		sum=0;
	}
	inline void add(int x){
		if(tag[x]<tim){
			cnt[x]=0,tag[x]=tim;
		}
		int nv=sum+1;
		if(nv==O){
			nv=0;
		}
		sum=((lint)sum+nv+O-cnt[x])%O;
		cnt[x]=nv;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
#endif
	const int n=ni;
	sigma=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(;tot--;){
		const int s=ni,l=ni,r=ni;
		lint ans=0;
		if(l<=s){
			pam::init();
			for(int i=s;i>=l;i--){
				pam::add(a[i]);
				if(i<=r){
					ans+=pam::sum;
				}
			}
		}
		if(s<=r){
			pam::init();
			for(int i=s;i<=r;i++){
				pam::add(a[i]);
				if(i>s&&i>=l){
					ans+=pam::sum;
				}
			}
		}
		printf("%lld\n",ans%O);
	}
	return 0;
}
