#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
#include <set>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=1010,INF=0x7f7f7f7f;
struct Pt{
	int x,y;
	inline lint d2()const{return sqr<lint>(x)+sqr<lint>(y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
	inline friend bool polarcmp(const Pt &a,const Pt &b){
		lint t=crs(a,b);
		return t?t>0:(a.d2()>b.d2());
	}
}pt[N];
int tp[N];
vi con[N];
int lnk[N];
bool vis[N];
bool aug(int x){
	for(vi::iterator it=con[x].begin(),ti=con[x].end();it!=ti;++it){
		int v=*it;
		if(!vis[v]){
			vis[v]=true;
			if(lnk[v]==0||aug(lnk[v])){
				lnk[x]=v,lnk[v]=x;
				return true;
			}
		}
	}
	return false;
}
int lst[N];
Pt base;
inline bool lcmp(int a,int b){
	return polarcmp(pt[a]-base,pt[b]-base);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("etoile.in","r",stdin);
	freopen("etoile.out","w",stdout);
#endif
	const int n=ni;
	const lint r=sqr(next_num<lint>()),d=sqr(next_num<lint>());
	int ls=-1;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		if((pt[i]-pt[1]).d2()<=r){
			tp[i]=2;
			lst[++ls]=i;
		}else{
			tp[i]=1;
		}
	}
	lst[++ls]=1;
	for(int i=1;i<=n;i++){
		if(tp[i]==2)continue;
		for(int j=1;j<=ls;j++){
			if((pt[i]-pt[lst[j]]).d2()<=d){
				con[i].push_back(lst[j]);
			}
		}
		base=pt[i],sort(con[i].begin(),con[i].end(),lcmp);
	}
	int flow=0;
	mset(lnk+1,0,n);
	for(int i=1;i<=n;i++){
		if(tp[i]==1){
			mset(vis+1,0,n);
			flow+=aug(i);
		}
	}
	mset(vis+1,0,n);
	printf("%d\n",flow<<1);
	for(int t=1;t<=flow;t++){
		for(int i=1;;i++){
			if(tp[i]==1&&lnk[i]&&!vis[i]){
				bool flag=true;
				for(vi::iterator it=con[i].begin(),ti=con[i].end();*it!=lnk[i];++it){
					if(!vis[*it]){
						flag=false;
						break;
					}
				}
				if(flag){
					vis[i]=vis[lnk[i]]=true;
					printf("%d %d\n",i,lnk[i]);
					break;
				}
			}
		}
	}
	return 0;
}
