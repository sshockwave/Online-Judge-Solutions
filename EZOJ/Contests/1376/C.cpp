#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <fstream>
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
template<class T>T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010,A=10000010,INF=0x7f7f7f7f;
int mnp[A],prime[A/10],ps=0;
bool np[A];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
			mnp[i]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			mnp[i*cur]=cur;
			if(i%cur==0)break;
		}
	}
}
namespace G{
	const int N=::N*20,E=::N*30*2;
	int vol[N],n;
	int to[E],bro[E],head[N],e;
	bool vis[N];
	int dfn[N],low[N],tim=0;
	inline void init(){
		e=n=0;
	}
	inline int nn(int v){
		n++;
		head[n]=-1;
		vol[n]=v;
		vis[n]=false;
		dfn[n]=0;
		return n;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int ans;
	int gsize(int x){
		vis[x]=true;
		int sz=vol[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				sz+=gsize(v);
			}
		}
		return sz;
	}
	int tarjan(int x,int allsize){
		int sz=vol[x],rsz=vol[x],bal=0;
		dfn[x]=low[x]=++tim;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]){
				apmin(low[x],dfn[v]);
			}else{
				int vsz=tarjan(v,allsize);
				sz+=vsz;
				if(low[v]>=dfn[x]){
					rsz+=vsz;
					apmax(bal,vsz);
				}else{
					apmin(low[x],low[v]);
				}
			}
		}
		apmax(bal,allsize-rsz);
		if(vol[x]){
			apmin(ans,bal);
		}
		return sz;
	}
}
map<int,int>vnode;
inline int gnode(int num){
	map<int,int>::iterator it=vnode.find(num);
	return it==vnode.end()?vnode[num]=G::nn(0):it->second;
}
int fact[N]={-1};
inline int Main(){
	G::init();
	vnode.clear();
	int n=ni;
	for(int i=1;i<=n;i++){
		int num=ni,node=G::nn(1);
		int fcnt=0;
		for(;num!=1;num/=mnp[num]){
			if(mnp[num]==fact[fcnt]){
				for(;num%fact[fcnt]==0;num/=fact[fcnt]);
				num*=fact[fcnt];
				G::add(node,gnode(mnp[num]*fact[fcnt]));
			}else{
				fact[++fcnt]=mnp[num];
				for(int j=1;j<fcnt;j++){
					G::add(node,gnode(mnp[num]*fact[j]));
				}
			}
		}
	}
	int mx1=0,mx2=0;
	G::tim=G::ans=0;
	for(int i=1;i<=G::n;i++){
		if(G::vol[i]==0)continue;
		if(G::vis[i])continue;
		int sz=G::gsize(i);
		if(sz>mx1){
			mx2=mx1,mx1=sz;
			G::ans=INF;
			G::tarjan(i,sz);
		}else if(sz>mx2){
			mx2=sz;
		}
	}
	return max(G::ans,mx2);
}
inline void space(){
	ifstream fin("/proc/self/status");
	cout<<string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("appoint.in","r",stdin);
	freopen("appoint.out","w",stdout);
#endif
	//space();
	sieve(A-1);
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
