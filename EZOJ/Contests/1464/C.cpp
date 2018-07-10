#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
const int N=100010,D=3;
namespace hashutil{
	ull sh_m[N],ish_m[N];
	inline void main(int n){
		const ull w=5,iw=14757395258967641293ull;
		assert(w*iw==1);
		sh_m[0]=ish_m[0]=1;
		for(int i=1;i<=n;i++){
			sh_m[i]=sh_m[i-1]*w;
			ish_m[i]=ish_m[i-1]*iw;
		}
	}
}
struct hashstk{
	int a[N],n;
	ull h[2][N];
	inline void init(){
		n=0;
		h[0][0]=h[1][0]=0;
	}
	inline void psh(ull x){
		++x;
		if(n&&a[n]==(int)x){
			--n;
		}else{
			using namespace hashutil;
			a[++n]=x;
			h[0][n]=h[0][n-1]+x*sh_m[n-1];
			h[1][n]=x+h[1][n-1]*sh_m[1];
		}
	}
	inline ull ask(int l,int r,int d){
		using namespace hashutil;
		if(d==0){//from low to high
			if(l>r)return 0;
			return (h[0][r]-h[0][l-1])*ish_m[l-1];
		}else{//from high to low
			if(l<r)return 0;
			return h[1][l]-h[1][r-1]*sh_m[l-r+1];
		}
	}
};
struct hashlst{
	ull a[N];
	int n;
	inline void init(){
		n=0;
	}
	inline void psh(ull x){
		a[++n]=x;
	}
};
char s[N];
inline int getlcp(hashstk &a,hashstk &b){//lcp at end
	int l=0,r=min(a.n,b.n);
	for(;l<r;){
		const int m=((l+r)>>1)+1;
		if(a.ask(a.n-m+1,a.n,0)==b.ask(b.n-m+1,b.n,0)){
			l=m;
		}else{
			r=m-1;
		}
	}
	return l;
}
inline void getlst(hashlst a[D][D],const int l,const int r,hashstk &stkl){
	static hashstk stkr;
	for(int i=0;i<D;i++){
		for(int j=0;j<D;j++){
			a[i][j].init();
		}
	}
	stkr.init();
	for(int i=r;i>=l;i--){
		stkr.psh(s[i]-'a');
	}
	for(int i=l;i<=r;i++){
		const int c=s[i]-'a';
		stkr.psh(c);
		for(int j=0;j<D;j++){
			if(j==c)continue;
			stkl.psh(j);
			const int len=getlcp(stkl,stkr);
			ull v;
			using hashutil::sh_m;
			v=stkr.ask(1,stkr.n-len,0)+sh_m[stkr.n-len]*stkl.ask(stkl.n-len,1,1);
			a[c][j].psh(v);
			stkl.psh(j);
		}
		stkl.psh(c);
	}
	for(int i=r;i>=l;i--){
		stkl.psh(s[i]-'a');
	}
}
lint ans=0;
inline void put_ans(hashlst &a,hashlst &b){
	sort(a.a+1,a.a+a.n+1);
	sort(b.a+1,b.a+b.n+1);
	for(int i=1,b1=1,b2=1;i<=a.n;i++){
		for(;b1<=b.n&&b.a[b1]<a.a[i];b1++);
		for(apmax(b2,b1);b2<=b.n&&b.a[b2]==a.a[i];b2++);
		ans+=b2-b1;
	}
}
hashstk stkl,stkr;
void solve(const int l,const int r){
	if(l==r)return;
	const int m=(l+r)>>1;
	static hashlst arr[2][D][D];
	getlst(arr[0],l,m,stkl);
	reverse(s+m+1,s+r+1);
	getlst(arr[1],m+1,r,stkr);
	reverse(s+m+1,s+r+1);
	for(int i=0;i<D;i++){
		for(int j=0;j<D;j++){
			if(i!=j){
				put_ans(arr[0][i][j],arr[1][j][i]);
			}
		}
	}
	for(int i=r;i>m;i--){
		stkr.psh(s[i]-'a');
	}
	solve(l,m);
	for(int i=m+1;i<=r;i++){
		stkr.psh(s[i]-'a');
	}
	for(int i=l;i<=m;i++){
		stkl.psh(s[i]-'a');
	}
	solve(m+1,r);
	for(int i=m;i>=l;i--){
		stkl.psh(s[i]-'a');
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("swap.in","r",stdin);
	freopen("swap.out","w",stdout);
#endif
	scanf("%s",s+1);
	const int n=strlen(s+1);
	hashutil::main(n);
	stkl.init(),stkr.init();
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
