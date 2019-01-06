#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
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
const int N=100000,E=N*3;
struct Pt{
	int x,y;
	inline lint d2()const{return sqr<lint>(x)+sqr<lint>(y);}
	inline int quad()const{
		if(x>0&&y>=0)return 1;
		if(x<=0&&y>0)return 2;
		if(x<0&&y<=0)return 3;
		if(x>=0&&y<0)return 4;
		return 0;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
	inline friend bool polarcmp(const Pt &a,const Pt &b){
		int qa=a.quad(),qb=b.quad();
		return qa!=qb?qa<qb:crs(a,b)>0;
	}
}pt[N];
lint hei[N];
int n,gn;
namespace dj{
	const int N=::E*2;
	int fa[N];
	inline void init(){
		mset(fa+1,0,gn);
	}
	inline int grt(int x){
		return fa[x]?fa[x]=grt(fa[x]):x;
	}
	inline void mg(int a,int b){
		a=grt(a),b=grt(b);
		if(a==b)return;
		fa[a]=b;
	}
}
namespace G{
	const int N=::N,E=::E*2;
	int to[E],val[E],nxt[E];
	Pt vec[E];
	vi edg[N];
	bool vis[E];
	inline void init(){
		for(int i=1;i<=n;i++){
			edg[i].clear();
		}
	}
	int base;
	inline bool cmp_polar(int a,int b){
		return polarcmp(pt[to[a]]-pt[base],pt[to[b]]-pt[base]);
	}
	inline void buildface(){
		for(int x=1;x<=n;x++){
			vi::iterator st=edg[x].begin(),ed=edg[x].end();
			base=x,sort(st,ed,cmp_polar);
			for(vi::iterator i=st;i!=ed;++i){
				const int a=1^*i,b=i+1!=ed?*(i+1):*st;
				nxt[a]=b;
			}
		}
	}
	lint a[3][3];
	inline lint det(){
		lint ans=0;
		ans+=a[0][0]*a[1][1]*a[2][2];
		ans+=a[0][1]*a[1][2]*a[2][0];
		ans+=a[0][2]*a[1][0]*a[2][1];
		ans-=a[0][2]*a[1][1]*a[2][0];
		ans-=a[0][1]*a[1][0]*a[2][2];
		ans-=a[0][0]*a[1][2]*a[2][1];
		return ans;
	}
	inline bool unifi(int lst[],int ls,int e1,int e2){
		a[0][0]=vec[e1].x,a[0][1]=vec[e1].y,a[0][2]=val[e1];
		a[1][0]=vec[e2].x,a[1][1]=vec[e2].y,a[1][2]=val[e2];
		for(int i=1;i<=ls;i++){
			const int x=lst[i];
			a[2][0]=vec[x].x,a[2][1]=vec[x].y,a[2][2]=val[x];
			if(det()==0)continue;
			lst[i]^=1,a[2][2]=-val[x];
			if(det()==0)continue;
			return false;
		}
		return true;
	}
	int lst1[N],lst2[N];
	inline void bind(int a,int b){
		if(val[a]==0||val[b]==0)return;
		dj::mg(a,b),dj::mg(a^1,b^1);
	}
	inline void build2sat(){
		{//init
			mset(vis+1,0,gn);
			vis[1]=true;
			int p=1;
			for(int i=1;i<=n;i++){
				if(pt[i].y<pt[p].y){
					p=i;
				}
			}
			for(int x=edg[p][0];!vis[x];x=nxt[x]){
				vis[x]=true;
			}
			dj::init();
		}
		for(int x=1;x<=gn;x++){
			if(vis[x])continue;
			int ls=0;
			for(int p=x;!vis[p];p=nxt[p]){
				vis[p]=true;
				++ls,lst1[ls]=lst2[ls]=p;
			}
			int y=x;
			for(;y=nxt[y],crs(vec[x],vec[y])==0;);
			bool ok1=unifi(lst1,ls,x,y);
			bool ok2=unifi(lst2,ls,x,y^1);
			assert(ok1||ok2);
			for(int i=2;i<=ls;i++){
				if(ok1&&ok2){
					bind(lst1[i]==lst2[i]?x:y,lst1[i]);
				}else{
					bind(x,(ok1?lst1:lst2)[i]);
				}
			}
		}
	}
	void markans(int x){
		vis[x]=true;
		for(vi::iterator it=edg[x].begin(),ti=edg[x].end();it!=ti;++it){
			const int i=*it,v=to[i];
			assert(val[i]==0||dj::grt(i)!=dj::grt(i^1));
			if(vis[v])continue;
			hei[v]=hei[x]+(dj::grt(i)<dj::grt(i^1)?val[i]:-val[i]);
			markans(v);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fireworks.in","r",stdin);
	freopen("fireworks.out","w",stdout);
#endif
	n=ni;
	const int e=ni;
	gn=e*2+1;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	G::init();
	for(int i=1;i<=e;i++){
		using namespace G;
		const int u=ni,v=ni;
		const int a=i<<1,b=a|1;
		db len;
		scanf("%lf",&len);
		val[a]=val[b]=round(sqrt(max<db>(sqr(len)-(pt[u]-pt[v]).d2(),0)));
		vec[a]=pt[to[a]=v]-pt[u],edg[u].push_back(a);
		vec[b]=pt[to[b]=u]-pt[v],edg[v].push_back(b);
	}
	G::buildface();
	G::build2sat();
	mset(G::vis+1,0,n),hei[1]=0,G::markans(1);
	for(int i=1;i<=n;i++){
		printf("%lld\n",hei[i]);
	}
	return 0;
}
