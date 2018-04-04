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
const int N=1000010;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int que[N],fa[N];
	inline void bfs(int s){
		int qh=1,qt=1;
		fa[s]=0,que[qt++]=s;
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]){
					fa[v]=x,que[qt++]=v;
				}
			}
		}
	}
	int f[N];
	inline void dp(int n){
		for(int t=n;t>=1;t--){
			int x=que[t];
			int soncnt=0,mx1=0,mx2=0;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]){
					soncnt++;
					if(f[v]>mx1){
						mx2=mx1,mx1=f[v];
					}else if(f[v]>mx2){
						mx2=f[v];
					}
				}
			}
			f[x]=mx2+soncnt;
		}
	}
}
bool vis[N];
inline bool judge(int x,int to,int rst,int soncnt){
	int acc=1;
	for(;x!=to;acc++,x=T::fa[x]){
		int dson=0,bancnt=0;
		for(int i=T::head[x],v;~i;i=T::bro[i]){
			if(!vis[v=T::to[i]]){
				dson++;
				if(soncnt-bancnt+T::f[v]>rst){
					if(acc==0||rst==0)return false;
					acc--,rst--,bancnt++;
				}
			}
		}
		soncnt-=dson;
	}
	return true;
}
inline int Main(){
	int n=ni,to=ni,fr=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::bfs(to);
	T::dp(n);
	memset(vis,0,sizeof(vis));
	for(int x=fr;x;x=T::fa[x]){
		vis[x]=true;
	}
	int soncnt=0;
	for(int x=fr;x!=to;x=T::fa[x]){
		for(int i=T::head[x],v;~i;i=T::bro[i]){
			if(!vis[v=T::to[i]]){
				soncnt++;
			}
		}
	}
	int l=0,r=n-1;
	while(l<r){
		int m=(l+r)>>1;
		if(judge(fr,to,m,soncnt)){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fish.in","r",stdin);
	freopen("fish.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
