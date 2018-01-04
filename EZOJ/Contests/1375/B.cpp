#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=30010;
int a[N];
int *lst[N];
inline bool lcmp(int* a,int* b){
	return *a<*b;
}
int cnt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("meet.in","r",stdin);
	freopen("meet.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		lst[i]=a+i;
	}
	sort(lst+1,lst+n+1,lcmp);
	for(int i=1,j=0,k=0;i<=n;i++){
		if(*lst[i]!=k){
			j++;
			k=*lst[i];
		}
		*lst[i]=j;
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		memset(cnt+1,0,n<<2);
		int tp[2]={0,0};
		for(int j=i;j<=n;j++){
			if(cnt[a[j]]){
				tp[cnt[a[j]]&1]--;
			}
			cnt[a[j]]++;
			tp[cnt[a[j]]&1]++;
			if(tp[0]==0){
				ans++;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
