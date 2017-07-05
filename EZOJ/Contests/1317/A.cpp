#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=1500010;
lint a[N],b[N];
vector<int>vec[N];
inline int lowbit(int x){
	return x&(-x);
}
inline int cntbit(int x){
	int cnt=0;
	for(;x;cnt++,x^=lowbit(x));
	return cnt;
}
inline lint sum(int i,int j){
	return b[i|j]-b[i&j];
}
inline void solve(int i,int j,int k){
	lint A=sum(i,j),B=sum(j,k),C=sum(k,i),all=((lint)A+B+C)/2;
	a[i]=all-B,a[j]=all-C,a[k]=all-A;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("spy1.in","r",stdin);
	freopen("spy.out","w",stdout);
#endif
	int n=ni,sh=cntbit(n-1);
	for(int i=0;i<n;i++){
		b[i]=nl;
		vec[cntbit(i)].push_back(i);
	}
	for(int i=1;i<sh;i++){
		int j=0;
		int n=vec[i].size();
		for(;j+3<=n;j+=3){
			solve(vec[i][j],vec[i][j+1],vec[i][j+2]);
		}
		for(;j<n;j++){
			a[vec[i][j]]=sum(vec[i][j],vec[i][0])-a[vec[i][0]];
		}
	}
	a[0]=b[0],a[n-1]=b[n-1];
	for(int i=1;i<n;i++){
		if((cntbit(i)&1)==0){
			a[0]-=a[i];
		}
	}
	for(int i=0,tn=n-1;i<tn;i++){
		a[n-1]-=a[i];
	}
	for(int i=0;i<n;i++){
		printf("%lld ",a[i]);
	}
	putchar('\n');
}
