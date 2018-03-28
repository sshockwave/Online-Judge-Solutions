#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>
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
const int N=60,O=998244353;
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
namespace gmath{
	int fac[N],invfac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int C(int n,int k){
		assert(k<=n);
		return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
	}
}
struct poly:vector<int>{
	inline void canon(){
		for(;!empty()&&*rbegin()==0;pop_back());
	}
	inline friend poly operator + (const poly &a,const poly &b){
		poly c;
		int sa=a.size(),sb=b.size();
		for(int i=0,ti=min(sa,sb);i<ti;i++){
			c.push_back((a[i]+b[i])%O);
		}
		if(sa>sb){
			for(int i=sb;i<sa;i++){
				c.push_back(a[i]);
			}
		}else if(sb>sa){
			for(int i=sa;i<sb;i++){
				c.push_back(b[i]);
			}
		}
		c.canon();
		return c;
	}
	inline friend poly operator * (const poly &a,const poly &b){
		poly c;
		int sa=a.size(),sb=b.size();
		c.resize(sa+sb-1,0);
		for(int i=0;i<sa;i++){
			int ta=a[i];
			for(int j=0;j<sb;j++){
				int &tc=c[i+j];
				tc=(tc+(lint)ta*b[j])%O;
			}
		}
		c.canon();
		return c;
	}
	inline poly operator () (const poly &x){
		poly f;
		for(int i=size()-1;i>=0;i--){
			f=f*x;
			int v=this->operator[](i);
			if(f.empty()){
				f.push_back(v);
			}else{
				f[0]=(f[0]+v)%O;
			}
		}
		f.canon();
		return f;
	}
	inline void lagrange(const poly &x,const poly &y){
		clear();
		int n=x.size();
		poly prod;
		prod.push_back(1);
		for(int i=0;i<n;i++){
			poly tmp;
			tmp.push_back((O-x[i])%O);
			tmp.push_back(1);
			prod=prod*tmp;
		}
		for(int i=0;i<n;i++){
			lint cur=1;
			for(int j=0;j<n;j++){
				if(i!=j){
					cur=cur*(x[i]+O-x[j])%O;
				}
			}
			cur=(lint)inv(cur)*y[i]%O;
			int r=0;
			assert((int)prod.size()==n+1);
			poly tmp;
			for(int j=n;j>=1;j--){
				r=((lint)r*x[i]+prod[j])%O;
				tmp.push_back(cur*r%O);
			}
			assert(((lint)r*x[i]%O+prod[0])%O==0);
			reverse(tmp.begin(),tmp.end());
			*this=*this+tmp;
		}
	}
};
poly pwsum[N],f[N];
lint a[N];
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
#endif
	int n=ni;
	lint m=next_num<lint>();
	gmath::main(n);
	using gmath::C;
	for(int i=0;i<n;i++){//get pwsum
		poly x,y;
		int cur=0;
		for(int j=0;j<=i+1;j++){
			x.push_back(j);
			y.push_back(cur=(cur+fpow(j,i))%O);
		}
		pwsum[i].lagrange(x,y);
	}
	a[1]=next_num<lint>();//i==1
	f[1].push_back(1);
	for(int i=2;i<=n;i++){
		a[i]=next_num<lint>();
		assert(a[i]%a[i-1]==0);
		int diff=a[i]/a[i-1]%O;
		poly cur2;
		cur2.push_back(m/a[i]%O);
		cur2.push_back(O-1);
		for(int k=0,tk=f[i-1].size();k<tk;k++){
			poly cur;
			for(int j=k;j<tk;j++){
				cur.push_back((lint)f[i-1][j]*fpow(diff,j)%O*C(j,k)%O);
			}
			f[i]=f[i]+cur*pwsum[k](cur2);
		}
	}
	printf("%d\n",f[n][0]);
	return 0;
}
