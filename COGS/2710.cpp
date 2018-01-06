#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
const int N=65536,O=998244353;
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
#define arr(x) static int* x=new int[poly::N]
namespace poly{
	const int SH=20,N=1<<SH;
	int sh,n,invn,mxn=0;
	int o[SH][N>>1],io[SH][N>>1];
	inline void clr(int a[],int x){
		memset(a+x,0,(n-x)<<2);
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		if(n<=mxn)return;
		mxn=n;
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			int wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0,w=1,iw=1;j<half;j++,w=(lint)w*wn%O,iw=(lint)iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N]={0};
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
			if(rev[i]<i){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				lint w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=w*a[k+half]%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	inline int* inv(const int a[],int n){
		arr(b);arr(ta);
		assert(a!=b);
		assert(n>=1);
		if(n==1){
			assert(a[0]);
			b[0]=::inv(a[0]);
			return b;
		}
		inv(a,n>>1);
		init(n<<1);
		memcpy(ta,a,n<<2);
		clr(b,n>>1),ntt(b);
		clr(ta,n),ntt(ta);
		for(int i=0;i<poly::n;i++){
			b[i]=((lint)(b[i]<<1)+O-(lint)ta[i]*b[i]%O*b[i]%O)%O;
		}
		ntt(b,-1);
		return b;
	}
	inline int* mod(const int a[],const int b[],int n,int m){
		arr(ta);arr(tb);
		if(n<m){
			memcpy(tb,a,(n+1)<<2);
			memset(tb+(n+1),0,(m-(n+1))<<2);
			return tb;
		}
		assert(b[m]);
		for(int i=0;i<=n-m;i++){
			ta[i]=a[n-i];
			tb[i]=b[m-i];
		}
		poly::init(n-m+1);
		clr(tb,n-m+1);
		memcpy(tb,inv(tb,poly::n),(n-m+1)<<2);
		poly::init(((n-m)<<1)+1);
		clr(ta,n-m+1),ntt(ta);
		clr(tb,n-m+1),ntt(tb);
		for(int i=0;i<poly::n;i++){
			ta[i]=(lint)ta[i]*tb[i]%O;
		}
		ntt(ta,-1);
		poly::init(n+1);
		for(int i=0,j=n-m;i<j;i++,j--){
			swap(ta[i],ta[j]);
		}
		clr(ta,n-m+1),ntt(ta);
		memcpy(tb,b,(m+1)<<2);
		clr(tb,m+1),ntt(tb);
		for(int i=0;i<poly::n;i++){
			ta[i]=(lint)ta[i]*tb[i]%O;
		}
		ntt(ta,-1);
		for(int i=0;i<m;i++){
			tb[i]=(a[i]+O-ta[i])%O;
		}
		//debug
		for(int i=m;i<=n;i++){
			assert(a[i]==ta[i]);
		}
		return tb;
	}
}
namespace mem{
	int pool[N*23*2];
	inline int* New(int n){
		static int* pt=pool;
		return (pt+=n)-n;
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int *a,*b;
		inline void up(){
			arr(f);arr(g);
			memcpy(f,lson->a,(m-l+1+1)<<2);
			memcpy(g,rson->a,(r-m+1)<<2);
			using namespace poly;
			init(r-l+2);
			clr(f,m-l+1+1),ntt(f);
			clr(g,r-m+1),ntt(g);
			for(int i=0;i<n;i++){
				f[i]=(lint)f[i]*g[i]%O;
			}
			ntt(f,-1);
			memcpy(a,f,(r-l+1+1)<<2);
		}
	};
	node rt;
	node build(const int l,const int r,const int a[]){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->a=mem::New(r-l+2);
		x->b=mem::New(r-l+1);
		if(l==r){
			x->a[0]=(O-a[0])%O,x->a[1]=1;
		}else{
			x->lson=build(l,x->m,a);
			x->rson=build(x->m+1,r,a+x->m+1-l);
			x->up();
		}
		return x;
	}
	void solve(node x,int a[]){
		if(x->l==x->r)return;
		arr(tmp);
		int len=x->r-x->l+1,lenl=x->m-x->l+1,lenr=x->r-x->m;
		memcpy(tmp,poly::mod(a,x->lson->a,len-1,lenl),lenl<<2);
		memcpy(tmp+lenl,poly::mod(a,x->rson->a,len-1,lenr),lenr<<2);
		memcpy(a,tmp,len<<2);
		solve(x->lson,a);
		solve(x->rson,a+lenl);
	}
}
int f[N],x[N];
int main(){
	freopen("polynomial_calc_value.in","r",stdin);
	freopen("polynomial_calc_value.out","w",stdout);
	int n=ni;
	memset(f,0,sizeof(f));
	for(int i=0;i<n;i++){
		f[i]=ni;
	}
	int m=ni;
	memset(x,0,sizeof(x));
	for(int i=0;i<m;i++){
		x[i]=ni;
	}
	poly::init((max(n,m)<<2)+1);
	seg::rt=seg::build(0,m-1,x);
	memcpy(f,poly::mod(f,seg::rt->a,n-1,m),m<<2);
	seg::solve(seg::rt,f);
	for(int i=0;i<m;i++){
		printf("%d ",f[i]);
	}
	putchar('\n');
	return 0;
}
