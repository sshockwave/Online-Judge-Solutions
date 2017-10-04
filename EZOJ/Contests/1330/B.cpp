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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=50004,M=204,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
namespace poly{
	const int SH=9,N=1<<SH;
	int sh,n,invn;
	int rev[N];
	int o[SH][N],io[SH][N];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		rev[0]=0;
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			int w=1,wn=fpow(3,(MOD-1)/full),iw=1,iwn=inv(wn);
			for(int j=0;j<half;j++,apmul(w,wn),apmul(iw,iwn)){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	inline void ntt(int a[],int d){
		for(int i=0;i<n;i++){
			if(rev[i]<i){
				swap(a[rev[i]],a[i]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				int w=d==1?o[i][j]:io[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=mul(a[k+half],w);
					a[k]=add(p,q);
					a[k+half]=sub(p,q);
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				apmul(a[i],invn);
			}
		}
	}
}
int m;
struct arr{
	int a[poly::N];
	inline void clr(){
		memset(a,0,poly::n<<2);
	}
	inline void ntt(int d=1){
		poly::ntt(a,d);
	}
	inline void operator = (const arr &b){
		memcpy(a,b.a,poly::n<<2);
	}
	inline void operator += (const arr &b){
		for(int i=0;i<poly::n;i++){
			apadd(a[i],b.a[i]);
		}
	}
	inline void operator *= (const arr &b){
		for(int i=0;i<poly::n;i++){
			apmul(a[i],b.a[i]);
		}
	}
	inline void cir(){
		for(int i=m;i<poly::n;i++){
			apadd(a[i%m],a[i]);
			a[i]=0;
		}
	}
	inline friend ostream & operator << (ostream & out,const arr &b){
		for(int i=0;i<poly::n;i++){
			out<<b.a[i]<<" ";
		}
		return out;
	}
}f[N][2],idx;
namespace G{
	const int E=N<<1;
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
	arr sum,prod[2][2];
	void dfs(int x,int fa){
		f[x][0].clr(),f[x][1].clr();
		f[x][0].a[0]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				f[x][0].ntt(),f[x][1].ntt();
				f[v][0].ntt(),f[v][1].ntt();
				prod[0][0]=f[x][0],prod[0][0]*=f[v][0];
				prod[0][1]=f[x][0],prod[0][1]*=f[v][1];
				prod[1][0]=f[x][1],prod[1][0]*=f[v][0];
				prod[1][1]=f[x][1],prod[1][1]*=f[v][1];
				sum=f[v][0],sum+=f[v][1];
				f[x][0]*=sum,f[x][1]*=sum;
				f[x][0]+=prod[0][1];
				prod[0][0]*=idx;
				f[x][1]+=prod[0][0];
				f[x][1]+=prod[1][0];
				f[x][1]+=prod[1][1];
				f[x][0].ntt(-1),f[x][0].cir();
				f[x][1].ntt(-1),f[x][1].cir();
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
#endif
	int n=ni;
	m=ni;
	poly::init(m<<1);
	idx.clr();
	idx.a[1]=1;
	idx.ntt();
	G::init();
	for(int i=1;i<n;i++){
		G::add(ni,ni);
	}
	G::dfs(1,0);
	printf("%d\n",add(f[1][0].a[0],f[1][1].a[0]));
	return 0;
}
