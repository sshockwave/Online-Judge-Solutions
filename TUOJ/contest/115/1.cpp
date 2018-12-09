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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,D=2;
struct Pt{
	lint x,y;
}intv[N],pt[N];
bool any[N];
struct Line{
	lint k,b;
	inline friend bool operator < (const Line &a,const Line &b){
		return a.k<b.k;
	}
	inline lint operator () (lint x)const{
		return k*x+b;
	}
};
//x1=(b.b-a.b)/(a.k-b.k)
//x2=(c.b-a.b)/(a.k-c.k)
inline bool turn_right(Line a,Line b,Line c){
	return (b.b-a.b)*(a.k-c.k)<(c.b-a.b)*(a.k-b.k);
}
Line lst[N],stk[N];
void solve(const int l,const int r){
	if(l==r)return;
	const int m=(l+r)>>1;
	solve(l,m),solve(m+1,r);
	{//for l
		int ss=0;
		for(int i=m+1;i<=r;i++){
			lst[i].k=2*intv[i].x;
			lst[i].b=pt[i-1].y-lst[i].k*pt[i-1].x;
		}
		sort(lst+m+1,lst+r+1);
		for(int i=r;i>m;i--){
			Line cur=lst[i];
			if(ss&&stk[ss].k==cur.k){
				apmin(cur.b,stk[ss--].b);
			}
			for(;ss>=2&&!turn_right(stk[ss-1],stk[ss],cur);ss--);
			stk[++ss]=cur;
		}
		for(int i=l;i<=m;i++){
			if(any[i])continue;
			int l=1,r=ss;
			const Pt cur=pt[i-1];
			for(;l<r;){
				const int m=(l+r)>>1;
				if(stk[m](cur.x)<stk[m+1](cur.x)){
					r=m;
				}else{
					l=m+1;
				}
			}
			any[i]=stk[l](cur.x)<cur.y;
		}
	}
	{//for r
		int ss=0;
		for(int i=m+1;i<=r;i++){
			lst[i].k=2*intv[i].y;
			lst[i].b=pt[i-1].y-lst[i].k*pt[i-1].x;
		}
		sort(lst+m+1,lst+r+1);
		for(int i=m+1;i<=r;i++){
			Line cur=lst[i];
			if(ss&&stk[ss].k==cur.k){
				apmax(cur.b,stk[ss--].b);
			}
			for(;ss>=2&&!turn_right(stk[ss-1],stk[ss],cur);ss--);
			stk[++ss]=cur;
		}
		for(int i=l;i<=m;i++){
			if(any[i])continue;
			int l=1,r=ss;
			const Pt cur=pt[i-1];
			for(;l<r;){
				const int m=(l+r)>>1;
				if(stk[m](cur.x)>stk[m+1](cur.x)){
					r=m;
				}else{
					l=m+1;
				}
			}
			any[i]=stk[l](cur.x)>cur.y;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	pt[0].x=pt[0].y=0;
	for(int i=1;i<=n;i++){
		intv[i]=(Pt){ni,ni};
		lint mass=intv[i].y-intv[i].x;
		pt[i].x=pt[i-1].x+mass;
		pt[i].y=pt[i-1].y+mass*(intv[i].x+intv[i].y);
	}
	mset(any+1,0,n);
	solve(1,n);
	int ans=0;
	for(int i=n,j=n+1;i>=1;i--){
		if(!any[i]){
			apmax(ans,j-i);
			j=i;
		}
	}
	printf("%d\n",ans);
	return 0;
}
