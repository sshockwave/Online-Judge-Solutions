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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=400010;
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sushi.in","r",stdin);
	freopen("sushi.out","w",stdout);
#endif
	int n=ni,q=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	while(q--){
		int s=ni,t=ni,p=ni;
		for(int i=s;;i=i<n?i+1:1){
			if(p<a[i]){
				swap(a[i],p);
			}
			if(i==t)break;
		}
		printf("%d\n",p);
	}
	return 0;
}
