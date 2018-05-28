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
namespace solve2{
	inline int ex_gcd(int _a,int _b,int &_x,int &_y){//ax+by=d
		int d[2]={_a,_b};
		int x[2]={1,0};
		int y[2]={0,1};
		for(;d[1];swap(d[0],d[1]),swap(x[0],x[1]),swap(y[0],y[1])){
			const int q=d[0]/d[1];
			d[0]-=d[1]*q;
			x[0]-=x[1]*q;
			y[0]-=y[1]*q;
		}
		_x=x[0],_y=y[0];
		if(d[0]<0){
			d[0]=-d[0],_x=-_x,_y=-_y;
		}
		return d[0];
	}
	inline int main(){
		int a=ni,b=ni,x,y;
		ex_gcd(a,-b,x,y);
		printf("%d %d\n%d %d\n",a,b,y,x);
		return 0;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("final.in","r",stdin);
	freopen("final.out","w",stdout);
#endif
	int n=ni;
	if(n==2)return solve2::main();
	return 0;
}
