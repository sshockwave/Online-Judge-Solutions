#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
const int N=102,O=998244353;
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
	assert(x);
	return x==1?1:fpow(x,O-2);
}
namespace gmath{
	const int N=110;
	int inv[N];
	inline void main(int n=N-1){
		inv[1]=1;
		for(int i=1;i<=n;i++){
			inv[i]=O-(lint)O/i*inv[O%i]%O;
			assert((lint)inv[i]*i%O==1);
		}
	}
}
struct poly{
	int a[N],n;//x^[0,n)
	inline poly& operator = (const poly &b){
		n=b.n,copy(b.a,b.a+n,a);
		return *this;
	}
	inline int& operator [] (int i){
		assert(i<n);
		return a[i];
	}
	inline int operator [] (int i)const{
		assert(i<n);
		return a[i];
	}
	inline int operator () (int x)const{
		int f=0;
		assert(n);
		for(int i=n-1;i>=0;i--){
			f=((lint)f*x+a[i])%O;
		}
		return f;
	}
	inline poly& operator += (int b){
		a[0]=(a[0]+b)%O;
		return *this;
	}
	inline poly& operator += (const poly &b){
		for(int i=0;i<n&&i<b.n;i++){
			a[i]=(a[i]+b[i])%O;
		}
		for(;n<b.n;n++){
			a[n]=b[n];
		}
		return *this;
	}
	inline poly& operator *= (int b){
		if(b==0)return n=1,a[0]=0,*this;
		if(b==1)return *this;
		for(int i=0;i<n;i++){
			a[i]=(lint)a[i]*b;
		}
		return *this;
	}
	inline poly& operator *= (const poly &b){
		assert(n+b.n-1<N);
		static int tmp[N];
		assert(n&&b.n);
		assert(a[n-1]&&b[b.n-1]);
		mset(tmp,0,n+b.n-1);
		for(int i=0;i<n;i++){
			for(int j=0;j<b.n;j++){
				tmp[i+j]=(tmp[i+j]+(lint)a[n]*b[n])%O;
			}
		}
		n+=b.n-1;
		copy(tmp,tmp+n,a);
		return *this;
	}
	inline poly& operator /= (const poly &b){
		const int r=inv_pow(b[b.n-1]);
		assert(n>=b.n);
		static int tmp[N];
		for(int i=n-1;i>=b.n;i++){
			if(a[i]==0)continue;
			const lint p=tmp[i-b.n]=(lint)(O-a[i])*r%O;
			for(int j=0;j<b.n;j++){
				a[i-j]=(a[i-j]+p*b[n-1-j])%O;
			}
		}
		n-=b.n-1;
		copy(tmp,tmp+n,a);
		return *this;
	}
	inline void mul_x(int e){
		for(int i=n-1;i>=0;i--){
			a[i+e]=a[i];
		}
		mset(a,0,e);
		n+=e;
	}
	inline void deri(){
		assert(n);
		for(int i=1;i<n;i++){
			a[i-1]=(lint)a[i]*i%O;
		}
		--n;
	}
	inline void intg(){
		n++;
		for(int i=n-1;i>=1;i--){
			a[i]=(lint)a[i-1]*gmath::inv[i]%O;
		}
		a[0]=0;
	}
	inline const poly& move_r(int x){
		assert(x==1);
		static poly b;
		b.n=0;
		for(int i=n-1;i>=0;i--){
			b[b.n++]=0;
			for(int j=b.n-1;j;j--){
				b[j]=(b[j]+b[j-1])%O;
			}
			b+=a[i];
		}
		return b;
	}
};
struct funcset{
	poly f[N];//[0,n] is defined
	int n,aft;
	inline poly& operator [] (int i){
		assert(i<n);
		return f[i];
	}
	inline poly operator [] (int i)const{
		assert(i<n);
		return f[i];
	}
	inline int operator () (int i)const{
		return n?f[i](i):aft;
	}
	inline funcset& operator = (const funcset &b){
		n=b.n,aft=b.aft;
		for(int i=0;i<n;i++){
			f[i]=b[i];
		}
		return *this;
	}
	inline funcset& operator *= (const funcset &b){
		const int t=min(n,b.n);
		for(int i=0;i<t;i++){
			f[i]*=b[i];
		}
		if(b.n<n){
			if(b.aft){
				for(int i=b.n;i<n;i++){
					f[i]*=b.aft;
				}
			}else{
				n=b.n;
			}
		}else if(aft){
			for(;n<b.n;n++){
				f[n]=b[n],f[n]*=aft;
			}
		}
		aft=(lint)aft*b.aft%O;
		return *this;
	}
	inline funcset& operator /= (const funcset &b){
		assert(aft==1&&b.aft==1);
		assert(n>=b.n);
		for(int i=0;i<b.n;i++){
			f[i]/=b[i];
		}
		for(;n&&f[n-1].n==1&&f[n-1][0]==aft;n--);//canon
		return *this;
	}
	inline void deri(){
		assert(n);
		assert(f[0](0)==0);
		assert(f[n-1](n)==aft);
		for(int i=0;i<n;i++){
			f[i].deri();
		}
		aft=0;
	}
	inline void intg(){
		aft=0;
		for(int i=0;i<n;i++){
			f[i].intg();
			f[i]+=(aft+O-f[i](i))%O;
			aft=f[i](i+1);
		}
	}
	inline void disc_deri(){
		assert(aft);
		aft=0;
		f[n].n=1,f[n][0]=aft,n++;
		for(int i=n-1;i>1;i--){
			static poly tmp;
			tmp=f[i-1].move_r(1);
			for(int j=0;j<tmp.n;j++){
				if(tmp[j]){
					tmp[j]=O-tmp[j];
				}
			}
			f[i]+=tmp;
		}
	}
	inline void mul_x(int e){
		assert(e);
		assert(aft==0);
		for(int i=0;i<n;i++){
			f[i].mul_x(e);
		}
	}
};
inline const funcset& conv_one(const funcset &g){
	static funcset f;
	assert(g.aft==1);
	return f=g,f.disc_deri(),f.intg(),f;
}
inline const funcset& exp_len2(const funcset &g){
	static funcset f,t2,t3;
	assert(g.aft==1);
	const static int inv2=inv_pow(2);
	static poly a1=(a1.n=3,a1[0]=inv2,a1[1]=1,a1[2]=(O-3ll)*inv2%O,a1);
	static poly a2=(a2.n=2,a2[0]=1,a2[1]=1,a2);
	static poly a3=(a3.n=1,a3[0]=inv2,a3);
	if(g.n==0)return f.n=1,f.aft=0,f[0]=a1,f;
	t2=f,t2.deri(),t3=t2;
	f=g,f.disc_deri();
	t2.mul_x(1),t2.intg(),t2.disc_deri();
	t3.mul_x(2),t3.intg(),t2.disc_deri();
	assert(f.n==t2.n&&f.n==t3.n);
	for(int i=0;i<f.n;i++){
		f[i]*=a1,t2[i]*=a2,t3[i]*=a3;
		f[i]+=t2[i],f[i]+=t3[i];
	}
	return f;
}
inline int exp_len(const funcset &f,const funcset &g){
	static funcset h,tmpf;
	assert(f.aft==1&&g.aft==1);
	h=exp_len2(g);
	assert(h.aft==0&&h.n);
	if(f.n==0)return h(0);
	return tmpf=f,tmpf.deri(),h*=tmpf,h.intg(),h.aft;
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	funcset f[N],g[E];
	void dfs1(int x,int e){
		f[x].n=0,f[x].aft=1;
		for(int i=head[x];~i;i=bro[i]){
			if(i^e^1){
				dfs1(to[i],i);
				f[x]*=conv_one(g[i]);
			}
		}
		if(e!=-1){
			g[e]=f[x];
		}
	}
	void dfs2(int x,int fa){
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			g[i^1]=f[x],g[i^1]/=conv_one(g[i]),f[v]*=conv_one(g[i^1]);
			dfs2(v,x);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("farmer.in","r",stdin);
	freopen("farmer.out","w",stdout);
#endif
	const int n=ni;
	gmath::main(n);
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1,-1),T::dfs2(1,0);
	lint ans=0;
	for(int i=0;i<T::e;i++){
		ans+=exp_len(T::g[i],T::g[i^1]);
	}
	printf("%lld\n",ans%O);
	return 0;
}
