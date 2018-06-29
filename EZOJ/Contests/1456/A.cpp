#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1000010;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int qr;
	// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a integer
	template <class I>
		inline void gi (I &x) {
			for (c = gc(); c < '0' || c > '9'; c = gc());
			for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
		}
	// print a integer
	template <class I>
		inline void print (I &x) {
			if (!x) putc ('0');
			while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
			while (qr) putc (qu[qr --]);
		}
}
namespace bit_util{
	const int SH=16,N=1<<SH;
	int cc[N];
	inline void init(){
		cc[0]=-1;
		for(int i=1;i<N;i++){
			cc[i]=cc[i-1]+(i==(i&-i));
		}
	}
	inline int hb(unsigned x){
		assert(x);
		return x>>SH?cc[x>>SH]+SH:cc[x];
	}
}
namespace lb{
	const int logN=32;
	unsigned a[logN];
	inline void init(){
		mset(a,0,logN);
	}
	inline bool ins(unsigned x){
		for(int i;x;){
			i=bit_util::hb(x);
			if(a[i]){
				x^=a[i];
			}else{
				a[i]=x;
				return true;
			}
		}
		return false;
	}
	inline unsigned ask(unsigned x){
		for(int i=logN-1;i>=0;i--){
			if(((x>>i)&1)==0&&a[i]){
				x^=a[i];
			}
		}
		return x;
	}
}
int a[N];
struct Query{
	int id,l,r;
	unsigned d;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.l!=b.l?a.l>b.l:a.r<b.r;
	}
}qry[N];
int ans[N];
int nx[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	bit_util::init();
	int n;
	io::gi(n);
	nx[0]=1;
	for(int i=1;i<=n;i++){
		io::gi(a[i]);
		nx[i]=i+1;
	}
	int q;
	io::gi(q);
	for(int i=1;i<=q;i++){
		qry[i].id=i;
		io::gi(qry[i].l);
		io::gi(qry[i].r);
		io::gi(qry[i].d);
	}
	sort(qry+1,qry+q+1);
	for(int i=n,j=1;i>=1;i--){
		int *pt=nx+i-1;
		lb::init();
		for(;j<=q&&qry[j].l==i;j++){
			for(;qry[j].r>=*pt;lb::ins(a[*pt])?*(pt=nx+*pt):(*pt=nx[*pt]));
			ans[qry[j].id]=lb::ask(qry[j].d);
		}
	}
	for(int i=1;i<=q;i++){
		io::print(ans[i]);
		io::putc('\n');
	}
	io::flush();
	return 0;
}
