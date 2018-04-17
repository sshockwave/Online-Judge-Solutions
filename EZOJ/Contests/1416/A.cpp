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
const int N=100010;
int n;
int factcnt[N],factls[N],*fact[N];
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int cnt[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(cnt,0,sizeof(cnt));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	lint ans=0;
	int has2=0,has3=0;
	void dfs(int x,int fa){
		if(x==1||cnt[x]||(((x&1)==0)&&has2)||(x%3==0&&has3))return;
		if(fa){
			ans++;
		}
		if(fa&&bro[head[x]]==-1)return;
		if(x==2){
			has2++;
		}else if(x==3){
			has3++;
		}else for(int i=0;i<factcnt[x];++i){
			++cnt[fact[x][i]];
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
			}
		}
		if(x==2){
			has2--;
		}else if(x==3){
			has3--;
		}else for(int i=0;i<factcnt[x];++i){
			--cnt[fact[x][i]];
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	n=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			++factcnt[j];
			if(j>i){
				++factcnt[i];
			}
		}
		factls[i]=0;
		fact[i]=new int[factcnt[i]];
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			fact[j][factls[j]++]=i;
			if(j>i){
				fact[i][factls[i]++]=j;
			}
		}
		assert(factls[i]==factcnt[i]);
	}
	for(int i=1;i<=n;i++){
		T::dfs(i,0);
	}
	assert((T::ans&1)==0);
	printf("%lld\n",T::ans>>1);
	return 0;
}
