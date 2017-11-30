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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int INF=0x7f7f7f7f;
namespace G{
	const int N=210*2,E=100000*2+N*2;
	int to[E],bro[E],cap[E],head[N],e=0;
	int indeg[N],oudeg[N];
	int bln[N],dfn[N],low[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	bool flag=true;
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(bln,-1,sizeof(bln));
		memset(dfn,0,sizeof(dfn));
		memset(instk,0,sizeof(instk));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
		if(flag){
			oudeg[u]++,indeg[v]++;
		}
	}
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				if(instk[v]){
					apmin(low[x],dfn[v]);
				}
			}else{
				tarjan(v);
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			for(int v;v=stk[--ss],instk[v]=false,bln[v]=x,v!=x;);
		}
	}
}
inline bool Main(){
	using namespace G;
	int n=ni,h=ni;
	init();
	for(int i=1;i<=n;i++){
		int a=ni,b=ni,c=ni,d=ni;
		ae(c?c+h:a,d?d:b+h);
	}
	flag=false;
	for(int i=1,j=h+1;i<=h;i++,j++){
		if(indeg[i]>oudeg[i])return false;
		if(indeg[i]!=oudeg[i])ae(0,i);
		if(indeg[j]<oudeg[j])return false;
		if(indeg[j]!=oudeg[j])ae(j,0);
	}
	tarjan(0);
	for(int i=1,ti=h<<1;i<=ti;i++){
		if((indeg[i]||oudeg[i])&&bln[i])return false;
	}
	return true;
}
int main(){
	puts(Main()?"YES":"NO");
	return 0;
}
