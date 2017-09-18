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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=110<<1,E=1010<<1;
namespace G{
	int to[E],bro[E],head[N],e;
	int dfn[N],low[N],bln[N],tim;
	inline void init(int n){
		memset(head,-1,n<<3);
		memset(dfn,0,n<<3);
		e=tim=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int stk[N],ss=0;
	bool instk[N];
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x,instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				if(instk[v]){
					apmin(low[x],low[v]);
				}
			}else{
				tarjan(v),apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				v=stk[--ss];
				bln[v]=x;
				instk[v]=false;
			}while(x!=v);
		}
	}
}
inline bool Main(){
	int n=ni;
	G::init(n);
	for(int tot=ni;tot--;){
		bool d1=nc()=='h';
		int id1=(ni-1)<<1;
		bool d2=nc()=='h';
		int id2=(ni-1)<<1;
		G::ae(id1+(!d1),id2+d2);
		G::ae(id2+(!d2),id1+d1);
	}
	for(int i=0,ti=n<<2;i<ti;i++){
		if(!G::dfn[i]){
			G::tarjan(i);
		}
	}
	for(int i=0;i<n;i++){
		if(G::bln[i<<1]==G::bln[(i<<1)|1]){
			return false;
		}
	}
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("meal.in","r",stdin);
	freopen("meal.out","w",stdout);
#endif
	for(int tot=ni;tot--;puts(Main()?"GOOD":"BAD"));
	return 0;
}
