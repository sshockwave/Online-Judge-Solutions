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
const int N=510;
int x[N],lst[N],cnt[N],seq[N*N];
inline bool lcmp(int a,int b){
	return x[a]<x[b];
}
inline bool Main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		x[i]=ni,lst[i]=i,cnt[i]=i-1;
	}
	sort(lst+1,lst+n+1,lcmp);
	int p=1,pl=1,pr=1;
	for(int i,t=1;i=lst[t],t<=n;t++){
		for(;p<x[i]&&pr<=n;cnt[lst[pr]]?--cnt[seq[p++]=lst[pr]]:++pr);
		for(;p<x[i]&&pl<i;cnt[lst[pl]]?--cnt[seq[p++]=lst[pl]]:++pl);
		if(p<x[i])return false;
		seq[p++]=i;
		apmax(pr,i+1);
		cnt[i]=n-i;
	}
	assert(pr>n);
	for(int tp=n*n;p<=tp;cnt[lst[pl]]?--cnt[seq[p++]=lst[pl]]:++pl);
	puts("Yes");
	for(int i=1,ti=n*n;i<=ti;i++){
		printf("%d ",seq[i]);
	}
	putchar('\n');
	return true;
}
int main(){
	if(!Main()){
		puts("No");
	}
	return 0;
}
