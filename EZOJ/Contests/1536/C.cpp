#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=2010,O=998244353;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
int a[N];
struct Poly:vector<int>{
	inline void operator += (const Poly &b){
		if(size()<b.size()){
			resize(b.size());
		}
		for(int i=0;i<(int)size()&&i<(int)b.size();i++){
			apadd(at(i),b[i]);
		}
	}
	inline void operator -= (const Poly &b){
		if(size()<b.size()){
			resize(b.size());
		}
		for(int i=0;i<(int)size()&&i<(int)b.size();i++){
			apadd(at(i),O-b[i]);
		}
	}
	inline friend Poly operator * (const Poly &a,const Poly &b){
		Poly c;
		c.resize(a.size()+b.size()-1);
		for(int i=0;i<(int)a.size();i++){
			for(int j=0;j<(int)b.size();j++){
				apadd(c[i+j],(lint)a[i]*b[j]);
			}
		}
		return c;
	}
	inline int getv(){
		int ans=0;
		for(int i=0;i<(int)size();i++){
			apadd(ans,(lint)at(i)*a[i]);
		}
		return ans;
	}
};
int ans[N];
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	Poly f[N],sum[N];
	void dfs1(int x,int fa){
		sum[x].push_back(1);
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			dfs1(v,x);
			Poly tmp=sum[v];
			tmp.insert(tmp.begin(),0);
			f[x]+=sum[x]*tmp;
			sum[x]+=tmp;
		}
	}
	void dfs2(int x,int fa,Poly g){
		f[x]+=sum[x]*g;
		sum[x]+=g;
		ans[x]=f[x].getv();
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			Poly tmp=sum[x],tmp2=sum[v];
			tmp2.insert(tmp2.begin(),0);
			tmp-=tmp2;
			dfs2(v,x,tmp);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	int n=ni,m=ni;
	int tot=ni;
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	T::init(n);
	for(int i=1;i<=m;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,0);
	T::dfs2(1,0,Poly());
	for(;tot--;){
		printf("%d\n",ans[ni]);
	}
	return 0;
}
