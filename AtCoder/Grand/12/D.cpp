#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=200010,O=1000000007;
inline int fpow(int x,int n){
	lint ret=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			(ret*=x)%=O;
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,O-2);
}
vector<int>wei[N];
int main(){
	int n=ni,x=ni,y=ni;
	for(int i=1,c;i<=n;i++,c=ni,wei[c].push_back(ni));
	int mn1=0,mn2=0;
	for(int i=1;i<=n;i++){
		sort(wei[i].begin(),wei[i].end());
		if(!wei[i].empty()){
			if(mn1==0||wei[i][0]<wei[mn1][0]){
				mn2=mn1,mn1=i;
			}else if(mn2==0||wei[i][0]<wei[mn2][0]){
				mn2=i;
			}
		}
	}
	lint ans=1;
	int totcnt=0;
	for(int i=1;i<=n;i++){
		if(!wei[i].empty()){
			int mn=i!=mn1?mn1:mn2,n=wei[i].size();
			int p1=1,p2=0;
			lint fac1=1,fac2=1;
			for(int tp=x-wei[i][0];p1<n&&wei[i][p1]<=tp;(fac1*=++p1)%=O);
			if(mn==0){//only one color
				assert(ans==1);
				assert(totcnt==0);
				break;
			}
			for(int tp=y-wei[mn][0];p2<n&&wei[i][p2]<=tp;(fac2*=++p2)%=O);
			if(p2){
				totcnt+=max(p1,p2);
				(ans*=inv(p1>p2?fac1:fac2))%=O;
			}
		}
	}
	for(;totcnt;(ans*=totcnt--)%=O);
	printf("%lld\n",ans);
	return 0;
}
