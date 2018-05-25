#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef double db;
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
const int N=1000010;
struct Route{
	int u,v;
	lint s,t;
	db p,mxp;
}bus[N];
struct Event{
	int id;
	lint t;
	int tp;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.t!=b.t?a.t<b.t:(a.tp==1&&b.tp==2);
	}
}ev[N<<1];
db prob[N];
inline bool lcmp(const Event &a,const Event &b){//sort 2 by biggest probablity
	assert(a.t==b.t);
	assert(a.tp==b.tp);
	const Route &u=bus[a.id],&v=bus[b.id];
	return u.mxp+(1-u.p)*prob[u.u]<v.mxp+(1-v.p)*prob[v.u];
}
int tag[N];
int main(){/*
#ifndef ONLINE_JUDGE
freopen("catch.in","r",stdin);
freopen("catch.out","w",stdout);
#endif*/
	int m=ni,n=ni;
	lint mxtim=next_num<lint>();
	int es=0;
	for(int i=1;i<=m;i++){
		bus[i]=(Route){ni,ni,next_num<lint>(),next_num<lint>()};
		scanf("%lf",&bus[i].p);
		ev[++es]=(Event){i,bus[i].s,1};
		ev[++es]=(Event){i,bus[i].t,2};
	}
	sort(ev+1,ev+es+1);
	prob[1]=1;
	for(int i=es;i>=1;){
		if(ev[i].t>mxtim)continue;
		Event &e=ev[i];
		if(e.tp==2){
			Route &b=bus[e.id];
			b.mxp=prob[b.v]*b.p;
			i--;
		}else{
			int j=i;
			for(;j>=1&&ev[j].t==ev[i].t;j--);
			sort(ev+j+1,ev+i+1,lcmp);
			for(int k=i;k>j;k--){
				Event &e=ev[k];
				Route &b=bus[e.id];
				if(tag[b.u]==i)continue;
				tag[b.u]=i;
				apmax(prob[b.u],b.mxp+(1-b.p)*prob[b.u]);
			}
			i=j;
		}
	}
	printf("%.10lf\n",prob[0]);
	return 0;
}
