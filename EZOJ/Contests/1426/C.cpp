#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=100010,rtN=1010;
int n,rt,p;
int a[N];
int lst[N];
bool pre[2][N];//pre lst
int dt[N];
inline bool lcmp(int x,int y){
	return a[x]<a[y];
}
int tmplst1[N],tmplst2[N],tmplst3[N];
inline void addv(int b,int ll,int rr,int v){//[ll,rr]
	int lend=b*rt,rend=min(lend+rt,n);
	if(ll==lend&&rr==rend-1){
		dt[b]=(dt[b]+v)%(p+1);
		return;
	}
	int ls1=0,ls2=0,ls3=0;
	for(int i=lend;i<rend;i++){
		int x=lst[i];
		if(ll<=x&&x<=rr){
			a[x]+=v;
			if(a[x]<=p){
				tmplst1[ls1++]=x;
			}else{
				a[x]-=p+1;
				tmplst2[ls2++]=x;
			}
		}else{
			tmplst3[ls3++]=x;
		}
	}
	for(int i=0;i<ls1;i++){
		tmplst2[ls2++]=tmplst1[i];
	}
	//merge tmplst2 && tmplst3
	int qt2=0,qt3=0;
	for(int i=lend,p0=0,p1=0;i<rend;i++){
		if(qt3==ls3||(qt2<ls2&&a[tmplst2[qt2]]<a[tmplst3[qt3]])){
			lst[i]=tmplst2[qt2++];
		}else{
			lst[i]=tmplst3[qt3++];
		}
		(a[lst[i]]&1?p1:p0)^=1;
		pre[0][i]=p0,pre[1][i]=p1;
	}
}
inline void addv(int l,int r,int v){
	int bl=l/rt,br=r/rt;
	if(bl==br)return addv(bl,l,r,v);
	addv(bl,l,bl*rt+rt-1,v);
	for(int i=bl+1;i<br;i++){
		dt[i]=(dt[i]+v)%(p+1);
	}
	addv(br,br*rt,r,v);
}
inline int ev(int x){
	return x&1?1:x==p?2:0;
}
inline bool ask(int l,int r){
	int bl=l/rt,br=r/rt;
	int ans=0;
	if(bl==br){
		for(int i=l;i<=r;i++){
			ans^=ev((a[i]+dt[bl])%(p+1));
		}
		return ans;
	}
	for(int i=l,ti=bl*rt+rt;i<ti;i++){
		ans^=ev((a[i]+dt[bl])%(p+1));
	}
	for(int b=bl+1;b<br;b++){
		int lend=b*rt,rend=lend+rt-1;
		if(p&1){
			ans^=pre[(dt[b]&1)^1][rend];
			continue;
		}
		assert(rend<=n);
		int m1,m2;//a[lst[m1,m2]]==p
		{//get m1
			int l=lend,r=rend+1;
			while(l<r){
				m1=(l+r)>>1;
				if(a[lst[m1]]+dt[b]>=p){
					r=m1;
				}else{
					l=m1+1;
				}
			}
			m1=l;
		}
		{//get m2
			int l=m1-1,r=rend;
			while(l<r){
				m2=((l+r)>>1)+1;
				if(a[lst[m2]]+dt[b]<=p){
					l=m2;
				}else{
					r=m2-1;
				}
			}
			m2=l;
		}
		if(lend<m1){
			ans^=pre[(dt[b]&1)^1][m1-1];
		}
		if(m1<=m2&&((m2-m1+1)&1)){
			ans^=2;
		}
		if(m2<rend){
			if(lend<=m2){
				ans^=pre[dt[b]&1][m2];
			}
			ans^=pre[dt[b]&1][rend];
		}
	}
	for(int i=br*rt;i<=r;i++){
		ans^=ev((a[i]+dt[br])%(p+1));
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("right.in","r",stdin);
	freopen("right.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	rt=max<int>(sqrt(n*log(n))*0.4,3);
	p=ni;
	for(int i=0;i<n;i++){
		a[i]=ni%(p+1);
		lst[i]=i;
	}
	for(int b=0;b<=(n-1)/rt;b++){
		int l=b*rt,r=min(l+rt,n);
		sort(lst+l,lst+r,lcmp);
		for(int i=l,p0=0,p1=0;i<r;i++){
			(a[lst[i]]&1?p1:p0)^=1;
			pre[0][i]=p0,pre[1][i]=p1;
		}
	}
	while(tot--){
		int tp=ni,l=ni-1,r=ni-1;
		if(tp){//ask
			putchar('0'+ask(l,r));
			putchar('\n');
		}else{//add
			addv(l,r,ni%(p+1));
		}
	}
	return 0;
}
