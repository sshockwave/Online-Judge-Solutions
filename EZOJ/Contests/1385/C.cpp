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
const int N=1000010,INF=0x7f7f7f7f;
struct Intv{
	int l,r,len;
	inline friend bool operator < (const Intv &a,const Intv &b){
		return a.l!=b.l?a.l<b.l:a.r>b.r;
	}
}ints[N],tp2[N];
lint val1[N],val2[N];
int vs1=0,vs2=0;
inline bool lencmp(const Intv &a,const Intv &b){
	return a.len<b.len;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dagon.in","r",stdin);
	freopen("dagon.out","w",stdout);
#endif
	int n=ni,k=ni;
	for(int i=1;i<=n;i++){
		ints[i]=(Intv){ni,ni};
		ints[i].len=ints[i].r-ints[i].l;
	}
	lint ans=0,sum=0;
	{
		sort(ints+1,ints+n+1,lencmp);
		int l=-INF,r=INF;
		for(int i=1;i<=n-(k-1);i++){
			apmax(l,ints[i].l);
			apmin(r,ints[i].r);
		}
		if(r<INF&&l<r){
			sum+=r-l;
		}
		for(int i=n-(k-1)+1;i<=n;i++){
			sum+=ints[i].len;
		}
		ans=sum,sum=0;
	}
	sort(ints+1,ints+n+1);
	for(int i=n,l=INF,r=INF;i>=1;i--){
		if(r<=ints[i].r){
			val2[++vs2]=ints[i].len;
		}else{
			sum+=ints[i].len;
			l=ints[i].l;
			if(r<INF){
				val1[++vs1]=r-l;
			}
			r=ints[i].r;
		}
	}
	sort(val1+1,val1+vs1+1);
	sort(val2+1,val2+vs2+1);
	assert(vs1+vs2==n-1);
	for(int i=1;i<=vs1;i++){
		val1[i]+=val1[i-1];
	}
	for(int i=1;i<=vs2;i++){
		val2[i]+=val2[i-1];
	}
	int i=min(k-1,vs1),j=vs2+1;
	for(;i+(vs2-(j-1)+1)+1<=k;j--);
	assert(j>=1);
	for(;i>=0&&j>=1;i--,j--){
		apmax(ans,sum-(val1[vs1]-val1[i])+(val2[vs2]-val2[j-1]));
	}
	printf("%lld\n",ans);
	return 0;
}
