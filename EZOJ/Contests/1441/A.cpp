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
template<class T>inline T ceil_div(const T &a,const T &b){return (a+b-1)/b;}
const int N=100010;
lint ans=0;
int blocksize;
struct State{
	int lend,hei;
	lint accu;
	inline lint collapse(int low,int rend){
		lint sz=(lint)(rend-lend)*(hei-low)-accu;
		if(sz>0){
			lint dt=ceil_div<lint>(sz,blocksize);
			ans+=dt;
			sz-=dt*blocksize;
		}
		assert(sz<=0);
		return -sz;
	}
}stk[N];
inline void pshstk(int i,int h){
	static int ss=0;
	lint accu=0;
	int lend=i-1;
	for(;ss&&stk[ss].hei>=h;ss--){
		stk[ss].accu+=accu;
		accu=stk[ss].collapse(max(h,stk[ss-1].hei),i-1);
		lend=stk[ss].lend;
	}
	stk[++ss]=(State){lend,h,accu};
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ichi.in","r",stdin);
	freopen("ichi.out","w",stdout);
#endif
	int n=ni;
	blocksize=ni;
	stk[0].hei=0;
	for(int i=1;i<=n;i++){
		pshstk(i,ni);
	}
	pshstk(n+1,0);
	printf("%lld\n",ans);
	return 0;
}
