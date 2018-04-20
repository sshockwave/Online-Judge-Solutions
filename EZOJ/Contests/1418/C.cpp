#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace gmath{
	int fac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
	}
}
namespace kmp{
	int fail[N];
	inline int main(int a[],int n){//get minimum loop
		fail[0]=-1;
		for(int i=0,j=-1;i<n;){
			if(j==-1||a[i+1]==a[j+1]){
				fail[++i]=++j;
			}else{
				j=fail[j];
			}
		}
		return n%(n-fail[n])==0?n-fail[n]:n;
	}
}
namespace minirep{
	int b[N<<1];
	inline void main(int a[],int n){
		if(n==1)return;
		memcpy(b+1,a+1,n*sizeof(b[0]));
		memcpy(b+n+1,a+1,n*sizeof(b[0]));
		int i=1,j=2;
		for(;i<=n&&j<=n;){
			assert(i!=j);
			int p=0;
			for(;p<=n&&b[i+p]==b[j+p];p++);
			if(p>n){
				memcpy(a+1,b+i,n*sizeof(a[0]));
				return;
			}
			if(b[i+p]<b[j+p]){
				j+=p+1;
			}else{
				i+=p+1;
			}
			if(i==j){
				++j;
			}
		}
		memcpy(a+1,b+(i<=n?i:j),n*sizeof(a[0]));
	}
}
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e,n;
	inline void init(int _n){
		n=_n,e=0,mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	namespace builder{
		int vis[N];
		bool isrt[N];
		inline void main(int a[]){
			mset(vis+1,0,n);
			mset(isrt+1,0,n);
			int tim=0;
			for(int i=1;i<=n;i++){
				if(vis[i]==0){
					++tim;
					int j=i;
					for(;vis[j]==0;j=a[j]){
						vis[j]=tim;
					}
					if(vis[j]<tim)continue;
					for(;!isrt[j];j=a[j]){
						isrt[j]=true;
					}
				}
			}
			for(int i=1;i<=n;i++){
				if(!isrt[i]){
					T::ae(a[i],i);
				}
			}
		}
	}
	int rnk[N],f[N];//f[rnk]
	namespace isomorph{
		int size[N];
		void dfs(int x){
			size[x]=1;
			for(int i=head[x],v;~i;i=bro[i]){
				dfs(v=to[i]);
				size[x]+=size[v];
			}
		}
		namespace trie{
			map<int,int>son[N];
			vector<int>nd[N];
			int n;
			inline int nn(){
				n++;
				son[n].clear();
				nd[n].clear();
				return n;
			}
			inline void init(){
				n=0,nn();
			}
			int lst[N];
			inline void ins(int rt){//ins sequence of rt
				int ls=0;
				for(int i=head[rt];~i;i=bro[i]){
					lst[++ls]=rnk[to[i]];
				}
				sort(lst+1,lst+ls+1);
				int x=1;
				for(int i=1;i<=ls;i++){
					map<int,int>&m=son[x];
					map<int,int>::iterator it=m.find(lst[i]);
					x=it==m.end()?m[lst[i]]=nn():it->second;
				}
				nd[x].push_back(rt);
			}
			int stk[N];
			void dfs(int x,int dep,int &tim){
				if(!nd[x].empty()){
					++tim;
					for(vector<int>::iterator it=nd[x].begin(),ti=nd[x].end();it!=ti;++it){
						rnk[*it]=tim;
					}
					f[tim]=1;
					for(int i=1,j=1;i<=dep;i=j){//calc f
						for(;j<=dep&&stk[i]==stk[j];j++){
							f[tim]=(lint)f[tim]*f[stk[j]]%O;
						}
						f[tim]=(lint)f[tim]*gmath::fac[j-i]%O;
					}
				}
				++dep;
				for(map<int,int>::iterator it=son[x].begin(),ti=son[x].end();it!=ti;++it){
					stk[dep]=it->first;
					dfs(it->second,dep,tim);
				}
			}
		}
		int cnt[N],lst[N];
		inline void radix_sort(){
			for(int i=1;i<=n;i++){
				if(builder::isrt[i]){
					dfs(i);
				}
			}
			mset(cnt,0,n+1);
			for(int i=1;i<=n;i++){
				++cnt[size[i]];
			}
			for(int i=1;i<=n;i++){
				cnt[i]+=cnt[i-1];
			}
			assert(cnt[n]==n);
			for(int i=1;i<=n;i++){
				lst[cnt[size[i]]--]=i;
			}
			int rnkcnt=0;
			for(int i=1,j=1;i<=n;i=j){
				trie::init();
				for(;j<=n&&size[lst[i]]==size[lst[j]];j++){
					trie::ins(lst[j]);
				}
				trie::dfs(1,0,rnkcnt);
			}
		}
	}
}
namespace trie{
	map<int,int>son[N];
	int cnt[N];
	int n;
	inline int nn(){
		n++;
		son[n].clear();
		cnt[n]=0;
		return n;
	}
	inline void init(){
		n=0,nn();
	}
	int lst[N];
	inline void ins(int ls){//ins lst
		minirep::main(lst,ls);
		int x=1;
		for(int i=1;i<=ls;i++){
			map<int,int>&m=son[x];
			map<int,int>::iterator it=m.find(lst[i]);
			x=it==m.end()?m[lst[i]]=nn():it->second;
		}
		++cnt[x];
	}
	int stk[N];
	int dfs(int x,int dep){
		int ans=1;
		if(cnt[x]){
			int cur=1;
			for(int i=1;i<=dep;i++){//calc f
				cur=(lint)cur*T::f[stk[i]]%O;
			}
			cur=(lint)cur*(dep/kmp::main(stk,dep))%O;
			ans=(lint)ans*fpow(cur,cnt[x])%O*gmath::fac[cnt[x]]%O;
		}
		++dep;
		for(map<int,int>::iterator it=son[x].begin(),ti=son[x].end();it!=ti;++it){
			stk[dep]=it->first;
			ans=(lint)ans*dfs(it->second,dep)%O;
		}
		return ans;
	}
}
int a[N];
bool vis[N];
inline int Main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	gmath::main(n);
	T::init(n);
	T::builder::main(a);
	T::isomorph::radix_sort();
	mset(vis+1,0,n);
	trie::init();
	for(int i=1;i<=n;i++){
		using T::builder::isrt;
		if(!vis[i]&&isrt[i]){
			int j=i,ls=0;
			for(;!vis[j];j=a[j]){
				vis[j]=true;
				trie::lst[++ls]=T::rnk[j];
			}
			trie::ins(ls);
		}
	}
	return ((lint)gmath::fac[n]*inv(trie::dfs(1,0))+O-1)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("langue.in","r",stdin);
	freopen("langue.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
