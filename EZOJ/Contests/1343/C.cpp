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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=2010,O=1000000007;
int f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("classroom.in","r",stdin);
	freopen("classroom.out","w",stdout);
#endif
	int n=ni,m=ni,d=ni;
	f[0]=1;
	lint ans=0;
	for(int i=1,ti=(n+m-1)/(d-1);i<=ti;i++){
		for(int j=min((d-1)*i,n),tj=max((d-1)*i-(m-1),0);j>=tj;j--){
			lint tmp=0;
			for(int k=min(d-1,j);k;k--){
				tmp+=f[j-k];
			}
			if((n-j)%(d-1)==0){
				ans+=tmp%O;
			}
			f[j]=(f[j]+tmp)%O;
		}
	}
	printf("%lld\n",ans%O);
	return 0;
}
