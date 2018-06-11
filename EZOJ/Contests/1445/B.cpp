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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=1010,O=1000000007;
int m;
namespace gmath{
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
	int fac[N],invfac[N];
	int _goC[N][N];
	inline int C(int n,int k){
		assert(k<=n);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
	inline void main(int n=N-1){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv_pow(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				if(((i^j^m)&1)||i+j>m){
					_goC[i][j]=0;
					continue;
				}
				const int r=(m-i-j)>>1;
				_goC[i][j]=(lint)C(m,r)*C(m,i+r)%O;
			}
		}
	}
	inline int goC(int x,int y){
		return _goC[cabs(x)][cabs(y)];
	}
}
struct Rng{
	int a,b,c,d;
	//y in x+[a,b]
	//y in -x+[c,d]
	inline friend Rng operator & (const Rng &a,const Rng &b){
		return (Rng){max(a.a,b.a),min(a.b,b.b),max(a.c,b.c),min(a.d,b.d)};
	}
	inline friend Rng operator | (const Rng &a,const Rng &b){
		return (Rng){min(a.a,b.a),max(a.b,b.b),min(a.c,b.c),max(a.d,b.d)};
	}
	inline bool ok(){
		return a<=b&&c<=d;
	}
};
struct Pt{
	int x,y;
	inline int tp(){
		return cabs(x+y)&1;
	}
	inline Rng rng(){
		return (Rng){y-m-x,y+m-x,y-m+x,y+m+x};
	}
	inline bool in(const Rng &r)const{
		return x+r.a<=y&&y<=x+r.b&&-x+r.c<=y&&y<=-x+r.d;
	}
}pt[N];
inline int Main(){
	const int p3=ni,p1=ni,p2=ni+p1,n=p3;
	m=ni;
	gmath::main();
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	int mxx=pt[1].x,mnx=pt[1].x;
	int mxy=pt[1].y,mny=pt[1].y;
	for(int i=1;i<=n;i++){
		apmax(mxx,pt[i].x);
		apmin(mnx,pt[i].x);
		apmax(mxy,pt[i].y);
		apmin(mny,pt[i].y);
	}
	Rng r1=pt[p1].rng(),r2=pt[p2].rng(),r3=pt[p3].rng();
	for(int i=1;i<=p1;i++){
		if(pt[p1].tp()^pt[i].tp())return 0;
		r1=r1&pt[i].rng();
	}
	for(int i=p1+1;i<=p2;i++){
		if(pt[p2].tp()^pt[i].tp())return 0;
		r2=r2&pt[i].rng();
	}
	for(int i=p2+1;i<=p3;i++){
		if(pt[p3].tp()^pt[i].tp())return 0;
		r3=r3&pt[i].rng();
	}
	if(!r1.ok())return 0;
	if(!r2.ok())return 0;
	if(!r3.ok())return 0;
	lint a=0,b=0,c=0,ab=0,bc=0,ca=0,abc=0;
	for(int i=mnx-m;i<=mxx+m;i++){
		for(int j=mny-m;j<=mxy+m;j++){
			lint cura=1;
			lint curb=1;
			lint curc=1;
			const Pt cur=(Pt){i,j};
			const int tp=((Pt){i+m,j}).tp();
			if(pt[p1].tp()==tp&&cur.in(r1)){
				for(int k=1;k<=p1;k++){
					cura=cura*gmath::goC(i-pt[k].x,j-pt[k].y)%O;
				}
			}else{
				cura=0;
			}
			if(pt[p2].tp()==tp&&cur.in(r2)){
				for(int k=p1+1;k<=p2;k++){
					curb=curb*gmath::goC(i-pt[k].x,j-pt[k].y)%O;
				}
			}else{
				curb=0;
			}
			if(pt[p3].tp()==tp&&cur.in(r3)){
				for(int k=p2+1;k<=p3;k++){
					curc=curc*gmath::goC(i-pt[k].x,j-pt[k].y)%O;
				}
			}else{
				curc=0;
			}
			a+=cura,b+=curb,c+=curc;
			ab+=(lint)cura*curb%O;
			bc+=(lint)curb*curc%O;
			ca+=(lint)curc*cura%O;
			abc+=(lint)cura*curb%O*curc%O;
		}
	}
	a%=O,b%=O,c%=O,ab%=O,bc%=O,ca%=O,abc%=O;
	lint ans=a*b%O*c%O-ab*c%O-bc*a%O-ca*b%O+2*abc;
	return (ans%O+O)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dark.in","r",stdin);
	freopen("dark.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
