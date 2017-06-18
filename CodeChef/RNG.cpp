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
const int SHIFT=16,N=1<<SHIFT,MOD=104857601;
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
inline void apsub(int &a,const int &b){
	a=sub(a,b);
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
inline int shifter(int n){
	int cnt=0;
	for(;(1<<cnt)<n;cnt++);
	return cnt;
}
inline void ntt(int a[],int shift,int d){
	int n=1<<shift;
	assert(n<=N);
	static int *rev=new int[N];
	rev[0]=0;
	for(int i=1,s=1<<(shift-1);i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=s;
		}
		if(rev[i]<i){
			swap(a[rev[i]],a[i]);
		}
	}
	for(int i=1;i<=shift;i++){
		int full=1<<i,half=full>>1;
		for(int j=0;j<half;j++){
			int w=fpow(3,(MOD-1+(MOD-1)/full*j*d)%(MOD-1));
			assert(fpow(w,full)==1);
			for(int k=j;k<n;k+=full){
				int p=a[k],q=mul(a[k+half],w);
				a[k]=add(p,q),a[k+half]=sub(p,q);
			}
		}
	}
	if(d==-1){
		int rev=fpow(n,MOD-2);
		for(int i=0;i<n;i++){
			apmul(a[i],rev);
		}
	}
}
struct Poly{
	int *a,n,shift;
	bool flag;
	Poly(int _a[]):a(_a),flag(false){}
	~Poly(){
		delete[] a;
	}
	inline int& operator [] (int i){
		return a[i];
	}
	inline void set(int s){
		shift=s,n=1<<s;
	}
	inline void clr(int n){
		memset(a+n,0,(this->n-n)<<2);
	}
	inline void dft(){
		ntt(a,shift,flag?-1:1);
		flag=!flag;
	}
	inline friend ostream & operator << (ostream & out,const Poly &p){
		for(int i=0;i<p.n;i++){
			out<<p.a[i]<<" ";
		}
		return out;
	}
	void rev(int arr[],int n){//store in a
		if(n==1){
			//for this problem
			assert(a[0]==1);
			arr[0]=1;
			return;
		}
		int na=(n>>1)+(n&1),nb=n;
		rev(arr,na);
		static Poly b(new int[N]);
		for(int i=0;i<n;i++){
			b[i]=arr[i];
		}
		while(a[--na]==0);
		while(b[--nb]==0);
		set(shifter(na+nb+1));
		b.set(shift);
		clr(na+1),b.clr(nb+1);
		dft(),b.dft();
		for(int i=0;i<this->n;i++){
			a[i]=sub(mul(a[i],2),mul(b[i],mul(a[i],a[i])));
		}
		dft();
	}
	inline void mod(int);
}M(new int[N]),P(new int[N]),C(new int[N]);
inline void Poly::mod(int n){//a-R(R(a)*P)*M
	static Poly q(new int[N]);
	for(int i=0,j=(n<<1)-2;i<n-1;i++){
		q[i]=a[j];
	}
	q.set(P.shift);
	q.dft();
	assert(q.flag&&P.flag);
	for(int i=0;i<q.n;i++){
		apmul(q[i],P[i]);
	}
	q.dft();
	for(int i=n-1;i<q.n;i++){
		assert(q[i]==0);
	}
	for(int i=0,j=n-2;i<j;i++,j--){
		swap(q[i],q[j]);
	}
	q.set(M.shift);
	q.dft();
	assert(q.flag&&M.flag);
	for(int i=0;i<q.n;i++){
		apmul(q[i],M[i]);
	}
	q.dft();
	for(int i=0;i<n;i++){
		apsub(a[i],q[i]);
	}
	for(int i=n;i<this->n;i++){
		assert(a[i]==q[i]);
	}
	clr(n);
}
int n;
inline void fpow(Poly x,lint t){
	if(t==0){
		memset(x.a,0,N<<2);
		x[1]=1;
		return;
	}
	fpow(x,t>>1);
	x.set(shifter(n));
	x.dft();
	assert(x.flag);
	for(int i=0;i<x.n;i++){
		apmul(x[i],x[i]);
	}
	x.dft(),x.mod(n);
	if(n&1){
		for(int i=n;i>=1;i--){
			x[i]=x[i-1];
		}
		x[0]=0;
		for(int i=0;i<n;i++){
			apsub(x[i],mul(x[n],C[i]));
		}
		x[n]=0;
	}
}
int a[N];
int main(){
	n=ni;
	lint t=nl-1;
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	if(t<n){
		printf("%d\n",a[t]);
		return 0;
	}
	memset(M.a,0,N<<2);
	M[n]=C[n]=1;
	for(int i=1;i<=n;i++){
		M[n]=C[n]=sub(0,ni);
	}
	M.set(shifter((n<<1)-1));
	M.dft();
	{
		int *a=new int[N];
		for(int i=0;i<=n;i++){
			a[i]=C[n-i];
		}
		P.rev(a,n-1);
		P.set(shifter((n<<1)-3));
		P.dft();
		delete[] a;
	}
	Poly s(new int[N]);
	fpow(s,t);
	int ans=0;
	for(int i=0;i<n;i++){
		apadd(ans,mul(s[i],a[i]));
	}
	printf("%d\n",ans);
}