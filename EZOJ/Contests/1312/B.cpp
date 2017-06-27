#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int n=ni,N=210,E=5010;
struct bitset{
	const static int D=N/32+1;
	unsigned int a[D];
	bitset(){
		memset(a,0,sizeof(a));
	}
	inline bool iszero(){
		for(int i=0;i<D;i++){
			if(a[i]){
				return false;
			}
		}
		return true;
	}
	inline void set(const int &x){
		a[x>>5]|=1<<(x&31);
	}
	inline void flip(const int &x){
		a[x>>5]^=1<<(x&31);
	}
	inline bool operator [] (const int &x){
		return a[x>>5]&(1<<(x&31));
	}
	inline void operator ^= (const bitset &b){
		for(int i=0;i<D;i++){
			a[i]^=b.a[i];
		}
	}
};
struct linbase{
	bitset a[N];
	inline void ins(bitset x){
		for(int i=n;i>=0;i--){
			if(x[i]){
				if(a[i].iszero()){
					a[i]=x;
					return;
				}else{
					x^=a[i];
				}
			}
		}
	}
	inline int cal(){
		for(int i=0;i<=n;i++){
			if(a[i].iszero()){
				return i;
			}
		}
		return -1;
	}
};
int sg[N];
namespace G{
	int to[E],bro[E],val[E],head[N],e=0;
	int oud[N];
	bool vis[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(oud,0,sizeof(oud));
		memset(vis,0,sizeof(vis));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
		oud[u]++;
	}
	void dfs(int x){
		vis[x]=true;
		map<int,bitset>m;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs(v);
			}
			m[val[i]].flip(sg[v]);
		}
		linbase lb;
		for(map<int,bitset>::iterator it=m.begin();it!=m.end();it++){
			lb.ins(it->second);
		}
		sg[x]=lb.cal();
	}
}
int cnt[N];
int main(){
	G::init();
	for(int tot=ni,u,v,c;tot--;){
		u=ni,v=ni,c=ni;
		G::ae(u,v,c);
	}
	for(int x=1;x<=n;x++){
		for(int *i=G::head+x;~(*i);){
			if(G::oud[G::to[*i]]){
				i=G::bro+(*i);
			}else{
				*i=G::bro[*i];
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!G::vis[i]&&G::oud[i]){
			G::dfs(i);
		}
	}
	memset(cnt,0,sizeof(cnt));
	for(int tot=ni;tot--;){
		cnt[ni]++;
	}
	bitset ans;
	for(int i=1;i<=n;i++){
		if((cnt[i]&1)&&G::oud[i]){
			ans.flip(sg[i]);
		}
	}
	putchar('0'+!ans.iszero()),putchar('\n');
}
