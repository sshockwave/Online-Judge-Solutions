#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010;
inline lint c2(lint n){
	return (lint)n*(n+1)/2;
}
int vis[N],tim=0;
struct rho{
	int lst[N],ls;
	int st,len;
	inline int at(lint x){
		return x<st?lst[x]:lst[(x-st)%len+st];
	}
	inline void init(int x,int a,int b,int n){
		ls=0;
		++tim;
		for(;vis[x]<tim;x=((lint)a*x+b)%n){
			lst[++ls]=x;
			vis[x]=tim;
		}
		for(st=1;lst[st]!=x;st++);
		len=ls-st+1;
	}
}a,b;
int n,m;
struct Seats{
	typedef set<int>si;
	si s;
	lint ans;
	Seats(){
		s.insert(-1);
		s.insert(m);
		ans=c2(m);
	}
	inline bool has(int x){
		return s.find(x)!=s.end();
	}
	inline bool ins(int x){
		if(has(x))return false;
		si::iterator it=s.insert(x).first;
		si::iterator pr=it,nx=it;
		--pr,++nx;
		ans-=c2(*nx-*pr-1);
		ans+=c2(x-*pr-1)+c2(*nx-x-1);
		return true;
	}
	inline bool del(int x){
		si::iterator it=s.find(x);
		if(it==s.end())return false;
		si::iterator pr=it,nx=it;
		--pr,++nx;
		ans-=c2(x-*pr-1)+c2(*nx-x-1);
		ans+=c2(*nx-*pr-1);
		s.erase(it);
		return true;
	}
};
bool calc[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	memset(vis,0,sizeof(vis));
	n=ni,m=ni;
	lint k=next_num<lint>();
	{
		const int x1=ni,a1=ni,b1=ni;
		const int x2=ni,a2=ni,b2=ni;
		a.init(x1,a1,b1,n);
		b.init(x2,a2,b2,m);
	}
	mset(calc,0,n);
	lint ans=0;
	for(int i=1;i<=k&&i<=a.ls;i++){
		if(i<a.st){
			int p=b.at(i);
			ans+=c2(p)+c2(m-p-1);
			calc[a.lst[i]]=true;
		}else if(!calc[a.lst[i]]){
			Seats seat;
			int step=a.len%b.len;
			for(lint l=i,r=i;l<=k&&!calc[a.at(l)];){
				for(;r<=k&&!seat.has(b.at(r));r+=a.len){
					seat.ins(b.at(r));
				}
				ans+=seat.ans;
				calc[a.at(l)]=true;
				seat.del(b.at(l));
				l+=step;
				r-=a.len-step;
				for(;l>a.ls;){
					l-=a.len;
					seat.ins(b.at(l));
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		if(!calc[i]){
			ans+=c2(m);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
