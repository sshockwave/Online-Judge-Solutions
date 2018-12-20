#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,D=52,O=1e9+7;
bool vis[D];
int basis;
struct State{
	int cnt[D];
	inline friend bool operator < (const State &a,const State &b){
		for(int i=0;i<D;i++){
			if(!vis[i])continue;
			int ta=a.cnt[i]-a.cnt[basis];
			int tb=b.cnt[i]-b.cnt[basis];
			if(ta!=tb)return ta<tb;
		}
		return false;
	}
};
char s[N];
int c[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
#endif
	const int n=ni;
	scanf("%s",s);
	mset(vis,0,D);
	for(int i=0;i<n;i++){
		c[i]=s[i]>='A'&&s[i]<='Z'?(s[i]-'A'):(s[i]-'a'+D/2);
		vis[c[i]]=true;
	}
	basis=c[0];
	typedef map<State,int>mp;
	mp m;
	State cur;
	mset(cur.cnt,0,D);
	++m[cur];
	for(int i=0;i<n;i++){
		++cur.cnt[c[i]];
		++m[cur];
	}
	lint ans=0;
	for(mp::iterator it=m.begin(),ti=m.end();it!=ti;++it){
		ans+=(lint)it->second*(it->second-1);
	}
	ans>>=1;
	ans%=O;
	printf("%lld\n",ans);
	return 0;
}
