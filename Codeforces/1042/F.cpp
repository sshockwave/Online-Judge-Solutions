#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
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
const int N=1000010;
int ans=0;
int k;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int deg[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(deg+1,0,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
		++deg[u],++deg[v];
	}
	int dep[N];
	inline bool dep_cmp(int a,int b){
		return dep[a]<dep[b];
	}
	int dfs(int x,int fa){
		dep[x]=dep[fa]+1;
		if(deg[x]==1)return x;
		vector<int>vec;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				vec.push_back(dfs(v,x));
			}
		}
		sort(vec.begin(),vec.end(),dep_cmp);
		int p=0;
		for(;p+1<(int)vec.size()&&dep[vec[p]]-dep[x]+dep[vec[p+1]]-dep[x]<=k;p++);
		ans+=vec.size()-p-1;
		return vec[p];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
#endif
	const int n=ni;
	k=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	for(int i=1;i<=n;i++){
		if(T::deg[i]>1){
			T::dfs(i,0);
			ans++;
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
