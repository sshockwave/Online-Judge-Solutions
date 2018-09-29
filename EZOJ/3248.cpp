#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
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
const int N=500010,INF=0x7f7f7f7f;
struct Pt{
	int x[3];
}pt[N];
int m=0;
namespace solve1{
	struct Item{
		int h,c;
	}a[N];
	inline bool cmp_h(const Item &a,const Item &b){
		return a.h<b.h;
	}
	inline void main(){
		const int n=ni;
		for(int i=1;i<=n;i++){
			a[i].h=ni;
			char c;
			for(;!isalpha(c=getchar()););
			a[i].c=c=='R'?0:c=='G'?1:2;
		}
		sort(a+1,a+n+1,cmp_h);
		Pt cnt=(Pt){1,1,1};
		for(int i=1,j=1;i<=n;i++){
			for(;j<=n&&a[j].h<(a[i].h<<1);j++){
				++cnt.x[a[j].c];
			}
			pt[++m]=cnt;
			--cnt.x[a[i].c];
		}
	}
}
namespace solve2{
	template<int t>struct cmp_x{
		inline bool operator () (const Pt &a,const Pt &b){
			return a.x[t]<b.x[t];
		}
	};
	inline lint main(){
		sort(pt+1,pt+m+1,cmp_x<0>());
		lint ans=0;
		lint area=0;
		int lastx=0;
		typedef set<Pt,cmp_x<1> >st;
		typedef st::iterator iter;
		st lst;
		lst.insert((Pt){0,0,INF});
		lst.insert((Pt){0,INF,0});
		for(int i=m;i>=1;i--){
			ans+=area*(lastx-pt[i].x[0]),lastx=pt[i].x[0];
			iter nx=lst.lower_bound(pt[i]);
			int nxy=nx->x[2];
			if(nxy>=pt[i].x[2])continue;
			for(iter it;it=nx,--it,it->x[2]<=pt[i].x[2];lst.erase(it)){
				area-=(lint)it->x[1]*(it->x[2]-nxy),nxy=it->x[2];
			}
			{
				iter it=nx;
				--it;
				area-=(lint)it->x[1]*(pt[i].x[2]-nxy);
			}
			if(nx->x[1]==pt[i].x[1]){
				iter it=nx;
				++nx;
				area-=(lint)it->x[1]*(it->x[2]-nx->x[2]);
				lst.erase(it);
			}
			lst.insert(pt[i]);
			area+=(lint)pt[i].x[1]*(pt[i].x[2]-nx->x[2]);
		}
		ans+=area*lastx;
		return ans-1;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	solve1::main();
	printf("%lld\n",solve2::main());
	return 0;
}
