#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=40010,logN=18;
const db DINF=1e100L,EPS=1e-4;
struct Pt{
	db x,y;
	inline db d2()const{return sqr(x)+sqr(y);}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend db crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
	inline friend bool turn_left(const Pt &a,const Pt &b,const Pt &c){
		return crs(b-a,c-b)>0;
	}
	inline int quad()const{
		if(x>0&&y>=0)return 1;
		if(x<=0&&y>0)return 2;
		if(x<0&&y<=0)return 3;
		if(x>=0&&y<0)return 4;
		assert(x==0&&y==0);
		return 0;
	}
}pt[N],cut[N];
inline bool polar_cmp(const Pt &a,const Pt &b){
	const int qa=a.quad(),qb=b.quad();
	if(qa!=qb)return qa<qb;
	const db c=crs(a,b);
	if(c)return c>0;
	return a.d2()<b.d2();
}
int f[N][logN];
int lst[N];
inline bool lst_cmp(int a,int b){
	return polar_cmp(cut[a],cut[b]);
}
inline int calc(const int n,const db r){
	for(int i=0;i<n;i++){
		const db d=sqrtl(pt[i].d2());
		const db a=r/d*r;
		const db b=sqrtl(r*r-a*a);
		const db ux=pt[i].x/d,uy=pt[i].y/d;
		cut[i]=(Pt){ux*a-uy*b,uy*a+ux*b};
	}
	sort(lst,lst+n,lst_cmp);
	for(int i=0,j=0;i<n;i++){
		const Pt &p=pt[lst[i]];
		const Pt &c=cut[lst[i]];
		apmax(j,i+1);
		for(int t;t=lst[j%n],t!=lst[i]&&crs(p-c,pt[t]-c)>=0;j++);
		f[i][0]=j-i;
	}
	int hb=0;
	for(;(1<<hb)<n;hb++);
	for(int j=0;j<hb;j++){
		for(int i=0;i<n;i++){
			f[i][j+1]=f[i][j]+f[(i+f[i][j])%n][j];
		}
	}
	int ans=n;
	for(int i=0;i<n;i++){
		int x=i,t=i+n;
		int cur=0;
		for(int j=hb;j>=0;j--){
			if(x+f[x%n][j]<t){
				cur|=1<<j;
				x+=f[x%n][j];
			}
		}
		assert(x+f[x%n][0]>=t);
		apmin(ans,cur+1);
	}
	return ans;
}
inline db Main(){
	const int n=ni,lim=ni;
	db l=0,r=DINF;
	for(int i=0;i<n;i++){
		pt[i]=(Pt){(db)ni,(db)ni};
		apmin(r,sqrtl(pt[i].d2()));
		lst[i]=i;
	}
	if(lim>=n)return r;
	for(;r-l>EPS;){
		const db m=(l+r)/2;
		(calc(n,m)<=lim?l:r)=m;
	}
	return (l+r)/2;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("board.in","r",stdin);
	freopen("board.out","w",stdout);
#endif
	printf("%.2f\n",(double)Main());
	return 0;
}
