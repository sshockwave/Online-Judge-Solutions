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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,E=100010;
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}e[E];
int fa[N],tag[N];
int tim=0;
int root(int x){
	if(tag[x]!=tim){
		return x;
	}
	return fa[x]=root(fa[x]);
}
int m;
inline int bchop1(int v){
	int l=1,r=m+1;
	while(l<r){
		int m=(l+r)>>1;
		if(e[m].w<v){
			l=m+1;
		}else{
			r=m;
		}
	}
	return l;
}
inline int bchop2(int v){
	int l=0,r=m;
	while(l<r){
		int m=((l+r)>>1)+1;
		if(e[m].w>v){
			r=m-1;
		}else{
			l=m;
		}
	}
	return l;
}
inline int kruskal(int l,int r){
	tim++;
	int ans=0;
	for(int i=l;i<=r;i++){
		int u=root(e[i].u),v=root(e[i].v);
		if(u!=v){
			tag[u]=tim,fa[u]=v;
			ans+=e[i].w;
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("build.in","r",stdin);
	freopen("build.out","w",stdout);
#endif
	ni,m=ni;
	int online=ni,ans=0;
	for(int i=1;i<=m;i++){
		e[i]=(Edge){ni,ni,ni};
	}
	sort(e+1,e+m+1);
	memset(tag,0,sizeof(tag));
	for(int tot=ni;tot--;){
		int l=ni-ans*online,h=ni-ans*online;
		printf("%d\n",ans=kruskal(bchop1(l),bchop2(h)));
	}
	return 0;
}
