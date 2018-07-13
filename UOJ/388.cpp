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
const int N=100010,O=998244353;
int seglen;
namespace seg{
	const int N=::N*20;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		int cnt;
		lint sum;
		int f[2][2][2];//[l/r][len's even/odd][cnt even/odd]
		inline void putf(int ff[2][2][2],int l,int r){
			if(this==null){
				const int len=r-l+1;
				memset(ff,0,sizeof(f));
				ff[0][1][0]=ff[1][1][0]=len-(len>>1);
				ff[0][0][0]=ff[1][0][0]=len>>1;
			}else for(int i=0;i<2;i++){
				for(int j=0;j<2;j++){
					for(int k=0;k<2;k++){
						ff[i][j][k]=f[i][j][k];
					}
				}
			}
		}
		inline void up(int l,int r){
			static int lf[2][2][2],rf[2][2][2];
			const int m=(l+r)>>1;
			lson->putf(lf,l,m);
			rson->putf(rf,m+1,r);
			{//get cnt
				cnt=lson->cnt+rson->cnt;
			}
			{//get sum
				sum=lson->sum+rson->sum;
				for(int i=0;i<2;i++){
					for(int j=0;j<2;j++){
						sum+=lf[1][i][j]*rf[0][i][j^1];
					}
				}
			}
			{//get left f
				const int lenl=m-l+1;
				for(int i=0;i<2;i++){
					for(int j=0;j<2;j++){
						f[0][i][j]=lf[0][i][j]+rf[0][i^(lenl&1)][j^(lson->cnt&1)];
					}
				}
			}
			{//get right f
				const int lenr=r-m;
				for(int i=0;i<2;i++){
					for(int j=0;j<2;j++){
						f[1][i][j]=lf[1][i^(lenr&1)][j^(rson->cnt&1)]+rf[1][i][j];
					}
				}
			}
			/*{//cout
				int suml=0,sumr=0;
				for(int i=0;i<2;i++){
					for(int j=0;j<2;j++){
						suml+=f[0][i][j];
						sumr+=f[1][i][j];
					}
				}
				const int len=r-l+1;
				assert(suml==len);
				assert(sumr==len);
			}*/
		}
	}pool[N],Null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
	}
	inline node upd(node x){
		static node n=pool;
		return x==null?*n=Null,n++:x;
	}
	node ins(node x,int p,int l=1,int r=seglen){
		x=upd(x);
		if(l==r){
			x->cnt=1;
			x->f[0][1][1]=1;
			x->f[1][1][1]=1;
		}else{
			const int m=(l+r)>>1;
			if(p<=m){
				x->lson=ins(x->lson,p,l,m);
			}else{
				x->rson=ins(x->rson,p,m+1,r);
			}
			x->up(l,r);
		}
		return x;
	}
	node mg(node u,node v,int l=1,int r=seglen){
		if(u==null||v==null)return u!=null?u:v;
		const int m=(l+r)>>1;
		u->lson=mg(u->lson,v->lson,l,m);
		u->rson=mg(u->rson,v->rson,m+1,r);
		u->up(l,r);
		return u;
	}
}
int ans=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	seg::node rt[N];
	inline void init(int n){
		mset(head+1,-1,n);
		for(int i=1;i<=n;i++){
			rt[i]=seg::null;
		}
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int con[N];
	void dfs(int x){
		for(int i=head[x],v;~i;i=bro[i]){
			if(i!=con[x]){
				v=to[i];
				con[v]=i^1;
				dfs(v);
				rt[x]=seg::mg(rt[x],rt[v]);
			}
		}
		if(con[x]!=-1){
			//when rt[x] is null, f is not correct
			//however sum is correct
			ans=(ans+rt[x]->sum%O*val[con[x]])%O;
		}
	}
}
int pres[N];
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pair.in","r",stdin);
	freopen("pair.out","w",stdout);
#endif
	const int n=ni;
	seglen=ni;
	seg::init();
	T::init(n);
	for(int i=1;i<n;i++){
		const int u=ni,v=ni;
		T::add(u,v,ni);
	}
	for(int i=1;i<=seglen;i++){
		const int x=ni;
		T::rt[x]=seg::ins(T::rt[x],i);
	}
	T::con[1]=-1,T::dfs(1);
	printf("%d\n",ans);
	return 0;
}
