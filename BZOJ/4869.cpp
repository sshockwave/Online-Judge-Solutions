#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=50010,L=40;
inline int pmod(const lint &a,const int &b){
	return a<b?a:(a%b+b);
}
inline int phi(int p){//O(sqrt(n))
	int q=p;
	for(int i=2;i*i<=q;i++){
		if(q%i==0){
			p=p/i*(i-1);
			for(;q%i==0;q/=i);
		}
	}
	if(q!=1){
		p=p/q*(q-1);
	}
	return p;
}
int p[L],ps=0;//p[ps]=1
namespace CP{
	const int step=1<<16;
	int f[L][step],g[L][step];
	inline void init(int c){
		for(int i=0;i<=ps;i++){
			f[i][0]=g[i][0]=1;
			for(int j=1;j<step;j++){
				f[i][j]=pmod((lint)f[i][j-1]*c,p[i]);
			}
			int d=pmod((lint)f[i][step-1]*c,p[i]);
			for(int j=1;j<step;j++){
				g[i][j]=pmod((lint)g[i][j-1]*d,p[i]);
			}
		}
	}
	inline int ask(int x,int i){
		return pmod((lint)f[i][x&(step-1)]*g[i][x>>16],p[i]);
	}
}
struct Num{
	int r[L];
	inline void init(int a){
		for(int i=0;i<=ps;i++){
			r[i]=pmod(a,p[i]);
		}
	}
	inline void nxt(int n){
		for(int i=0;i<n;i++){
			r[i]=CP::ask(r[i+1],i);
		}
	}
}a[N];
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid,sum,rest;
	node lson,rson;
	inline void grab(){
		assert(lend==rend);
		sum=a[lend].r[0]%p[0];
	}
	inline void up(){
		assert(lend!=rend);
		sum=(lson->sum+rson->sum)%p[0];
		rest=max(lson->rest,rson->rest);
	}
	void build(int l,int r){
		static node n=new SegmentTree[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		if(l==r){
			rest=ps;
			a[l].init(ni);
			grab();
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
	void nxt(int l,int r){
		if(rest==0){
			return;
		}
		if(lend==rend){
			a[l].nxt(rest--);
			grab();
			return;
		}
		if(r<=mid){
			lson->nxt(l,r);
		}else if(l>mid){
			rson->nxt(l,r);
		}else{
			lson->nxt(l,mid);
			rson->nxt(mid+1,r);
		}
		up();
	}
	int ask(int l,int r){
		if(lend==l&&rend==r){
			return sum;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return (lson->ask(l,mid)+rson->ask(mid+1,r))%p[0];
	}
}seg;
int main(){
	int n=ni,tot=ni;
	for(p[0]=ni;p[ps]>1;p[ps+1]=phi(p[ps]),ps++);
	p[++ps]=1;
	CP::init(ni);
	seg.build(1,n);
	while(tot--){
		int o=ni,l=ni,r=ni;
		if(o){//ask
			printf("%d\n",seg.ask(l,r));
		}else{
			seg.nxt(l,r);
		}
	}
}