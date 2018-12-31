#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long double db;
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=1010;
const db EPS=1e-9;
inline bool isz(db x){
	return x>=-EPS&&x<=EPS;
}
struct Pt{
	lint x,y;
	inline lint d2()const{return sqr(x)+sqr(y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
}pt[N];
Pt b,c;
int lst1[N],lst2[N];
inline db calc_x(const Pt &p){//cout
	db mx=(db)(b.x+c.x)/2,my=(db)(b.y+c.y)/2;
	db t2=sqr(b.x-mx)+sqr(b.y-my);
	db t=sqrt(t2);
	db x=((p.x-mx)*(b.y-my)-(p.y-my)*(b.x-mx))/t;
	db y=((p.x-mx)*(b.x-mx)+(p.y-my)*(b.y-my))/t;
	return x/2+(sqr(y)-t2)/(x*2);
}
inline bool cmp_circ(int a1,int a2){
	return calc_x(pt[a1])+EPS<calc_x(pt[a2]);
}
inline bool on_circ(int a1,int a2){
	return isz(calc_x(pt[a1])-calc_x(pt[a2]));
}
inline bool in_circ(int a1,int a2){
	return calc_x(pt[a2])+EPS>calc_x(pt[a1]);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	lint ans=0;
	for(int x=1;x<=n;x++){
		for(int y=1;y<x;y++){
			b=pt[x],c=pt[y];
			int ls1=0,ls2=0;
			for(int k=1;k<=n;k++){
				if(x!=k&&y!=k){
					if(crs(b-c,pt[k]-c)<0){
						lst1[++ls1]=k;
					}else{
						lst2[++ls2]=k;
					}
				}
			}
			swap(b,c),sort(lst2+1,lst2+ls2+1,cmp_circ);
			swap(b,c),sort(lst1+1,lst1+ls1+1,cmp_circ);
			for(int i=1,j=ls2,j2=j;i<=ls1;i++){
				for(;j>=1&&!in_circ(lst1[i],lst2[j]);j--);
				for(apmin(j2,j);j2>=1&&on_circ(lst1[i],lst2[j2]);j2--);
				ans+=4+j+j2;
			}
			swap(b,c);
			for(int i=1,j=ls1,j2=j;i<=ls2;i++){
				for(;j>=1&&!in_circ(lst2[i],lst1[j]);j--);
				for(apmin(j2,j);j2>=1&&on_circ(lst2[i],lst1[j2]);j2--);
				ans+=4+j+j2;
			}
		}
	}
	ans*=2;//swap b,c
	printf("%lld\n",ans);
	return 0;
}
