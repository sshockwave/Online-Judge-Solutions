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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,M=60010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int mod_inv(int x){
	assert(x);
	return fpow(x,O-2);
}
namespace poly{
	const int SH=18,N=1<<SH;
	int n,sh;
	int o[N],r[N];
	inline void clr(int a[],int x){
		mset(a+x,0,n-x);
	}
	inline void cpy(int a[],const int b[],int n){
		memcpy(a,b,n*sizeof(a[0]));
	}
	inline void calc_o(){
		o[0]=1;
		for(int i=1,w=fpow(3,(O-1)>>SH);i<N;i++){
			o[i]=(lint)o[i-1]*w%O;
		}
	}
	int __initer__=(calc_o(),r[0]=0,0);
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh;
	}
	inline void ntt(int a[],int d=1){
		if(n==1)return;
		for(int i=0;i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1));
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=o[j<<(SH-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			lint invn=mod_inv(n);
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=a[i]*invn%O;
			}
		}
	}
	inline const int* inv(const int a[],int _n){
		init(_n),_n=n;
		static int b[N],ta[N];
		mset(b,0,_n<<1);
		b[0]=mod_inv(a[0]);
		for(int i=1;(1<<i)<=_n;i++){
			int tn=1<<i;
			init(tn<<1);
			ntt(b);
			cpy(ta,a,tn),clr(ta,tn),ntt(ta);
			for(int i=0;i<n;i++){
				b[i]=(O-(lint)ta[i]*b[i]%O*b[i]%O+(b[i]<<1))%O;
			}
			ntt(b,-1),clr(b,tn);
		}
		return b;
	}
	inline const int* mod(const int a[],const int b[],int n,int m){
		static int ta[N],tb[N];
		if(n<m){
			cpy(ta,a,n+1),mset(ta+n+1,0,m-n);
			return ta;
		}
		for(int i=0;i<=n-m;i++){
			ta[i]=a[n-i];
		}
		for(int i=0;i<=n-m&&i<=m;i++){
			tb[i]=b[m-i];
		}
		if(m<=n-m){
			mset(tb+m+1,0,n-m-m);
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
		for(int i=0;i<m;i++){
			ta[i]=(a[i]+O-ta[i])%O;
		}
		for(int i=m;i<=n;i++){//cout
			assert(ta[i]==a[i]);
		}
		return ta;
	}
}
namespace seg{
	const int N=::M<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int *a;
		inline void up(){
			static int ta[poly::N],tb[poly::N];
			using namespace poly;
			int lenl=m-l+1,lenr=r-m,len=lenl+lenr;
			init(len+1);
			cpy(ta,lson->a,lenl+1),clr(ta,lenl+1),ntt(ta);
			cpy(tb,rson->a,lenr+1),clr(tb,lenr+1),ntt(tb);
			for(int i=0;i<n;i++){
				ta[i]=(lint)ta[i]*tb[i]%O;
			}
			ntt(ta,-1);
			a=new int[len+1],cpy(a,ta,len+1);
		}
	}pool[N];
	node build(int l,int r,int a[]){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->a=new int[2];
			x->a[0]=(O-a[l])%O,x->a[1]=1;
		}else{
			x->lson=build(l,x->m,a);
			x->rson=build(x->m+1,r,a);
			x->up();
		}
		return x;
	}
	void eval(node x,int y[]){
		if(x->l==x->r)return;
		static int ta[poly::N],tb[poly::N];
		using namespace poly;
		int lenl=x->m-x->l+1,lenr=x->r-x->m,len=lenl+lenr;
		cpy(ta,poly::mod(y,x->lson->a,len-1,lenl),lenl);
		cpy(tb,poly::mod(y,x->rson->a,len-1,lenr),lenr);
		cpy(y,ta,lenl),cpy(y+lenl,tb,lenr);
		eval(x->lson,y),eval(x->rson,y+lenl);
	}
}
struct pairpoly{
	int *a,*b;
	pairpoly(int n){
		a=new int[n+1];
		b=new int[n];
	}
	inline void free(){
		delete[] a;
		delete[] b;
	}
};
int a[N];
pairpoly solve(int l,int r){
	if(l==r){
		pairpoly ans(1);
		ans.a[0]=ans.b[0]=1;
		ans.a[1]=a[l];
		return ans;
	}
	int m=(l+r)>>1;
	int lenl=m-l+1,lenr=r-m,len=lenl+lenr;
	pairpoly ansl=solve(l,m),ansr=solve(m+1,r);
	static int a1[poly::N],b1[poly::N],a2[poly::N],b2[poly::N];
	using namespace poly;
	init(len+1);
	cpy(a1,ansl.a,lenl+1),clr(a1,lenl+1),ntt(a1);
	cpy(b1,ansl.b,lenl),clr(b1,lenl),ntt(b1);
	cpy(a2,ansr.a,lenr+1),clr(a2,lenr+1),ntt(a2);
	cpy(b2,ansr.b,lenr),clr(b2,lenr),ntt(b2);
	ansl.free(),ansr.free();
	for(int i=0;i<n;i++){
		b1[i]=((lint)b1[i]*a2[i]+(lint)b2[i]*a1[i])%O;
		a1[i]=(lint)a1[i]*a2[i]%O;
	}
	pairpoly ans(len);
	ntt(a1,-1),cpy(ans.a,a1,len+1);
	ntt(b1,-1),cpy(ans.b,b1,len);
	return ans;
}
struct Frac{
	int a,b,c,d;
}frac[N];
int lst[N],lstval[N];
int ans[M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("red.in","r",stdin);
	freopen("red.out","w",stdout);
#endif
	int n=ni,m=ni;
	lint sum=0,suminv=0;
	for(int i=1;i<=n;i++){
		sum+=a[i]=ni;
		if(a[i]){
			suminv+=mod_inv(a[i]);
		}
	}
	sum%=O,suminv%=O;
	frac[0]=(Frac){1,0,0,1};
	int ls=0;
	for(int i=1;i<=m;i++){
		int &a=frac[i-1].a,&b=frac[i-1].b,&c=frac[i-1].c,&d=frac[i-1].d;
		if(ni==1){
			int x=ni;
			frac[i]=(Frac){(int)((a+(lint)c*x)%O),(int)((b+(lint)d*x)%O),c,d};
		}else{
			frac[i]=(Frac){c,d,a,b};
		}
		assert(frac[i].c||frac[i].d);
		if(frac[i].c){
			if(frac[i].d){
				ans[i]=-++ls,lst[ls]=(lint)frac[i].c*mod_inv(frac[i].d)%O;
			}else{
				ans[i]=((lint)frac[i].a*n+(lint)frac[i].b*suminv)*mod_inv(frac[i].c)%O;
			}
		}else{
			ans[i]=(sum*frac[i].a+(lint)n*frac[i].b)%O*mod_inv(frac[i].d)%O;
		}
	}
	if(ls){
		pairpoly ff=solve(1,n);
		seg::node rt=seg::build(1,ls,lst);
		static int ta[poly::N];
		using namespace poly;
		cpy(ta,mod(ff.a,rt->a,n,ls),ls),seg::eval(rt,ta),cpy(lstval+1,ta,ls);
		cpy(ta,mod(ff.b,rt->a,n-1,ls),ls),seg::eval(rt,ta);
		for(int i=1;i<=ls;i++){
			lstval[i]=(lint)ta[i-1]*mod_inv(lstval[i])%O;
		}
	}
	for(int i=1;i<=m;i++){
		if(ans[i]<0){
			const int a=frac[i].a,b=frac[i].b,c=frac[i].c,d=frac[i].d;
			const int invc=mod_inv(c),invd=mod_inv(d);
			ans[i]=((lint)a*invc%O*n+((lint)b*invd%O+O-(lint)a*invc%O)*lstval[-ans[i]])%O;
		}
		printf("%d\n",ans[i]);
	}
	return 0;
}
