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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,L=5;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int pval[N][L];
int len;
namespace T{
	const int E=::N;
	int to[E],bro[E],head[N],e=0;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int fa[N];
	inline void init(int n){
		mset(head+1,-1,n);
		for(int i=2;i<=n;i++){
			ae(fa[i]=ni,i);
		}
	}
	inline bool ischain(int n){
		for(int i=2;i<=n;i++){
			if(fa[i]!=i-1)return false;
		}
		return true;
	}
	lint f[N][L];
	void dfs(int x){
		f[x][1]=pval[x][1];
		for(int i=2;i<=len;i++){
			f[x][i]=-LINF;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			lint t=-LINF;
			for(int j=1;j<=len;j++){
				apmax(t,f[v][j]);
			}
			lint allsum=f[x][1]-pval[x][1];
			for(int j=1;j<=len;j++){
				lint t2=f[x][j];
				f[x][j]=-LINF;
				if(t2>-LINF){
					apmax(f[x][j],t2+t);
				}
				if(j>1){
					apmax(f[x][j],allsum+f[v][j-1]+pval[x][j]);
				}
			}
		}
	}
}
namespace brute3{
	const int D=4;
	namespace seg{
		const int N=::N<<1;
		struct Node;
		typedef Node* node;
		struct Node{
			node lson,rson;
			int l,m,r;
			lint dis[D][D];
			inline void getdis(){
				for(int i=0;i<len;i++){
					for(int j=0;j<len;j++){
						dis[i][j]=-LINF;
					}
					if(i<len-1){
						dis[i][i+1]=pval[l][i+2];
					}
					dis[i][0]=pval[l][1];
				}
			}
			inline void up(){
				for(int i=0;i<len;i++){
					for(int j=0;j<len;j++){
						lint &ans=dis[i][j]=-LINF;
						for(int k=0;k<len;k++){
							if(rson->dis[i][k]>-LINF&&lson->dis[k][j]>-LINF){
								apmax(ans,rson->dis[i][k]+lson->dis[k][j]);
							}
						}
					}
				}
			}
		}pool[N];
		node build(int l,int r){
			static node n=pool;
			node x=n++;
			x->l=l,x->m=(l+r)>>1,x->r=r;
			if(l==r){
				x->getdis();
			}else{
				x->lson=build(l,x->m);
				x->rson=build(x->m+1,r);
				x->up();
			}
			return x;
		}
		void upd(node x,int p){
			if(x->l==x->r){
				x->getdis();
			}else{
				upd(p<=x->m?x->lson:x->rson,p);
				x->up();
			}
		}
	}
	inline int main(int n,int q){
		seg::node rt=seg::build(1,n-1);
		assert(n>1);
		for(int i=1;i<=q;i++){
			int x=ni;
			for(int j=1;j<=len;j++){
				pval[x][j]=ni;
			}
			if(x<n){
				seg::upd(rt,x);
			}
			lint ans=-LINF;
			for(int t=0;t<len;t++){
				apmax(ans,rt->dis[0][t]);
			}
			ans+=pval[n][1];
			printf("%lld\n",ans);
		}
		return 0;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decompose.in","r",stdin);
	freopen("decompose.out","w",stdout);
#endif
	int n=ni,q=ni;
	len=ni;
	T::init(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=len;j++){
			pval[i][j]=ni;
		}
	}
	if(T::ischain(n)&&n>1)return brute3::main(n,q);
	for(int i=1;i<=q;i++){
		int x=ni;
		for(int j=1;j<=len;j++){
			pval[x][j]=ni;
		}
		T::dfs(1);
		lint t=-LINF;
		for(int j=1;j<=len;j++){
			apmax(t,T::f[1][j]);
		}
		printf("%lld\n",t);
	}
	return 0;
}
