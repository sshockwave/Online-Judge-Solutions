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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
int col[N];
int tag[N],tim=0;
int colcnt;
void markpt(int x){
	x=col[x];
	if(tag[x]<tim){
		tag[x]=tim,++colcnt;
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dep[N],fa[N];
	void dfs(int x){
		dep[x]=dep[fa[x]]+1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			fa[v]=x;
			dfs(v);
		}
	}
	void markpath(int u,int v){
		for(;u!=v;){
			if(dep[u]<dep[v]){
				swap(u,v);
			}
			markpt(u);
			u=fa[u];
		}
		markpt(u);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	const int op=ni;
	for(int i=1;i<=n;i++){
		col[i]=ni;
	}
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::fa[1]=0,T::dep[0]=0,T::dfs(1);
	int lastans=0;
	for(;tot--;){
		++tim,colcnt=0;
		int num=ni;
		for(int i=1;i<=num;i++){
			T::markpath(ni^(lastans*op),ni^(lastans*op));
		}
		int mex=0;
		for(;tag[mex]==tim;++mex);
		printf("%d %d\n",colcnt,mex);
		lastans=colcnt+mex;
	}
	return 0;
}
