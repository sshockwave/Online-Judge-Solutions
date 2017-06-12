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
const int SHIFT=20,N=1<<SHIFT,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
namespace NTT{
	int n=1,shift=0,revn;
	int omega[SHIFT][N],rev[N];
	inline void init(int tmpn){
		for(tmpn<<=1;n<tmpn;n<<=1,shift++);
		revn=fpow(n,MOD-2);
		rev[0]=0;
		for(int i=1,s=1<<(shift-1);i<n;i++){
			rev[i]=rev[i>>1]>>1;
			if(i&1){
				rev[i]|=s;
			}
		}
	}
	inline void work(int a[],int d){
		for(int i=0;i<n;i++){
			if(rev[i]<i){
				swap(a[rev[i]],a[i]);
			}
		}
		for(int i=1;i<=shift;i++){
			int full=1<<i,half=full>>1,wn=fpow(3,(MOD-1)/full*(d==1?1:(full-1)));
			for(int j=0,w=1;j<half;j++,w=mul(w,wn)){
				for(int k=j;k<n;k+=full){
					int p=a[k],q=mul(a[k+half],w);
					a[k]=add(p,q);
					a[k+half]=sub(p,q);
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=mul(a[i],revn);
			}
		}
	}
}
int x[N],y[N];
int main(){
	int n=ni;
	ni;
	for(int i=0;i<n;i++){
		x[i]=ni;
	}
	for(int i=0;i<n;i++){
		y[i]=ni;
	}
	lint ans=0;
	{
		int sum=0;
		for(int i=0;i<n;i++){
			sum+=x[i]-y[i];
		}
		lint c=-sum/n;
		ans=n*c*c+2*sum*c;
		c--,apmin(ans,(n*c+2*sum)*c);
		c+=2,apmin(ans,(n*c+2*sum)*c);
		for(int i=0;i<n;i++){
			ans+=(lint)x[i]*x[i]+(lint)y[i]*y[i];
		}
	}
	{
		for(int i=0,j=n-1;i<j;i++,j--){
			swap(y[i],y[j]);
		}
		lint tmp=0;
		NTT::init(n);
		NTT::work(x,1),NTT::work(y,1);
		for(int i=0;i<NTT::n;i++){
			x[i]=mul(x[i],y[i]);
		}
		NTT::work(x,-1);
		memset(y,0,sizeof(y));
		for(int i=0;i<NTT::n;i++){
			y[i%n]+=x[i];
		}
		for(int i=0;i<n;i++){
			apmax(tmp,y[i]);
		}
		ans-=tmp*2;
	}
	printf("%lld\n",ans);
}