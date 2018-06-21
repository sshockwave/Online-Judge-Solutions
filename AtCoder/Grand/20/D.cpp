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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
inline void Main(){
	const int a=ni,b=ni;
	const int m=(a+b)/(min(a,b)+1);
	if(m==1){
		bool isA=a>=b;
		const int l=ni,r=ni;
		for(int i=l;i<=r;i++){
			putchar((i&1)==isA?'A':'B');
		}
		putchar('\n');
		return;
	}
	const int c1=((lint)(m+1)*a-a-b)/((lint)m*m-1);
	const int c4=((lint)(m+1)*b-a-b)/((lint)m*m-1);
	const int c2=a-m*c1-c4;
	const int c3=b-c1-m*c4;
	assert(c2<=m);
	assert(c3<=m);
	const int l=ni,r=ni;
	for(int i=l;i<=r;i++){
		int t=i;
		if(t<=c1*(m+1)){
			putchar(t%(m+1)?'A':'B');
		}else if(t-=c1*(m+1),t<=c2){
			putchar('A');
		}else if(t-=c2,t<=c3){
			putchar('B');
		}else if(t-=c3,t<=c4*(m+1)){
			putchar(t%(m+1)==1?'A':'B');
		}else{
			assert(false);
		}
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rep.in","r",stdin);
	freopen("rep.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
