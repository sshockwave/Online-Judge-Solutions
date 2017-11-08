#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=100010;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int size[N],dep[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	lint ans=0,cur=0;
	void dfs1(int x,int fa){
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dep[v]=dep[x]+1;
				dfs1(v,x);
				size[x]+=size[v];
			}
		}
		ans+=dep[x];
		cur+=dep[x];
	}
	int stk[N],ss=0;
	void dfs2(int x){
		apmin(ans,cur);
		for(int i=head[x],v;~i;i=bro[i]){
			if(dep[v=to[i]]==dep[x]+1){
				stk[ss++]=v;
				cur-=size[v];
				cur+=size[stk[(dep[v]>>1)+1]]-size[v];
				dfs2(v);
				cur-=size[stk[(dep[v]>>1)+1]]-size[v];
				cur+=size[v];
				ss--;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	T::init();
	int n=ni;
	for(int i=1;i<n;T::add(ni,ni),i++);
	T::dep[1]=0;
	T::dfs1(1,0);
	T::stk[T::ss++]=1;
	for(int i=T::head[1];~i;i=T::bro[i]){
		T::stk[T::ss++]=T::to[i];
		T::dfs2(T::to[i]);
		T::ss--;
	}
	printf("%lld\n",T::ans);
	return 0;
}
