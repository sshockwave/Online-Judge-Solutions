#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=110,D=17;
int mxcnt[N];
namespace G{
	const int E=1710<<1;
	int to[E],bro[E],head[N],e;
	int oud[N];
	inline void init(const int n){
		mset(head+1,-1,n);
		mset(oud+1,0,n);
		e=0;
	}
	inline void ae(const int u,const int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(const int u,const int v){
		oud[u]++;
		ae(u,v),ae(v,u);
	}
	int que[N];
	inline void topsort(const int n){
		int qh=1,qt=1;
		for(int i=1;i<=n;i++){
			if(oud[i]==0){
				que[qt++]=i;
			}
		}
		for(;qh<qt;){
			const int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if((i&1)&&--oud[v=to[i]]==0){
					que[qt++]=v;
				}
			}
		}
	}
	int sg[N],f[1<<D],vl[1<<D],bcnt[1<<D];
	int tag[(1<<D)+10],tim=0;
	inline void dp(const int n){
		for(int t=1;t<=n;t++){
			const int x=que[t];
			int ls=0;
			for(int i=head[x];~i;i=bro[i]){
				if((i&1)==0){
					vl[1<<ls++]=sg[to[i]];
				}
			}
			if(ls==0){
				sg[x]=0;
				continue;
			}
			++tim;
			const int sn=1<<ls;
			for(int s=0;s<sn;s++){
				const int lb=s&-s;
				bcnt[s]=s?bcnt[s^lb]+1:0;
				f[s]=s?f[s^lb]^vl[lb]:0;
				if(bcnt[s]<=mxcnt[x]&&(bcnt[s]&1)==(mxcnt[x]&1)){
					tag[f[s]]=tim;
				}
			}
			for(int &i=sg[x]=0;tag[i]==tim;i++);
		}
	}
}
inline void Main(){
	const int n=ni;
	G::init(n);
	for(int tot=ni;tot--;){
		const int u=ni+1,v=ni+1;
		G::add(u,v);
	}
	G::topsort(n);
	for(int i=1;i<=n;i++){
		mxcnt[i]=ni;
	}
	G::dp(n);
	for(int t=1,tot=ni;t<=tot;t++){
		int ans=0;
		for(int i=1;i<=n;i++){
			if(ni&1){
				ans^=G::sg[i];
			}
		}
		printf("Round#%d: %s\n",t,ans?"WINNING":"LOSING");
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	for(int i=1,tot=ni;i<=tot;i++){
		printf("Game#%d:\n",i);
		Main();
		putchar('\n');
	}
	return 0;
}
