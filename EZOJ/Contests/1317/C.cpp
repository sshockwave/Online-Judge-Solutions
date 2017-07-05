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
const int N=100010,NN=1000010;
struct Edge{
	int u,v,w;
}e[N];
int mu[NN],prime[NN],mnp[NN],ps=0;
bool np[NN];
inline void sieve(){
	memset(np,0,sizeof(np));
	for(int i=2;i<NN;i++){
		if(!np[i]){
			prime[ps++]=i;
			mu[i]=-1;
			mnp[i]=i;
		}
		assert(mnp[i]);
		for(int j=0,cur=2;j<ps&&i*cur<NN;cur=prime[++j]){
			np[i*cur]=true;
			mnp[i*cur]=cur;
			assert(cur);
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
	}
}
lint lastans[NN],ans=0;
namespace unifind{
	int fa[N],tag[N],size[N],tim=0;
	int root(int x){
		if(tag[x]<tim||fa[x]==x){
			return x;
		}
		return fa[x]=root(fa[x]);
	}
	inline lint work(const set<int>&s){
		tim++;
		lint ans=0;
		for(set<int>::iterator it=s.begin();it!=s.end();it++){
			int u=root(e[*it].u),v=root(e[*it].v);
			if(tag[u]<tim){
				tag[u]=tim,fa[u]=u,size[u]=1;
			}
			if(tag[v]<tim){
				tag[v]=tim,fa[v]=v,size[v]=1;
			}
			ans+=(lint)size[u]*size[v];
			if(size[v]>size[u]){
				swap(u,v);
			}
			fa[v]=u,size[u]+=size[v];
		}
		return ans;
	}
}
set<int>s[NN];
int mx=0;
vector<int>vec;
inline void tear(int cur){
	vec.clear(),vec.push_back(1);
	while(cur!=1){
		int p=mnp[cur];
		assert(p);
		for(;cur%p==0;cur/=p);
		for(int i=0,tn=vec.size();i<tn;i++){
			vec.push_back(vec[i]*p);
		}
	}
}
inline void ins(int id,int cur){
	tear(cur);
	for(int i=1,tn=vec.size();i<tn;i++){
		assert(vec[i]!=1);
		s[vec[i]].insert(id);
	}
	apmax(mx,vec[vec.size()-1]);
}
inline void dins(int id,int cur){
	tear(cur);
	for(int i=1,tn=vec.size();i<tn;i++){
		assert(vec[i]!=1);
		int x=vec[i];
		ans-=lastans[x];
		s[x].insert(id);
		lastans[x]=unifind::work(s[x])*mu[x];
		ans+=lastans[x];
	}
}
inline void ddel(int id,int cur){
	tear(cur);
	for(int i=1,tn=vec.size();i<tn;i++){
		assert(vec[i]!=1);
		int x=vec[i];
		ans-=lastans[x];
		s[x].erase(id);
		lastans[x]=unifind::work(s[x])*mu[x];
		ans+=lastans[x];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
#endif
	sieve();
	int n=ni;
	for(int i=1;i<n;i++){
		e[i]=(Edge){ni,ni,ni};
		ins(i,e[i].w);
	}
	memset(lastans,0,sizeof(lastans));
	ans=(lint)n*(n-1)/2;
	for(int i=2;i<=mx;i++){
		if(!s[i].empty()){
			lastans[i]=unifind::work(s[i])*mu[i];
			ans+=lastans[i];
		}
	}
	printf("%lld\n",ans);
	for(int tot=ni;tot--;){
		int k=ni,x=ni;
		ddel(k,e[k].w),dins(k,x);
		e[k].w=x;
		printf("%lld\n",ans);
	}
}
