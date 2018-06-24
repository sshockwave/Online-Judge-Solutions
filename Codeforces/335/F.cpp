#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <functional>
#include <set>
#include <map>
#include <algorithm>
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
const int N=500010;
int a[N];
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pie.in","r",stdin);
	freopen("pie.out","w",stdout);
#endif
	const int n=ni;
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=a[i]=ni;
	}
	sort(a+1,a+n+1);
	multiset<int>s;
	int sing=0;
	for(int i=n,j=n;i>=1;i=j){
		const int v=a[i];
		for(;j>=1&&a[j]==v;j--);
		int cnt=i-j,ls=0;
		for(;cnt&&sing;cnt--,sing--){
			lst[ls++]=v;
		}
		if(cnt){
			multiset<int>::iterator it=s.end();
			for(;cnt>=2&&it!=s.begin();cnt-=2){
				lst[ls++]=v*2-*--it;
			}
			if(cnt){
				sing+=cnt;
				assert(it==s.begin()||cnt==1);
				if(it!=s.begin()&&v>*--it){
					s.erase(it);
					s.insert(v);
				}
			}
		}
		s.insert(lst,lst+ls);
	}
	for(multiset<int>::iterator it=s.begin(),ti=s.end();it!=ti;++it){
		ans-=max(*it,0);
	}
	printf("%I64d\n",ans);
	return 0;
}
