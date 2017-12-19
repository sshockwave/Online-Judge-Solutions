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
const int N=500010;
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
}
int pos[N];
inline void work(int i,int x){
	if(pos[x]){
		B::add(pos[x],-1);
	}
	B::add(pos[x]=i,1);
}
struct Edge{
	int u,v;
}e[N];
struct Query{
	int l,r,id;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.l!=b.l?a.l<b.l:a.r<b.r;
	}
}q[N];
int ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sensou.in","r",stdin);
	freopen("sensou.out","w",stdout);
#endif
	int n=ni,m=ni,tot=ni;
	for(int i=1;i<=m;i++){
		e[i]=(Edge){ni,ni};
	}
	for(int i=1;i<=tot;i++){
		q[i]=(Query){ni,ni,i};
	}
	B::init(m);
	sort(q+1,q+tot+1);
	memset(pos,0,sizeof(pos));
	for(int i=m,j=tot;i>=1;i--){
		work(i,e[i].u),work(i,e[i].v);
		for(;j>=1&&q[j].l==i;j--){//get ans
			ans[q[j].id]=B::sum(q[j].r)-(q[j].r-q[j].l+1);
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
