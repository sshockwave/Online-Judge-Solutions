#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=210,O=1000000007;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
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
inline int _n1(int n){
	return ((lint)n*(n+1)>>1)%O;
}
inline int _n2(int n){
	const static int inv6=inv_pow(6);
	return (lint)n*(n+1)%O*(2*n+1)%O*inv6%O;
}
struct Pt{
	int x,y;
}pt[N];
int a[N],d;
int xcor[N],ycor[N];
lint mat[N][N];
inline int calc_mid_max(const int len,lint a,lint b){
	if(d==0)return len;
	return min<lint>(len,max(0ll,((lint)d*len+d+b-a)/(d<<1)));
}
inline int calc_mid_min(const int len,lint a,lint b){
	return len-calc_mid_max(len,b,a);
}
inline int calc_tri(const int n,lint v){
	if(n==0)return 0;
	lint ans=(lint)(v+(O-d)*2)%O*_n1(n)%O;
	const static int inv2=inv_pow(2);
	ans+=((lint)(n+1+inv2)*_n1(n)+(lint)(O-inv2)*_n2(n))%O*d%O;
	return ans%O;
}
inline int calc_rec(const int r,const int c,lint v){
	if(r==0||c==0)return 0;
	return ((lint)v%O*r%O*c%O+((lint)c*_n1(r-1)+(lint)r*_n1(c-1))%O*d)%O;
}
inline int calc_round(int r,int c,int h,lint v){
	if(r==0||c==0||h==0)return 0;
	//border: x==r,y==c,x+y==h
	apmin(r,h),apmin(c,h),apmin(h,r+c-1);
	const int p=r+c-h;
	lint ans=0;
	ans+=calc_tri(p,v+(lint)(r-p+c-p)*d);
	ans+=calc_rec(r,c-p,v);
	ans+=calc_rec(r-p,p,v+(lint)(c-p)*d);
	return ans%O;
}
inline int solve(const int r,const int c,lint lu,lint ru,lint ld,lint rd){
	//priority: lu>ru>ld>rd
	const int s1=calc_mid_max(c,lu,ru);
	const int s2=calc_mid_max(r,lu,ld);
	const int s3=calc_mid_max(r,ru,rd);
	const int s4=calc_mid_max(c,ld,rd);
	const int s5=calc_mid_max(r+c-1,lu,rd);
	const int s6=calc_mid_min(r+c-1,ld,ru);
	lint ans=0;
	ans+=calc_round(s2,s1,s5,lu);
	ans+=calc_round(s3,c-s1,r+c-1-s6,ru);
	ans+=calc_round(r-s2,s4,s6,ld);
	ans+=calc_round(r-s3,c-s4,r+c-1-s5,rd);
	return ans%O;
}
inline void Main(){
	const int r=ni,c=ni,n=ni;
	d=ni;
	xcor[0]=0,ycor[0]=0;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){xcor[i]=ni-1,ycor[i]=ni-1};
		a[i]=ni;
	}
	xcor[n+1]=r,ycor[n+1]=c;
	sort(xcor,xcor+n+2);
	sort(ycor,ycor+n+2);
	const int xs=unique(xcor,xcor+n+2)-xcor-1;
	const int ys=unique(ycor,ycor+n+2)-ycor-1;
	for(int i=0;i<=xs;i++){
		for(int j=0;j<=ys;j++){
			mat[i][j]=LINF;
		}
	}
	for(int i=1;i<=n;i++){
		pt[i].x=lower_bound(xcor,xcor+xs+1,pt[i].x)-xcor;
		pt[i].y=lower_bound(ycor,ycor+ys+1,pt[i].y)-ycor;
		apmin(mat[pt[i].x][pt[i].y],a[i]);
	}
	for(int i=0;i<=xs;i++){
		for(int j=1;j<=ys;j++){
			if(mat[i][j-1]<LINF){
				apmin(mat[i][j],mat[i][j-1]+(lint)d*(ycor[j]-ycor[j-1]));
			}
		}
		for(int j=ys-1;j>=0;j--){
			if(mat[i][j+1]<LINF){
				apmin(mat[i][j],mat[i][j+1]+(lint)d*(ycor[j+1]-ycor[j]));
			}
		}
	}
	for(int j=0;j<=ys;j++){
		for(int i=1;i<=xs;i++){
			if(mat[i-1][j]<LINF){
				apmin(mat[i][j],mat[i-1][j]+(lint)d*(xcor[i]-xcor[i-1]));
			}
		}
		for(int i=xs-1;i>=0;i--){
			if(mat[i+1][j]<LINF){
				apmin(mat[i][j],mat[i+1][j]+(lint)d*(xcor[i+1]-xcor[i]));
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(mat[pt[i].x][pt[i].y]<a[i]){
			puts("IMPOSSIBLE");
			return;
		}
	}
	lint ans=0;
	for(int i=0;i<xs;i++){
		for(int j=0;j<ys;j++){
			const lint lu=mat[i][j];
			const lint ru=mat[i][j+1]+d;
			const lint ld=mat[i+1][j]+d;
			const lint rd=mat[i+1][j+1]+d*2;
			ans+=solve(xcor[i+1]-xcor[i],ycor[j+1]-ycor[j],lu,ru,ld,rd);
		}
	}
	printf("%lld\n",ans%O);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("geographer.in","r",stdin);
	freopen("geographer.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
