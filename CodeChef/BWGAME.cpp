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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010;
struct Intv{
	int l,r;
}intv[N];
int lst[N];
inline bool r_cmp(int a,int b){
	return intv[a].r<intv[b].r;
}
int a[N],fa[N];
inline int grt(int x){
	return a[x]?fa[x]=grt(fa[x]):x;
}
int pos[N];
inline const char* Main(){
	const int n=ni;
	for(int i=1;i<=n;i++){
		intv[i]=(Intv){ni,ni};
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,r_cmp);
	mset(a+1,0,n+1);
	for(int i=1;i<=n;i++){
		Intv cur=intv[lst[i]];
		cur.l=grt(cur.l);
		if(cur.l<=cur.r){
			a[cur.l]=lst[i];
			fa[cur.l]=cur.r+1;
		}else return "Draw";
	}
	for(int i=1;i<=n;i++){
		pos[a[i]]=i;
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		if(a[i]!=i){
			const int j=pos[i];
			swap(a[i],a[j]);
			swap(pos[a[i]],pos[a[j]]);
			ans=-ans;
		}
		assert(a[i]==i);
	}
	return ans==1?"Alex":"Fedor";
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bwgame.in","r",stdin);
	freopen("bwgame.out","w",stdout);
#endif
	for(int tot=ni;tot--;puts(Main()));
	return 0;
}
