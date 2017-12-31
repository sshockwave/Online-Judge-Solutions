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
const int N=1000010,E=1000010;
struct Edge{
	int u,v,w,id;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}e[E];
int fa[N];
int root(int x){
	return fa[x]?fa[x]=root(fa[x]):x;
}
bool mark[E];
int main(){
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
	freopen("road2.in","r",stdin);
	freopen("road2.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=m;i++){
		e[i]=(Edge){ni,ni,ni,i};
		ni;
	}
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++){
		int u=root(e[i].u),v=root(e[i].v);
		if(u!=v){
			fa[u]=v;
			mark[e[i].id]=true;
		}
	}
	lint ans=0;
	for(int i=1;i<=m;i++){
		if(mark[i]){
			ans+=e[i].w;
			printf("%d\n",i);
		}
	}
	return 0;
}
