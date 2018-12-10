#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int>vi;
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
const int N=50010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
namespace poly{
	const int SH=17,N=1<<SH;
	int o[N],r[N];
	inline void init(){
		o[0]=1,r[0]=0;
		for(int i=1,w=fpow(3,(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void ntt(int a[],int n,int d=1){
		for(int i=0;i<n;i++){
			r[i]=(r[i>>1]>>1)|(i&1?n>>1:0);
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;(1<<i)<=n;i++){
			const int full=1<<i,half=full>>1;
			for(int k=0;k<n;k+=full){
				for(int j=k;j<k+half;j++){
					int p=a[j];
					lint q=(lint)o[(j-k)<<(SH-i)]*a[j+half];
					a[j]=(p+q)%O;
					a[j+half]=(p-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			int ivn=inv_pow(n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*ivn%O;
			}
		}
	}
	inline void pmul(int a[],const int b[],int n){
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*b[i]%O;
		}
	}
}
namespace disc{
	const int N=::N<<1;
	int *num[N],n=0;
	inline void psh(int &x){
		num[++n]=&x;
	}
	inline bool cmp_num(int* a,int* b){
		return *a<*b;
	}
	int mp[N];
	inline void main(){
		sort(num+1,num+n+1,cmp_num);
		int m=0;
		for(int i=1,&j=m,v=-1;i<=n;i++){
			if(v<*num[i])mp[++j]=v=*num[i];
			*num[i]=j;
		}
	}
}
struct Poly{
	int *a,n;
	Poly(){}
	Poly(int _n){
		n=_n;
		a=new int[n];
	}
	inline void del(){
		delete a;
	}
	inline friend Poly getmul(Poly a,Poly b){
		Poly c(a.n+b.n-1);
		int sn=1;
		for(;sn<c.n;sn<<=1);
		static int ta[poly::N],tb[poly::N];
		mset(ta,0,sn),mcpy(ta,a.a,a.n),poly::ntt(ta,sn);
		mset(tb,0,sn),mcpy(tb,b.a,b.n),poly::ntt(tb,sn);
		poly::pmul(ta,tb,sn);
		poly::ntt(ta,sn,-1);
		mcpy(c.a,ta,c.n);
		a.del(),b.del();
		return c;
	}
};
namespace seg{
	const int N=disc::N;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		vi lst;
	}pool[N<<1];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void pb(node x,int l,int r,int v){
		if(x->l==l&&x->r==r)return x->lst.push_back(v);
		if(r<=x->m)return pb(x->lson,l,r,v);
		if(l>x->m)return pb(x->rson,l,r,v);
		pb(x->lson,l,x->m,v);
		pb(x->rson,x->m+1,r,v);
	}
	Poly binomprod(const vi &vec,int l,int r){
		if(l==r){
			Poly ans(2);
			ans.a[0]=1-vec[l],ans.a[1]=vec[l];
			return ans;
		}else{
			const int m=(l+r)>>1;
			return getmul(binomprod(vec,l,m),binomprod(vec,m+1,r));
		}
	}
	Poly solve(node x){
		Poly a,b;
		if(x->l==x->r){
			a=Poly(1);
			a.a[0]=disc::mp[x->m]-disc::mp[x->m-1];
		}else{
			a=solve(x->lson);
			Poly tb=solve(x->rson);
			if(a.n<tb.n){
				swap(a,tb);
			}
			for(int i=0;i<tb.n;i++){
				a.a[i]=(a.a[i]+tb.a[i])%O;
			}
			tb.del();
		}
		if(x->lst.empty()){
			b=Poly(1);
			b.a[0]=1;
		}else{
			b=binomprod(x->lst,0,x->lst.size()-1);
		}
		return getmul(a,b);
	}
}
inline seg::node build_tree(){
	static int intl[N],intr[N],intp[N];
	int n=ni;
	int pl=0,pr=1e9;
	disc::psh(pl);
	disc::psh(pr);
	for(int i=1;i<=n;i++){
		disc::psh(intl[i]=ni-1);
		disc::psh(intr[i]=ni);
		intp[i]=ni;
	}
	disc::main();
	const seg::node rt=seg::build(1,pr);
	for(int i=1;i<=n;i++){
		seg::pb(rt,intl[i]+1,intr[i],intp[i]);
	}
	return rt;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("alpha.in","r",stdin);
	freopen("alpha.out","w",stdout);
#endif
	poly::init();
	const seg::node rt=build_tree();
	Poly anspoly=seg::solve(rt);
	const int k=ni;
	printf("%d\n",k<anspoly.n?(anspoly.a[k]+O)%O:0);
	return 0;
}
