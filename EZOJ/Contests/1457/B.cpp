#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <bitset>
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
const int N=2010;
typedef bitset<N>bs;
int n;
int a[N],b[N];
int ask(int l,int r){
	if(l==0)return b[r];
	if(l<=r)return b[l-1]^b[r];
	return b[r]^ask(l,n-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("xortwo.in","r",stdin);
	freopen("xortwo.out","w",stdout);
#endif
	n=ni;
	int k=ni;
	lint tot=next_num<lint>();
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	for(;tot--;){
		b[0]=a[0];
		for(int i=1;i<n;i++){
			b[i]=b[i-1]^a[i];
		}
		for(int i=0;i<n;i++){
			a[i]=ask(i,(i+k-1)%n);
		}
	}
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
	return 0;
}
