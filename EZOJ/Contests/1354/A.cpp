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
const int N=10010,O=1000000007;
bool ban[N];
lint f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("stick.in","r",stdin);
	freopen("stick.out","w",stdout);
#endif
	memset(ban,0,sizeof(ban));
	int n=ni;
	for(int tot=ni;tot--;ban[ni]=true);
	f[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=0;
		if(!ban[i]){
			for(int j=0;j<i;j++){
				f[i]+=f[j]*(i-j)%O*(i-j)%O;
			}
			f[i]%=O;
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
