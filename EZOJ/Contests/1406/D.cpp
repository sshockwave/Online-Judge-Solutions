#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace poly{
	const int SH=17,N=1<<SH;
	int sh,n,invn,o[N],r[N];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)*sizeof(a[0]));
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		o[0]=1,r[0]=0;
		for(int i=1,w=fpow(3,(O-1)>>sh);i<n;i++){
			o[i]=(lint)o[i-1]*w%O;
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
		}
	}
	inline void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=o[j<<(sh-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
namespace gmath{
	int invnum[N<<1];
	inline void main(int n){
		invnum[1]=1;
		for(int i=2;i<=n;i++){
			invnum[i]=(O-(lint)O/i*invnum[O%i]%O)%O;
		}
	}
}
lint ans=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool vis[N];
	int size[N],g;
	void gcen(int x,int n){
		vis[x]=true;
		size[x]=1;
		int bal=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				gcen(v,n);
				size[x]+=size[v];
				apmax(bal,size[v]);
			}
		}
		vis[x]=false;
		apmax(bal,n-size[x]);
		if((bal<<1)<=n){
			g=x;
		}
	}
	int sum1[poly::N],sum2[poly::N],tag[poly::N],tim=0;
	void dfs(int x,int dep){
		if(tag[dep]<tim){
			tag[dep]=tim;
			sum2[dep]=0;
		}
		sum2[dep]++;
		vis[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				dfs(v,dep+1);
			}
		}
		vis[x]=false;
	}
	void solve(int x,int n){
		gcen(x,n),x=g;
		vis[x]=true;
		int d=0;
		sum1[0]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				tim++,dfs(v,1);
				int td;
				for(int &j=td=1;tag[j]==tim;j++){
					if(d<j){
						sum1[d=j]=0;
					}
					sum1[j]=(sum1[j]+sum2[j])%O;
				}
				td--;
				poly::init(td*2+1),poly::clr(sum2,td+1),poly::ntt(sum2);
				for(int j=0;j<poly::n;j++){
					sum2[j]=(lint)sum2[j]*sum2[j]%O;
				}
				poly::ntt(sum2,-1);
				for(int j=2,tj=td*2;j<=tj;j++){
					ans=(ans-(lint)gmath::invnum[j+1]*sum2[j])%O;
				}
			}
		}
		poly::init(d*2+1),poly::clr(sum1,d+1),poly::ntt(sum1);
		for(int j=0;j<poly::n;j++){
			sum1[j]=(lint)sum1[j]*sum1[j]%O;
		}
		poly::ntt(sum1,-1);
		for(int j=0,tj=d*2;j<=tj;j++){
			ans=(ans+(lint)gmath::invnum[j+1]*sum1[j])%O;
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				solve(v,size[v]>size[x]?n-size[x]:size[v]);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("expect.in","r",stdin);
	freopen("expect.out","w",stdout);
#endif
	int n=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	gmath::main(n*2);
	T::solve(1,n);
	printf("%lld\n",ans%O);
	return 0;
}
