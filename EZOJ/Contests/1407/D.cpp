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
const int N=60010,O=998244353,I=86583718;
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
#define arr(a) static int *a=new int[poly::N]
	const int SH=17,N=1<<SH;
	int sh,n,invn,r[N],o[N];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)*sizeof(a[0]));
	}
	inline void cpy(int a[],const int b[],int x=n){
		memcpy(a,b,x*sizeof(a[0]));
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		r[0]=0,o[0]=1;
		for(int i=1,w=fpow(3,(O-1)>>sh);i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			o[i]=(lint)o[i-1]*w%O;
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
	const int* inv(const int a[],int _n){
		int sh=0;
		for(;(1<<sh)<_n;sh++);
		arr(b);arr(c);
		memset(b,0,sizeof(b[0])<<(sh+1));
		b[0]=::inv(a[0]);
		for(int t=1;t<=sh;t++){
			int full=1<<t;
			init(full<<1),ntt(b);//always cleared
			cpy(c,a,full),clr(c,full),ntt(c);
			for(int i=0;i<n;i++){
				b[i]=(O-(lint)c[i]*b[i]%O*b[i]%O+(b[i]<<1))%O;
			}
			ntt(b,-1),clr(b,full);
		}
		return b;
	}
	const int* mod(const int a[],const int b[],const int n,const int m){
		arr(ta);arr(tb);
		for(int i=0;i<=n-m;i++){
			ta[i]=a[n-i];
		}
		for(int i=0;i<=n-m&&i<=m;i++){
			tb[i]=b[m-i];
		}
		if(m<=n-m){
			memset(tb+m+1,0,(n-m-m)*sizeof(tb[0]));
		}
		cpy(tb,inv(tb,n-m+1),n-m+1);
		init((n-m)*2+1);
		clr(ta,n-m+1),ntt(ta);
		clr(tb,n-m+1),ntt(tb);
		for(int i=0;i<poly::n;i++){
			ta[i]=(lint)ta[i]*tb[i]%O;
		}
		ntt(ta,-1);
		init(n+1);
		reverse(ta,ta+n-m+1),clr(ta,n-m+1),ntt(ta);
		cpy(tb,b,m+1),clr(tb,m+1),ntt(tb);
		for(int i=0;i<poly::n;i++){
			ta[i]=(lint)ta[i]*tb[i]%O;
		}
		ntt(ta,-1);
		for(int i=0;i<=n;i++){
			ta[i]=(a[i]+O-ta[i])%O;
		}
		return ta;
	}
}
namespace seg{
	const int N=::N*2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r,n;
		int *a;
		inline void fixup(const int v){
			for(int i=n;i>0;i--){
				a[i]=((lint)(O-v)*a[i]+a[i-1])%O;
			}
			a[0]=(lint)(O-v)*a[0]%O;
		}
		inline void up(int b[]){
			arr(ta);arr(tb);
			a=new int[n+1];
			poly::init(n);
			using namespace poly;
			cpy(ta,lson->a,lson->n),clr(ta,lson->n),ntt(ta),lson->fixup(b[l]);
			rson->fixup(b[m+1]),cpy(tb,rson->a,rson->n+1),clr(tb,rson->n+1),ntt(tb);
			for(int i=0;i<poly::n;i++){
				ta[i]=(lint)ta[i]*tb[i]%O;
			}
			ntt(ta,-1);
			cpy(a,ta,n);
		}
	}pool[N];
	node build(int l,int r,int a[]){
		static node n=pool;
		node x=n++;
		x->l=l,x->r=r,x->n=r-l+1;
		{
			int n=r-l+1,lb=n&-n;
			x->m=x->l+(lb==n?n>>1:lb)-1;
		}
		if(l==r){
			x->a=new int[2];
			x->a[0]=1,x->a[1]=0;
		}else{
			x->lson=build(l,x->m,a);
			x->rson=build(x->m+1,r,a);
			x->up(a);
		}
		return x;
	}
	void solve(node x,int a[]){
		arr(ta);arr(tb);
		if(x->l==x->r)return;
		using poly::cpy;
		cpy(ta,poly::mod(a,x->lson->a,x->n-1,x->lson->n),x->lson->n);
		cpy(tb,poly::mod(a,x->rson->a,x->n-1,x->rson->n),x->rson->n);
		cpy(a,ta,x->lson->n);
		cpy(a+x->lson->n,tb,x->rson->n);
		solve(x->lson,a);
		solve(x->rson,a+x->lson->n);
	}
}
int x[N],y[N],a[N],deri[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("philo.in","r",stdin);
	freopen("philo.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		x[i]=ni,y[i]=ni;
		a[i]=((x[i]+O)+(lint)I*(y[i]+O))%O;
	}
	seg::node rt=seg::build(1,n,a);
	rt->fixup(a[1]);
	for(int i=1;i<=n;i++){
		deri[i-1]=(lint)rt->a[i]*i%O;
	}
	seg::solve(rt,deri);
	lint ans=0;
	for(int i=0;i<n;i++){
		if(y[i+1]>0){
			ans+=inv(deri[i]);
		}
	}
	printf("%lld\n",ans%O*I*2%O);
	return 0;
}
