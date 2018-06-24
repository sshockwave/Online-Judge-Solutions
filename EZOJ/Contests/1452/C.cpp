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
const int N=310,logN=9,O=998244353;
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
namespace gmath{
	int fac[N];
	inline void main(const int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
	}
}
struct Mat{
	int a[N][N];
	int n1,n2;
	inline friend ostream & operator << (ostream & out,const Mat &b){
		for(int i=1;i<=b.n1;i++){
			out<<endl<<"[";
			for(int j=1;j<=b.n2;j++){
				out<<b.a[i][j];
				if(j<b.n2){
					out<<" ";
				}
			}
			out<<"]";
		}
		return out;
	}
	inline void clr(const bool d=0){
		for(int i=1;i<=n1;i++){
			mset(a[i]+1,0,n2);
			a[i][i]=d;
		}
	}
	inline void canon(){
		for(int i=1;i<=n1;i++){
			for(int j=1;j<=n2;j++){
				if(a[i][j]<0){
					a[i][j]=(a[i][j]%O+O)%O;
				}
			}
		}
	}
	inline const Mat& operator = (const Mat &b){
		n1=b.n1,n2=b.n2;
		for(int i=1;i<=n1;i++){
			memcpy(a[i]+1,b.a[i]+1,n2*sizeof(a[i][0]));
		}
		return *this;
	}
	inline void gmul(const Mat &x,const Mat &y){
		assert(x.n2==y.n1);
		n1=x.n1,n2=y.n2;
		for(int i=1;i<=n1;i++){
			for(int j=1;j<=n2;j++){
				int &ans=a[i][j]=0;
				for(int k=1;k<=x.n2;k++){
					ans=(ans+(lint)x.a[i][k]*y.a[k][j])%O;
				}
			}
		}
	}
	inline void lw_swap(const int p,const int q){
		if(p==q)return;
		for(int j=1;j<=n2;j++){
			swap(a[p][j],a[q][j]);
		}
	}
	inline void lw_div(const int i,const int v){
		assert(v);
		if(v==1)return;
		const int iv=inv_pow(v);
		for(int j=1;j<=n2;j++){
			if(a[i][j]){
				a[i][j]=(lint)a[i][j]*iv%O;
			}
		}
	}
	inline void lw_add(const int p,const int q,const int r){
		if(r==0||r==O)return;
		for(int j=1;j<=n2;j++){
			a[q][j]=(a[q][j]+(lint)a[p][j]*r)%O;
		}
	}
	inline const Mat& inv(){
		assert(n1==n2);
		static Mat b;
		const int n=n1;
		b.n1=b.n2=n,b.clr(1);
		for(int i=1;i<=n;i++){
			int j=i;
			for(;j<=n&&a[j][i]==0;j++);
			assert(j<=n);
			b.lw_swap(i,j),lw_swap(i,j);
			b.lw_div(j,a[j][i]),lw_div(j,a[j][i]);
			for(j=1;j<=n;j++){
				if(i!=j&&a[j][i]){
					b.lw_add(i,j,O-a[j][i]),lw_add(i,j,O-a[j][i]);
				}
			}
		}
		return b;
	}
	inline int det(){
		assert(n1==n2);
		const int n=n1;
		int ans=1;
		for(int i=1;i<=n;i++){
			int j=i;
			for(;j<=n&&a[j][i]==0;j++);
			assert(j<=n);
			if(i!=j){
				ans=O-ans;
				lw_swap(i,j);
			}
			if(a[j][i]!=1){
				ans=(lint)ans*a[j][i]%O;
				lw_div(j,a[j][i]);
			}
			for(j=i+1;j<=n;j++){
				lw_add(i,j,O-a[j][i]);
			}
		}
		return ans;
	}
};
int colmat[N][N];
Mat kir;
int oud[N];
int spcnt,pdfac;
inline int gkir(const int x,const int i,const int j){
	return (i!=x)==(j!=x)?kir.a[i][j]:0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	const int n=ni;
	memset(colmat,0,sizeof(colmat));
	mset(oud+1,0,n);
	kir.n1=kir.n2=n,kir.clr();
	for(int tot=ni;tot--;){
		const int x=ni,u=ni,v=ni;
		colmat[u][v]=x;
		++oud[u];
		++kir.a[u][u],--kir.a[u][v];
	}
	kir.canon();
	{//get etcnt
		static Mat tmp;
		tmp=kir;
		--tmp.n1,--tmp.n2;
		spcnt=tmp.det();
		gmath::main(n);
		pdfac=1;
		for(int i=1;i<=n;i++){
			pdfac=(lint)pdfac*gmath::fac[oud[i]-1]%O;
		}
	}
	static Mat v1,iv1;
	{//get v1
		v1=kir;
		for(int i=2;i<=n;i++){
			v1.a[i][1]=0;
		}
		for(int j=2;j<=n;j++){
			v1.a[1][j]=0;
		}
		iv1=v1,iv1=iv1.inv();
	}
	int ans=0;
	for(int x=1;x<=n;x++){
		static Mat vcur,b,c;
		{//get b,c
			b.n1=n,b.n2=4,b.clr();
			c.n1=4,c.n2=n,c.clr();
			b.a[1][1]=1;
			for(int j=1;j<=n;j++){
				c.a[1][j]=(v1.a[1][j]+O-gkir(x,1,j))%O;
			}
			b.a[x][2]=1;
			for(int j=1;j<=n;j++){
				c.a[2][j]=(v1.a[x][j]+O-gkir(x,x,j))%O;
			}
			c.a[3][1]=1;
			for(int i=2;i<=n;i++){//this is 2 so that you won't substract twice
				b.a[i][3]=(v1.a[i][1]+O-gkir(x,i,1))%O;
			}
			c.a[4][x]=1;
			for(int i=1;i<=n;i++){
				b.a[i][4]=(v1.a[i][x]+O-gkir(x,i,x))%O;
			}
		}
		{//get vcur=A^{-1}+A^{-1}B(I-CA^{-1}B)^{-1}CA^{-1}
			static Mat tmp1,tmp2;
			{//tmp1=(I-CA^{-1}B)^{-1}
				tmp2.gmul(c,iv1);
				tmp1.gmul(tmp2,b);
				assert(tmp1.n1==4&&tmp1.n2==4);
				for(int i=1;i<=4;i++){
					for(int j=1;j<=4;j++){
						tmp1.a[i][j]=(O+(i==j)-tmp1.a[i][j])%O;
					}
				}
				tmp1=tmp1.inv();
			}
			tmp2.gmul(b,tmp1);
			tmp1.gmul(iv1,tmp2);
			tmp2.gmul(c,iv1);
			vcur.gmul(tmp1,tmp2);
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					vcur.a[i][j]=(vcur.a[i][j]+iv1.a[i][j])%O;
				}
			}
		}
		int cnt=0;
		lint sum=0;
		for(int i=1;i<=n;i++){
			if(colmat[i][x]==0)continue;
			for(int j=1;j<=n;j++){
				if(colmat[i][x]!=colmat[x][j])continue;
				++cnt,sum+=vcur.a[j][i];
			}
		}
		if(oud[x]==1){
			ans=(ans+(lint)spcnt*cnt%O*pdfac)%O;
		}else{
			ans=(ans+(lint)spcnt*(cnt+O-sum%O)%O*pdfac%O*inv_pow(oud[x]-1))%O;
		}
	}
	printf("%d\n",ans);
	return 0;
}
