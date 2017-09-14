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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=1000010,INF=0x7f7f7f7f;
int a[N],b[N];
lint f[N],_b[N],_bi[N];
inline lint dy(int i,int j){
	return (f[i]+_bi[i])-(f[j]+_bi[j]);
}
inline lint dx(int i,int j){
	return _b[i]-_b[j];
}
inline bool fcmp(int i,int j,int k){
	assert(j<k);
	return dy(k,j)<=i*dx(k,j);
}
int que[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("farm.in","r",stdin);
	freopen("farm.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=ni;
		_b[i]=_b[i-1]+b[i];
		_bi[i]=_bi[i-1]+(lint)i*b[i];
	}
	f[0]=a[0]=0;
	int qh=0,qt=0;
	que[qt++]=0;
	for(int i=1;i<=n;i++){
		for(;qh+1<qt&&fcmp(i,que[qh],que[qh+1]);qh++);
		int j=que[qh];
		f[i]=f[j]+i*(_b[i]-_b[j])-(_bi[i]-_bi[j])+a[i];
		for(;qh+1<qt&&dy(i,que[qt-2])*dx(que[qt-1],que[qt-2])<=dx(i,que[qt-2])*dy(que[qt-1],que[qt-2]);qt--);
		que[qt++]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
