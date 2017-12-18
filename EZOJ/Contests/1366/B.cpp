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
const int N=100010;
bool ans[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int size[N]={0},f[N]={0};
	void dfs1(int x,int fa){
		size[x]=0;
		int son=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs1(v,x);
				size[x]+=size[v];
				if(size[v]>size[son]){
					son=v;
				}
			}
		}
		if(f[son]<=size[x]-size[son]){
			f[x]=(size[x]&1)+1;
		}else{
			f[x]=f[son]-(size[x]-size[son])+1;
		}
		size[x]++;
	}
	void dfs2(int x,int fa,int upsize,int mx1){
		int mx2=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(size[v]>size[mx1]){
					mx2=mx1,mx1=v;
				}else if(size[v]>size[mx2]){
					mx2=v;
				}
			}
		}
		ans[x]=f[mx1]<=upsize+size[x]-1-size[mx1]&&((upsize+size[x]-1)&1)==0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs2(v,x,upsize+size[x]-1-size[v],v!=mx1?mx1:mx2);
			}
		}
	}
}
int testtype;
inline void Main(){
	int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,0),T::dfs2(1,0,0,0);
	if(testtype==3){
		putchar(ans[1]+'0');
	}else for(int i=1;i<=n;i++){
		putchar(ans[i]+'0');
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("core.in","r",stdin);
	freopen("core.out","w",stdout);
#endif
	testtype=ni;
	for(int tot=ni;tot--;Main());
	return 0;
}
