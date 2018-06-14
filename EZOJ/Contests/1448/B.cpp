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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010;
typedef set<int>si;
typedef si::iterator iter;
int n;
namespace chi{
	const int E=200010,N=E*4;
	int nx[N],nd[N],n;
	inline void init(){
		n=0;
	}
	inline int nn(const int x){
		assert(x<=::n);
		return ++n,nx[n]=0,nd[n]=x,n;
	}
	inline void print(int x){
		cout<<"[";
		for(;x;x=nx[x]){
			cout<<nd[x];
			if(nx[x]){
				cout<<",";
			}
		}
		cout<<"]";
	}
}
si odp;
int oddedg;
namespace G{
	si to[N];
	inline void init(){
		for(int i=1;i<=n;i++){
			to[i].clear();
		}
	}
	bool vis[N];
	bool stat[N];
	void dfs(int x){
		assert(x<=n);
		vis[x]=true;
		stat[x]=false;
		for(iter it=to[x].begin(),ti=to[x].end();it!=ti;++it){
			int v=*it;
			if(v<=n){
				stat[x]^=1;
				++oddedg;
			}else{
				v-=n;
			}
			if(!vis[v]){
				dfs(v);
			}
		}
		if(stat[x]){
			odp.insert(x);
		}
	}
	inline int follow(int x){
		using chi::nd;
		using chi::nx;
		bool fir=true;
		for(;;x=nx[x]){
			const int v=nd[x];
			vis[v]=true;
			if(stat[v]==0&&!fir)break;
			fir=false;
			assert(v<=n);
			assert(!to[v].empty());
			const iter beg=to[v].begin();
			const int w=*beg;
			assert(w<=n);
			nx[x]=chi::nn(w);
			stat[v]^=1,to[v].erase(beg);
			stat[w]^=1,to[w].erase(v);
		}
		odp.erase(nd[x]);
		return x;
	}
	inline void expand(int x){
		using chi::nd;
		using chi::nx;
		for(;x;x=nx[x]){
			const int u=nd[x];
			assert(u<=n);
			vis[u]=true;
			for(;!to[u].empty();){
				const iter beg=to[u].begin();
				int v=*beg;
				if(v<=n){
					const int a=nx[x];
					nx[follow(x)]=a;
				}else{
					v-=n;
					if(!vis[v]){
						const int a=chi::nn(v);
						const int b=chi::nn(u);
						nx[a]=b,nx[b]=nx[x],nx[x]=a;
					}
					to[u].erase(beg);
					to[v].erase(u+n);
				}
			}
		}
	}
}
int st[N],ss;
inline void Main(){
	n=ni;
	G::init();
	for(int tot=ni;tot--;){
		const int u=ni,v=ni,dt=ni?0:n;
		G::to[u].insert(v+dt);
		G::to[v].insert(u+dt);
	}
	mset(G::vis+1,0,n);
	chi::init();
	assert(odp.empty());
	odp.clear();//for safety
	ss=0;
	for(int i=1;i<=n;i++){
		if(!G::vis[i]){
			size_t t=odp.size();
			oddedg=0;
			G::dfs(i);
			if(oddedg&&t==odp.size()){
				st[++ss]=chi::nn(i);
			}
		}
	}
	assert((odp.size()&1)==0);
	mset(G::vis+1,0,n);
	//cout<<"followed:"<<endl;
	for(;!odp.empty();){
		assert(*odp.begin()<=n);
		st[++ss]=chi::nn(*odp.begin());
		odp.erase(odp.begin());
		G::follow(st[ss]);
		//cout<<"\t",chi::print(st[ss]),cout<<endl;
	}
	printf("%d\n",ss);
	for(int i=1;i<=ss;i++){
		G::expand(st[i]);
		int cnt=0;
		for(int x=st[i];x;++cnt,x=chi::nx[x]);
		printf("%d",cnt);
		for(int x=st[i];x;x=chi::nx[x]){
			printf(" %d",chi::nd[x]);
		}
		putchar('\n');
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cross.in","r",stdin);
	freopen("cross.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
