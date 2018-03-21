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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=20010,INF=0x7f7f7f7f;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int cst;
	struct state{
		lint val;
		int cnt;
		inline friend state operator + (const state &a,const state &b){
			return (state){a.val+b.val,a.cnt+b.cnt};
		}
		inline friend bool operator < (const state &a,const state &b){
			return a.val!=b.val?a.val<b.val:a.cnt>b.cnt;
		}
		inline friend state operator + (const state &a,const lint &b){
			return (state){a.val+b,a.cnt};
		}
		inline state nxt(){
			return (state){val-cst,cnt+1};
		}
	}f[N][2];
	void dfs(int x,int fa){
		f[x][0]=f[x][1]=(state){0,0};
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				state pre0=f[x][0],pre1=f[x][1];
				f[x][0]=max(pre0+f[v][0],(pre1+f[v][1]+val[i]).nxt());
				f[x][1]=max(pre0+f[v][1]+val[i],pre1+f[v][0]);
			}
		}
		apmax(f[x][0],f[x][1].nxt());
	}
}
inline int Main(int n,int k,int c){
	T::init(n);
	int sum=0;
	for(int i=1;i<n;i++){
		int u=ni+1,v=ni+1,w=ni;
		T::add(u,v,w);
		sum+=w;
	}
	T::state &f=T::f[1][0];
	T::cst=c,T::dfs(1,0);
	int l=c,r=sum+1;
	while(l<r){
		T::cst=(l+r)>>1,T::dfs(1,0);
		if(f.cnt<=k){
			r=T::cst;
		}else{
			l=T::cst+1;
		}
	}
	T::cst=l,T::dfs(1,0);
	return (sum<<1)-f.val+k*(c-T::cst);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("newmzz.in","r",stdin);
	freopen("newmzz.out","w",stdout);
#endif
	for(int n,k,c;scanf("%d%d%d",&n,&k,&c)!=EOF;){
		printf("%d\n",Main(n,k,c));
	}
	return 0;
}
