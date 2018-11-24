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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=152,O=998244353;
int d;
struct Mat{
	int a[N][N];
	inline void id(){
		for(int i=0;i<=d;i++){
			mset(a[i],0,d+1);
			a[i][i]=1;
		}
	}
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=0;i<=d;i++){
			for(int j=0;j<=d;j++){
				lint ans=0;
				for(int k=0;k<=d;k++){
					ans+=(lint)x.a[i][k]*y.a[k][j];
					const static lint OO=0x7f7f7f7f7f7f7f7fll-(lint)O*O;
					if(ans>OO){
						ans%=O;
					}
				}
				a[i][j]=ans%O;
			}
		}
	}
	inline void sh(int t){
		static Mat b;
		b=*this;
		for(int i=0;i<d;i++){
			for(int j=0;j<d;j++){
				a[(i+t)%d][(j+t)%d]=b.a[i][j];
			}
		}
		for(int i=0;i<d;i++){
			a[(i+t)%d][d]=b.a[i][d];
			a[d][(i+t)%d]=b.a[d][i];
		}
		a[d][d]=b.a[d][d];
	}
	inline friend ostream & operator << (ostream & out,const Mat &x){
		for(int i=0;i<=d;i++){
			out<<endl;
			for(int j=0;j<=d;j++){
				out<<x.a[i][j]<<" ";
			}
		}
		return out;
	}
}res;
void fpow(const Mat &x,int n){
	if(n==0)return res.id();
	fpow(x,n>>1);
	static Mat tmp1,tmp2;
	tmp1=res,tmp2=res,tmp2.sh(n>>1);
	res.gmul(tmp1,tmp2);
	if(n&1){
		tmp1=res,tmp2=x,tmp2.sh(n-1);
		res.gmul(tmp1,tmp2);
	}
}
Mat res2;
inline int bitcnt(lint n){
	int a=0;
	for(;n;a+=n%d,n/=d);
	return a;
}
void solve(const Mat &x,lint n){
	if(n==0)return res2.id();
	fpow(x,d);
	Mat &nxt=*(new Mat)=res;
	solve(nxt,n/d);
	delete &nxt;
	static Mat tmp;
	fpow(x,n%d);
	res.sh(bitcnt(n/d));
	tmp=res2;
	res2.gmul(tmp,res);
}
Mat mat;
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	lint n=next_num<lint>();
	d=ni;
	mat.id();
	for(int i=0;i<=d;i++){
		mat.a[0][i]=1;
	}
	solve(mat,n);
	lint ans=0;
	for(int i=0;i<=d;i++){
		ans+=res2.a[i][d];
	}
	printf("%lld\n",ans%O);
	return 0;
}
