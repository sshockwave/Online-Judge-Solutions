#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int>vi;
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
const int N=510;
int n;
int pval[N];
int lnk[N];
int lst[N];
int mnd;
bool usemnd;
lint ans;
namespace G{
	vi to[N];
	inline void add(int u,int v){
		to[u].push_back(v);
		to[v].push_back(u);
	}
	int tag[N],tim;
	bool dfs(int x){
		if(usemnd){
			if(x==mnd){
				ans-=pval[x];
				return true;
			}
		}else{
			if(pval[x]<pval[mnd]){
				mnd=x;
			}
		}
		tag[x]=tim;
		for(vi::iterator it=to[x].begin(),ti=to[x].end();it!=ti;++it){
			const int v=*it;
			if(lnk[v]==0){
				lnk[x]=v,lnk[v]=x;
				ans+=pval[v];
				return true;
			}else{
				int w=lnk[v];
				if(tag[w]<tim){
					lnk[v]=x,lnk[x]=v,lnk[w]=0;
					if(dfs(w))return true;
					lnk[v]=w,lnk[w]=v,lnk[x]=0;
				}
			}
		}
		return false;
	}
}
inline lint solve(){
	for(int i=1;i<=n;i++){
		random_shuffle(G::to[i].begin(),G::to[i].end());
		lnk[i]=0;
	}
	ans=0;
	for(int t=n;t>=1;t--){
		const int i=lst[t];
		if(lnk[i])continue;
		ans+=pval[i];
		++G::tim;
		usemnd=false,mnd=i;
		if(G::dfs(i))continue;
		++G::tim;
		usemnd=true,G::dfs(i);
	}
	lint sum=0;
	for(int i=1;i<=n;i++){
		if(lnk[i]){
			assert(lnk[lnk[i]]==i);
			sum+=pval[i];
		}
	}
	assert(sum==ans);
	return ans;
}
inline bool cmp_pval(int a,int b){
	return pval[a]<pval[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	//srand(time(0));
	n=ni;
	int e=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,cmp_pval);
	for(int i=1;i<=e;i++){
		G::add(ni,ni);
	}
	lint ans=0;
	for(int i=0;i<3;i++){
		apmax(ans,solve());
	}
	printf("%lld\n",ans);
	return 0;
}
