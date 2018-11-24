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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1000010;
struct Query{
	int l,r,idx;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.l<b.l;
	}
}q[N];
int a[N],mpa[N],pos[N];
int ans[N];
namespace B{
	int c[N],n;
	inline void init(int _n){
		mset(c+1,0,n=_n);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]^=v,x+=x&-x);
	}
	inline int ask(int x){
		int a=0;
		for(;x;a^=c[x],x^=x&-x);
		return a;
	}
}
int *num[N];
inline bool cmp_num(int* a,int* b){
	return *a<*b;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		num[i]=a+i;
	}
	sort(num+1,num+n+1,cmp_num);
	mpa[0]=-1;
	for(int i=1,j=0;i<=n;i++){
		*num[i]=mpa[j]<*num[i]?mpa[++j]=*num[i],pos[j]=n+1,j:j;
	}
	for(int i=1;i<=tot;i++){
		q[i]=(Query){ni,ni,i};
	}
	sort(q+1,q+tot+1);
	B::init(n);
	for(int i=n,j=tot;i>=1;i--){
		B::add(pos[a[i]],mpa[a[i]]);
		pos[a[i]]=i;
		for(;j>=1&&q[j].l==i;j--){
			ans[q[j].idx]=B::ask(q[j].r);
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
