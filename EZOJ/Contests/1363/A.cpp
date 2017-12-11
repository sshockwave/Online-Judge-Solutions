#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=30010,M=33,O=998244353;
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
int fac[N],invfac[N];
inline int C(int n,int k){
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
int stir[M<<1][M<<1],f[2][M<<1];
inline void gstir(int n){
	memset(stir,0,sizeof(stir));
	stir[0][0]=1;
	for(int i=1,ti=n<<1;i<=ti;i++){
		for(int j=1;j<=i;j++){
			stir[i][j]=((lint)j*stir[i-1][j]%O+stir[i-1][j-1])%O;
		}
	}
	for(int d=0;d<2;d++,n<<=1){
		for(int i=0;i<=n;i++){
			lint tmp=0;
			for(int j=i;j<=n;j++){//j in the front
				tmp+=(lint)C(n,j)*stir[j][i]%O;
			}
			f[d][i]=tmp%O;
		}
	}
}
namespace poly{
	const int SH=16,N=1<<SH;
	int sh,n,invn,mxn=0;
	int o[SH][N>>1],io[SH][N>>1];
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
	inline void ntt(vector<int>&a,int d=1){
		a.resize(n);
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
					a[k+half]=(p-q+O)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
int n,m,a[N];
struct state{
	vector<int>a,b;
	inline void ntt(int d=1){
		poly::ntt(a,d),poly::ntt(b,d);
	}
	inline friend ostream & operator << (ostream & out,state &b){
		out<<"[";
		for(int i=0;i<b.a.size();i++){
			out<<b.a[i]<<"+";
		}
		if(b.a.size()){
			out<<"\b";
		}
		out<<",";
		for(int i=0;i<b.b.size();i++){
			out<<b.b[i]<<"+";
		}
		if(b.b.size()){
			out<<"\b";
		}
		out<<"]";
		return out;
	}
};
state solve(int l,int r){
	if(l==r){
		state ans;
		for(int i=0,p=1;i<=m;i++){
			p=(lint)p*a[l]%O;
			ans.a.push_back((lint)f[0][i]*p%O);
		}
		if(m>n-2){
			ans.a.resize(n-1);
		}
		for(int i=0,p=1,ti=m<<1;i<=ti;i++){
			p=(lint)p*a[l]%O;
			ans.b.push_back((lint)f[1][i]*p%O);
		}
		if((m<<1)>n-2){
			ans.b.resize(n-1);
		}
		return ans;
	}
	int md=(l+r)>>1;
	state lson=solve(l,md),rson=solve(md+1,r);
	int pn=max(lson.a.size()+rson.b.size(),lson.b.size()+rson.a.size())-1;
	int lena=min(n-2,int(lson.a.size()+rson.a.size()-2));
	int lenb=min(n-2,pn-1);
	poly::init(pn);
	lson.ntt(),rson.ntt();
	for(int i=0;i<poly::n;i++){
		lson.b[i]=((lint)lson.a[i]*rson.b[i]%O+(lint)lson.b[i]*rson.a[i]%O)%O;
		lson.a[i]=(lint)lson.a[i]*rson.a[i]%O;
	}
	lson.ntt(-1);
	lson.a.resize(lena+1),lson.b.resize(lenb+1);
	return lson;
}
inline int Main(){
	n=ni,m=ni;
	gmath(max(n,m<<1)),gstir(m),poly::init(((n-2)<<1)+1);
	int sum=0;
	for(int i=1;i<=n;i++){
		(sum+=a[i]=ni)%=O;
	}
	state c=solve(1,n);
	lint ans=0;
	for(int i=0;i<=n-2;i++){
		ans+=(lint)c.b[i]*fpow(sum,n-2-i)%O*invfac[n-2-i]%O;
	}
	return ans%O*fac[n-2]%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
