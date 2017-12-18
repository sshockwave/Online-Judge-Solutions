#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=100010,Q=110,W=1000010;
int mu[W],prime[W],mnp[W],ps=0;
bool np[W];
inline void sieve(){
	memset(np,0,sizeof(np));
	for(int i=2;i<W;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
			mnp[i]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<W;cur=prime[++j]){
			np[i*cur]=true;
			mnp[i*cur]=cur;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
	}
}
struct Edge{
	int u,v,w;
	vector<int>vec;
	inline void fact(){
		vec.push_back(1);
		for(int x=w,p;x!=1;){
			p=mnp[x];
			while(x/=p,x%p==0);
			for(int i=0,n=vec.size();i<n;i++){
				vec.push_back(vec[i]*p);
			}
		}
	}
}e[N+Q];
struct Query{
	int k,x;
	lint ans;
}q[Q];
int tot;
struct Node{
	int fa,size,dep,tag;
};
namespace uni1{
	Node node[N];
	int tim=0;
	inline void reset(int x){
		if(node[x].tag<tim){
			node[x]=(Node){0,1,0,tim};
		}
	}
	inline Node getnode(int x){
		return reset(x),node[x];
	}
	int root(int x){
		reset(x);
		if(node[x].fa==0){
			return x;
		}
		return node[x].fa=root(node[x].fa);
	}
	inline void uni(int u,int v){
		if(node[u].dep<node[v].dep){
			swap(u,v);
		}
		node[v].fa=u;
		node[u].size+=node[v].size;
		if(node[u].dep==node[v].dep){
			node[u].dep++;
		}
	}
	inline lint solve(const vector<int>&g){
		lint ans=0;
		for(int i=0,n=g.size();i<n;i++){
			int u=root(e[g[i]].u),v=root(e[g[i]].v);
			ans+=(lint)node[u].size*node[v].size;
			uni(u,v);
		}
		return ans;
	}
}
namespace uni2{
	Node node[N];
	int tim=0;
	int root(int x){
		if(node[x].tag<tim){
			node[x]=uni1::getnode(x);
			node[x].tag=tim;
		}
		if(node[x].fa==0){
			return x;
		}
		return node[x].fa=root(node[x].fa);
	}
	inline void uni(int u,int v){
		if(node[u].dep<node[v].dep){
			swap(u,v);
		}
		node[v].fa=u;
		node[u].size+=node[v].size;
		if(node[u].dep==node[v].dep){
			node[u].dep++;
		}
	}
	inline lint solve(const vector<int>&g){
		tim++;
		lint ans=0;
		for(int i=0,n=g.size();i<n;i++){
			int u=root(e[g[i]].u),v=root(e[g[i]].v);
			ans+=(lint)node[u].size*node[v].size;
			uni(u,v);
		}
		return ans;
	}
	struct Graph{
		Query *q;
		vector<int>e;
	};
	vector<Graph>g[W];
	inline void work(){
		for(int i=2;i<W;i++){
			if(!g[i].empty()){
				uni1::tim++;
				for(int j=0,tn=g[i].size();j<tn;j++){
					if(g[i][j].q){
						g[i][j].q->ans+=solve(g[i][j].e)*mu[i];
					}else{
						lint ans=uni1::solve(g[i][j].e);
						for(int k=0;k<=tot;k++){
							q[k].ans+=ans*mu[i];
						}
					}
				}
			}
		}
	}
}
inline void pushe(int w,Query *q,int e){
	using namespace uni2;
	int x=g[w].size();
	if(x==0||g[w][x-1].q!=q){
		g[w].push_back(Graph());
		g[w][x].q=q;
	}else{
		x--;
	}
	g[w][x].e.push_back(e);
}
inline void ae(Query *q,const set<int>&s){
	for(set<int>::iterator it=s.begin();it!=s.end();it++){
		vector<int>&vec=e[*it].vec;
		for(int i=1,n=vec.size();i<n;i++){
			pushe(vec[i],q,*it);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
#endif
	sieve();
	int n=ni;
	static int last[N];
	for(int i=1;i<n;i++){
		e[i]=(Edge){ni,ni,ni};
		e[i].fact();
		last[i]=i;
	}
	static bool vis[N+Q];
	memset(vis,0,sizeof(vis));
	tot=ni;
	for(int i=1;i<=tot;i++){
		q[i]=(Query){ni,ni,0ll};
		vis[q[i].k]=vis[n+i-1]=true;
		e[n+i-1]=(Edge){e[q[i].k].u,e[q[i].k].v,q[i].x};
		e[n+i-1].fact();
	}
	set<int>s,ini;
	for(int i=1;i<n;i++){
		if(vis[i]){
			s.insert(i);
		}else{
			ini.insert(i);
		}
	}
	ae(0,ini),ae(q,s);
	for(int i=1;i<=tot;i++){
		s.erase(last[q[i].k]);
		s.insert(last[q[i].k]=n+i-1);
		ae(q+i,s);
	}
	uni2::work();
	lint a1=(lint)n*(n-1)>>1;
	for(int i=0;i<=tot;i++){
		printf("%lld\n",q[i].ans+a1);
	}
}
