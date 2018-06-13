#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <algorithm>
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
const int N=7,S=110,M=510,D=2,O=998244353;
namespace trie{
	const int N=::N*S*2;
	int son[N][D],ed[N],n=0;
	inline int nn(int &x){
		if(x==0){
			x=++n;
			memset(son[x],0,sizeof(son[x]));
			ed[x]=0;
		}
		return x;
	}
	inline void init(){
		//cout
	}
	inline void ins(int x,char s[],const int bt){
		for(;s[0];x=nn(son[x][s++[0]-'0']));
		ed[x]|=bt;
	}
	int fa[N],fail[N];
	int que[N];
	inline void build(int x){
		int qh=0,qt=0;
		que[qt++]=x;
		fa[x]=0,fail[x]=0;
		for(int i=0;i<D;i++){
			son[0][i]=x;
		}
		ed[0]=0;
		while(qh<qt){
			x=que[qh++];
			ed[x]|=ed[fa[x]]|ed[fail[x]];
			for(int i=0;i<D;i++){
				int &v=son[x][i];
				if(v){
					fa[v]=x;
					fail[v]=son[fail[x]][i];
					que[qt++]=v;
				}else{
					v=son[fail[x]][i];
				}
			}
		}
		for(int i=0;i<D;i++){
			son[0][i]=0;
		}
	}
	inline int ed2(int x,int v){
		int bt=ed[x];
		for(;fa[v];v=fa[v]){
			assert(v==fa[v][son][0]||v==fa[v][son][1]);
			x=son[x][v==fa[v][son][1]];
			bt|=ed[x];
		}
		return bt;
	}
}
char s[S];
struct State{
	int bt,pos,neg;
	inline friend bool operator < (const State &a,const State &b){
		return a.bt!=b.bt?a.bt<b.bt:a.pos!=b.pos?a.pos<b.pos:a.neg<b.neg;
	}
};
map<State,int>f[2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	const int n=ni,m=ni;
	trie::init();
	int pos=0,neg=0;
	trie::nn(pos),trie::nn(neg);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		trie::ins(pos,s,1<<(i-1));
		reverse(s,s+strlen(s));
		trie::ins(neg,s,1<<(i-1));
	}
	trie::build(pos);
	trie::build(neg);
	bool r=false;
	f[r][((State){0,pos,neg})]=1;
	for(int i=1;i<=m;i++,r=!r){
		f[!r].clear();
		for(map<State,int>::iterator it=f[r].begin(),ti=f[r].end();it!=ti;++it){
			const State &s=it->first;
			for(int j=0;j<D;j++){
				using trie::ed;
				pos=trie::son[s.pos][j],neg=trie::son[s.neg][!j];
				(f[!r][((State){s.bt|ed[pos]|ed[neg],pos,neg})]+=it->second)%=O;
			}
		}
	}
	lint ans=0;
	const int sn=(1<<n)-1;
	for(map<State,int>::iterator it=f[r].begin(),ti=f[r].end();it!=ti;++it){
		const State &s=it->first;
		if(sn==(s.bt|trie::ed2(s.pos,s.neg))){
			ans+=it->second;
		}
	}
	printf("%lld\n",ans%O);
	return 0;
}
