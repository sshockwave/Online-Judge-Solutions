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
struct Pt{//y/x
	lint x,y;
	bool tp;
};
template<>inline void apmin(Pt &a,const Pt &b){
	const lint va=a.x*a.y;
	if(b.x>va/b.y)return;
	const lint vb=b.x*b.y;
	if(vb<va||(vb==va&&b.x<a.x)){
		a=b;
	}
}
inline void Main(){
	const lint k=next_num<lint>(),O=next_num<lint>();
	Pt a=(Pt){1,k,0},b=(Pt){1,O-k,1};
	if(a.y<b.y){
		swap(a,b);
	}
	Pt ansp=b;
	for(;a.y!=b.y;swap(a,b)){//a.y>b.y
		lint q=(a.y-1)/b.y;
		a.x+=q*b.x;
		a.y-=q*b.y;
		apmin(ansp,a);
	}
	if(ansp.tp){
		ansp.y=-ansp.y;
	}
	printf("%lld %lld\n",ansp.y,ansp.x);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("frac.in","r",stdin);
	freopen("frac.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
