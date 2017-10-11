#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=100010;
namespace T{//splay
}
namespace seg{
}
int a[N],w[N];
int tag[N],tim=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		w[i]=ni;
	}
	for(lint ans=0;tot--;){
		if(ni==1){
			lint p=nl^ans,c=nl^ans;
			a[p]=c;
		}else{
			lint l=nl^ans,r=nl^ans;
			tim++;
			ans=0;
			for(int i=l;i<=r;i++){
				if(tag[a[i]]!=tim){
					tag[a[i]]=tim;
					ans+=w[a[i]];
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
