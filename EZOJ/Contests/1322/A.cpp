#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=100010,E=N*3;
namespace U{
	int fa[N],rk[N];
	inline void init(int n){
		memset(fa+1,0,n<<2);
		memset(rk+1,0,n<<2);
	}
	int root(int x){
		return fa[x]==0?x:(fa[x]=root(fa[x]));
	}
	inline void uni(int u,int v){
		u=root(u),v=root(v);
		if(rk[u]<rk[v]){
			swap(u,v);
		}
		fa[v]=u;
		if(rk[u]==rk[v]){
			rk[u]++;
		}
	}
}
namespace G{
	int to[E],bro[E],head[N],e;
	int tag[N],tim;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		memset(tag+1,0,n<<2);
		e=tim=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool find(int x,int t,int e,set<int>*s){
		if(x==t){
			s->insert(x);
			return true;
		}
		tag[x]=tim;
		for(int i=head[x],v;~i;i=bro[i]){
			if(i!=e&&tag[v=to[i]]<tim&&find(v,t,i^1,s)){
				s->insert(x);
				return true;
			}
		}
		return false;
	}
}
namespace W{
	int n,deg[N];
	bool flag;
	set<int>s;
	typedef set<int>::iterator iter;
	inline void operator &= (set<int>&a,const set<int>&b){
		for(iter i=a.begin(),j;i!=a.end();){
			j=i++;
			if(b.find(*j)==b.end()){
				a.erase(j);
			}
		}
	}
	inline int ans(){
		return flag?s.size():n;
	}
	inline void init(int _n){
		n=_n,flag=false;
		memset(deg+1,0,n<<2);
	}
	inline void inc(int x){
		deg[x]++;
		if(deg[x]>=3){
			set<int>pt;
			pt.insert(x);
			if(deg[x]==3){
				for(int i=G::head[x];~i;i=G::bro[i]){
					pt.insert(G::to[i]);
				}
			}
			if(flag){
				s&=pt;
			}else{
				s=pt;
				flag=true;
			}
		}
	}
	inline void add(int u,int v){
		if(ans()==0){
			return;
		}
		G::add(u,v);
		inc(u),inc(v);
		if(ans()==0){
			return;
		}
		if(U::root(u)==U::root(v)){
			set<int>pt;
			G::tim++,G::find(u,v,G::e-2,&pt);
			if(flag){
				s&=pt;
			}else{
				s=pt;
				flag=true;
			}
		}else{
			U::uni(u,v);
		}
	}
	inline void put(){
		cout<<"Now:";
		if(flag==false){
			cout<<"all"<<endl;
			return;
		}
		for(iter i=s.begin();i!=s.end();i++){
			cout<<*i<<" ";
		}
		cout<<endl;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("chain.out","w",stdout);
#endif
	int n=ni;
	U::init(n),W::init(n),G::init(n);
	for(int tot=ni;tot--;){
		if(nc()=='L'){
			W::add(ni,ni);
		}else{
			printf("%d\n",W::ans());
		}
	}
}
