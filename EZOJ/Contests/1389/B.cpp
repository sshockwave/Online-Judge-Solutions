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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=200010,A=1000010;
int a[N];
int cnt[A];
int tag[A];
int main(){
#ifndef ONLINE_JUDGE
	freopen("odd.in","r",stdin);
	freopen("odd.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	int tim=0;
	lint ans=0;
	for(int i=1;i<=n;i++){
		int b[2]={0,0};
		tim++;
		for(int j=i;j<=n;j++){
			if(tag[a[j]]<tim){
				tag[a[j]]=tim;
				cnt[a[j]]=1;
				b[1]++;
			}else{
				b[cnt[a[j]]&1]--;
				cnt[a[j]]++;
				b[cnt[a[j]]&1]++;
			}
			if(b[0]==0){
				ans++;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
