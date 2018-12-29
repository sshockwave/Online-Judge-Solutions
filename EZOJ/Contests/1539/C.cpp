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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}que[N*4];
namespace dj{
	const int N=::N<<1;
	int fa[N];
	inline void init(int n){
		mset(fa+1,0x00,n);
	}
	inline int rt(int x){
		return fa[x]?fa[x]=rt(fa[x]):x;
	}
}
lint ecnt[N],ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	const int n=ni,m=ni,e=ni;
	for(int i=0;i<e;i++){
		que[i]=(Edge){ni,n+ni,ni};
	}
	mset(ans+1,0x00,m);
	for(int w=0;w<=30;w++){
		ecnt[0]=0;
		for(int i=0;i<e;i++){
			ecnt[0]+=que[i].w<=w;
		}
		dj::init(n*2);
		int qh=0,qt=e;
		for(int i=1;i<=m;i++){
			ecnt[i]=ecnt[i-1];
			for(int &j=qh,tj=qt;j<tj;j++){
				if(que[j].w>w)continue;
				int u=dj::rt(que[j].u),v=dj::rt(que[j].v);
				if(u==v){
					--ecnt[i];
				}else{
					if(u>v)swap(u,v);
					dj::fa[u]=v;
					if(u>n&&v>n){
						que[qt++]=(Edge){u-n,v-n,0};
					}
				}
			}
		}
		ecnt[0]=0;
		for(int i=1;i<=m;i++){
			ecnt[i]+=ecnt[i-1];
			ans[i]+=(lint)(i+1)*n-1-ecnt[i];
		}
	}
	for(int i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
