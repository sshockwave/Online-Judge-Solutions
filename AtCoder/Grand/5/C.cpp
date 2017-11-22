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
const int N=110;
int d[N];
inline bool Main(){
	int n=ni,mx=0;
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++){
		int tmp=ni;
		d[tmp]++;
		apmax(mx,tmp);
	}
	int l=0,r=mx;
	for(;l<r;l++,r--){
		d[r]-=2;
		if(d[r]<0){
			return false;
		}
	}
	if(l==r){
		d[l]--;
		if(d[l]<0){
			return false;
		}
	}
	int t=max(l,r)+1;
	for(int i=0;i<t;i++){
		if(d[i]){
			return false;
		}
	}
	return true;
}
int main(){
	puts(Main()?"Possible":"Impossible");
	return 0;
}
