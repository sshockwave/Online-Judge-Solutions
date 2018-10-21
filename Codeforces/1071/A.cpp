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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int a=ni,b=ni;
	int t=1;
	lint s=0;
	for(;s+t<=a+b;s+=t,++t);
	--t;
	vector<int>va,vb;
	for(int i=t;i>=1;i--){
		if(a>=i){
			a-=i;
			va.push_back(i);
		}else{
			vb.push_back(i);
		}
	}
	printf("%d\n",(int)va.size());
	for(int i=0,ti=va.size();i<ti;i++){
		printf("%d ",va[i]);
	}
	putchar('\n');
	printf("%d\n",(int)vb.size());
	for(int i=0,ti=vb.size();i<ti;i++){
		printf("%d ",vb[i]);
	}
	putchar('\n');
	return 0;
}
