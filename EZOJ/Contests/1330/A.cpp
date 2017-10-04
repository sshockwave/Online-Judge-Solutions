#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int d[N],v[N];
struct deci{
	int d,v;
	deci(int _d,int _v){
		int g=gcd(_d,_v);
		d=_d/g,v=_v/g;
	}
	inline friend bool operator < (const deci &a,const deci &b){
		return (lint)a.d*b.v<(lint)b.d*a.v;
	}
};
int stk[N];
inline deci work(int lst[],int n){
	set<deci>s;
	set<deci>::iterator it;
	int ss=0;
	for(int i=0;i<n;i++){
		int x=lst[i];
		for(;ss&&stk[ss-1]<x;ss--,s.erase(deci(d[stk[ss]],v[stk[ss]])));
		deci tmp(d[x],v[x]);
		if(s.empty()||*(it=s.end(),--it)<tmp){
			stk[ss++]=x;
			s.insert(tmp);
		}
	}
	it=s.end();
	it--;
	return s.empty()?deci(0,1):*(it=s.end(),--it);
}
int lst[N];
int qa[N],qb[N];
inline bool lcmp(int a,int b){
	return d[a]<d[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
#endif
	int n=ni,L=ni;
	if(n==1){
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		d[i]=ni;
	}
	for(int i=1;i<=n;i++){
		v[i]=ni;
	}
	for(int i=1;i<n;i++){
		v[i]-=v[n];
		d[i]=(d[i]-d[n]+L)%L;
		lst[i]=i;
	}
	n--;
	sort(lst+1,lst+n+1,lcmp);
	int la=0,lb=0;
	for(int i=1,mx=0;i<=n;i++){
		int x=lst[i];
		if(v[x]>0){
			apmax(mx,x);
		}else if(x>mx){
			qa[la++]=x;
			mx=0;
		}
	}
	for(int i=n,mx=0;i>=1;i--){
		int x=lst[i];
		if(v[x]<0){
			apmax(mx,x);
		}else if(x>mx){
			qb[lb++]=x;
			mx=0;
		}
	}
	for(int i=0;i<la;i++){
		v[qa[i]]=-v[qa[i]];
	}
	for(int i=0;i<lb;i++){
		d[qb[i]]=L-d[qb[i]];
	}
	deci ans=max(work(qa,la),work(qb,lb));
	printf("%d/%d\n",ans.d,ans.v);
	return 0;
}
