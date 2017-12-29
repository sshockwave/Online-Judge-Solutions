#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
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
template<class T>T gcd(T a,T b){
	return b?gcd(b,a%b):a;
}
lint O;
struct Mat{
	const static int D=4;
	int a[D][D];
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=0;i<D;i++){
			for(int j=0;j<D;j++){
				lint tmp=0;
				for(int k=0;k<D;k++){
					tmp+=(lint)x.a[i][k]*y.a[k][j]%O;
				}
				a[i][j]=tmp%O;
			}
		}
	}
}trans=(Mat){1,0,1,0,0,1,0,1,1,0,0,0,0,1,0,0},res;
inline void fpow(lint n){
	if(n==0){
		res=(Mat){1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
		return;
	}
	fpow(n>>1);
	Mat tmp;
	tmp.gmul(res,res);
	res=tmp;
	if(n&1){
		tmp.gmul(res,trans);
		res=tmp;
	}
}
inline void ex_gcd(lint a,lint b,lint &x,lint &y){
	if(b){
		ex_gcd(b,a%b,y,x);
		y-=x*(a/b);
	}else{
		x=1,y=0;
	}
}
inline lint gsol(lint x,lint d,lint n){
	if(n<0)return 0;
	x=(x%d+d)%d;
	//first is x
	if(n<x)return 0;
	return (n-x)/d+1;
}
inline lint Main(){
	lint a1=nl,l=nl,r=nl,n=nl;
	O=nl;
	lint m=nl;
	a1%=O;
	lint p,q;
	if(n==1){
		p=a1,q=0;
	}else if(n==2){
		p=0,q=1;
	}else{
		fpow(n-2);
		p=(res.a[0][2]*a1%O+res.a[0][1])%O;
		q=(res.a[1][2]*a1%O+res.a[1][1])%O;
	}
	m=((m-p)%O+O)%O;
	lint d=gcd(O,q);
	if(m%d!=0)return 0;
	lint abc=m/d;
	m/=d;
	lint x,y;
	ex_gcd(q,O,x,y);
	x*=abc,y*=abc;
	//x+kd is the solution
	return gsol(x,O/d,r)-gsol(x,O/d,l-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("solve2.in","r",stdin);
	freopen("solve2.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
