#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <vector>
using namespace std;
typedef vector<int>vi;
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
struct Query{
	int len;
	vector<int>ext;
};
typedef vector<Query>vq;
vq qry[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	memset(vis,0,sizeof(vis));
	n=ni,m=ni;
	lint k=next_num<lint>();
	lint ans=0;
	{
		const int x1=ni,a1=ni,b1=ni;
		const int x2=ni,a2=ni,b2=ni;
		a.init(x1,a1,b1,n);
		for(int i=0;i<n;i++){
			if(vis[i]<tim){
				ans+=c2(m);
			}
		}
		b.init(x2,a2,b2,m);
	}
	for(int i=1;i<=a.ls;i++){
		if(i<a.st){
			int p=b.at(i);
			if(i<=k){
				ans+=c2(p)+c2(m-p-1);
			}else{
				ans+=c2(m);
			}
		}else{
			int p=i;
			Query q;
			q.len=max((k-p+a.len)/a.len,0ll);
			for(;p<b.st;p+=a.len){
				if(q.len>0){
					--q.len,q.ext.push_back(b.lst[p]);
				}
			}
			qry[(p-b.st)%b.len+b.st].push_back(q);
		}
	}
	int step=a.len%b.len;
	++tim;
	int ringlen=b.len/gcd(a.len,b.len);
	for(int i=b.st,ti=i+gcd(a.len,b.len);i<ti;i++){
		Seats seat;
		for(int p=i,len=0;vis[p]<tim;p=(p+step-b.st)%b.len+b.st){
			vis[p]=tim;
			for(vq::iterator it1=qry[p].begin(),ti1=qry[p].end();it1!=ti1;++it1){
				int tlen=it1->len;
				for(;len<ringlen&&len<tlen;seat.ins(b.at(p+step*len++)));
				for(;len>tlen;seat.del(b.at(p+step*--len)));
				for(vi::iterator it2=it1->ext.begin(),ti2=it1->ext.end();it2!=ti2;++it2){
					seat.ins(*it2);
				}
				ans+=seat.ans;
				for(vi::iterator it2=it1->ext.begin(),ti2=it1->ext.end();it2!=ti2;++it2){
					seat.del(*it2);
				}
			}
			if(len){
				--len,seat.del(b.lst[p]);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
