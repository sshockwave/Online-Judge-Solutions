#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=100010,N2=N<<1;
namespace BIT{
	const int N=N2;
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)*sizeof(c[0]));
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&(-x));
	}
	inline int sum(int x){
		int a=0;
		for(;x;a+=c[x],x^=x&(-x));
		return a;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
db ang[N2];
int lst[N2],pos[N2];
inline db angmod(db x){
	const static db r=M_PI*2;
	for(;x<0;x+=r);
	for(;x>r;x-=r);
	return x;
}
inline bool lcmp(int a,int b){
	return ang[a]<ang[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flower.in","r",stdin);
	freopen("flower.out","w",stdout);
#endif
	int n=ni,d=ni;
	for(int i=1;i<=n;i++){
		int id1=(i<<1)-2,id2=id1^1;
		int a=ni,b=ni,c=ni;
		db t=asin(-c/(d*sqrt(sqr((db)a)+sqr((db)b))));
		db ang2=atan2(a,b);
		//(t,M_PI-t)-ang2
		lst[id1]=id1,ang[id1]=angmod(t-ang2);
		lst[id2]=id2,ang[id2]=angmod(M_PI-t-ang2);
	}
	sort(lst,lst+n*2,lcmp);
	for(int i=0;i<n*2;i++){
		pos[lst[i]]=i;
	}
	BIT::init(n*2);
	lint ans=0;
	for(int i=0;i<n*2;i++){
		int t=lst[i];
		if(ang[t]<ang[t^1]){//start
			BIT::add(i+1,1);
		}else{//end
			BIT::add(pos[t^1]+1,-1);
			ans+=BIT::ask(pos[t^1]+1,i);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
