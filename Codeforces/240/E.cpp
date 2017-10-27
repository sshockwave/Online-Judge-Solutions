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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=200010,E=100010;
int fr[E],to[E],val[E];
int rt[N][2],con[N],fa[N],ringfa[N];
int ringroot(int x){
	return ringfa[x]?ringfa[x]=ringroot(ringfa[x]):x;
}
int root(int x){
	x=ringroot(x);
	return fa[x]?fa[x]=root(fa[x]):x;
}
namespace C{
	int nxt[E],last[E];
	inline void join(int &u,int v){
		if(!(u&&v)){
			u|=v;
			return;
		}
		nxt[last[u]]=v,last[u]=last[v];
	}
	inline void del(int &x){
		x=nxt[x];
	}
}
int stk[N];
bool okay[E>>1];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n=ni,m=ni;
	for(int i=1;i<=m;i++){
		fr[i]=ni,to[i]=ni,val[i]=ni;
		C::last[i]=i;
		C::join(rt[to[i]][val[i]],i);
	}
	int node=n;
	memset(fa,0,sizeof(fa));
	memset(ringfa,0,sizeof(ringfa));
	memset(con,0,sizeof(con));
	for(int i=1;i<=n;i++){
		stk[i]=i;
	}
	for(int i=n;i>=2;i--){
		int x=stk[i];
		for(;rt[x][0]&&root(fr[rt[x][0]])==x;C::del(rt[x][0]));
		for(;rt[x][1]&&root(fr[rt[x][1]])==x;C::del(rt[x][1]));
		if(rt[x][0]){
			con[x]=rt[x][0];
			C::del(rt[x][0]);
		}else if(rt[x][1]){
			con[x]=rt[x][1];
			C::del(rt[x][1]);
		}else{
			puts("-1");
			return 0;
		}
		con[to[con[x]]]=con[x];
		int y=root(fr[con[x]]);
		if(x==y){
			stk[i++]=++node;
			for(int p=x;p!=node;p=ringroot(fr[con[p]])){
				ringfa[p]=node;
				if(val[con[p]]){
					assert(rt[p][0]==0);
					C::join(rt[node][0],rt[p][1]);
				}else{
					C::join(rt[node][0],rt[p][0]);
					C::join(rt[node][1],rt[p][1]);
				}
			}
		}else{
			fa[x]=y;
		}
	}
	memset(okay,0,sizeof(okay));
	int cnt=0;
	for(int i=2;i<=n;i++){
		if(val[con[i]]){
			okay[con[i]]=true;
			cnt++;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=m;i++){
		if(okay[i]){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
