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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,INF=0x7f7f7f7f;
int lst[N],ls;
inline bool has(int x){
	for(int i=1;i<=ls;i++){
		if(lst[i]==x)return true;
	}
	return false;
}
inline int get_p(){
	int x=lst[1];
	for(int i=1;i<=ls;i++){
		apmin(x,lst[i]);
	}
	return x;
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e;
	bool vis[N];
	int size[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(vis+1,0,n);
		e=0;
	}
	inline void ae(const int u,const int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int u,const int v){
		ae(u,v),ae(v,u);
	}
	void gcen(int x,int n){
		vis[x]=true;
		int bal=0;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			gcen(v,n);
			size[x]+=size[v];
			apmax(bal,size[v]);
		}
		apmax(bal,n-size[x]);
		if((bal<<1)<=n){
			lst[++ls]=x;
		}
		vis[x]=false;
	}
	bool solve(int x,int n){
		ls=0,gcen(x,n);
		if(!has(x))return false;
		x=get_p();
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(vis[v=to[i]])continue;
			if(!solve(v,size[v]>size[x]?n-size[x]:size[v]))return false;
		}
		return true;
	}
}
int n;
inline const char* Main(){
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	ls=0,T::gcen(1,n);
	return T::solve(get_p(),n)?"Yes":"No";
}
int main(){
	//freopen("tree.in","r",stdin);
	int tot=ni;
	n=ni;
	for(;tot--;){
		puts(Main());
	}
	return 0;
}
