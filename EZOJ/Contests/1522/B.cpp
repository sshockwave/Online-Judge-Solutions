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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
namespace G{
	const int E=200010;
	int to[E],bro[E],head[N],e=0;
	int ind[N];
	inline void init(int n){
		mset(head+1,-1,n);
		mset(ind+1,0,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++,++ind[v];
	}
	int f[N];
	int que[N];
	int dp(const int n){
		int qh=0,qt=0;
		mset(f+1,0,n);
		int ans=0;
		for(int i=1;i<=n;i++){
			if(ind[i]==0&&head[i]!=-1){
				f[i]=1,que[qt++]=i;
			}
		}
		for(;qh<qt;){
			int x=que[qh++];
			if(head[x]==-1){
				ans+=f[x];
				continue;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				f[v=to[i]]+=f[x];
				if(--ind[v]==0){
					que[qt++]=v;
				}
			}
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	G::init(n);
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		G::ae(u,v);
	}
	printf("%d\n",G::dp(n));
	return 0;
}
