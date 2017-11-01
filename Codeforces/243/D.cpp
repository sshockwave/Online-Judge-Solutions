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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1001,N2=N*N,INF=0x7f7f7f7f;

struct Pt{
	int x,y;
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend int dot(const Pt &a,const Pt &b){return a.x*b.x+a.y*b.y;}
	inline friend int crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
}pt[N2],vec;
int plst[N2],ps=0;
inline ostream & operator << (ostream & out,const Pt &b){
	out<<"("<<b.x<<","<<b.y<<")";
	return out;
}
inline bool pcmp(int a,int b){
	return crs(pt[a]-pt[b],vec)>0;
}

struct Li{
	int x,y,h,p1,p2;
}li[N2<<2];
int ls=0;
inline bool lcmp(const Li &a,const Li &b){
	return dot((pt[b.p1]+pt[b.p2])-(pt[a.p1]+pt[a.p2]),vec)>0;
}

namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int h;
		inline void down(){
			apmax(lson->h,h);
			apmax(rson->h,h);
		}
		inline void up(){
			h=min(lson->h,rson->h);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N2<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->h=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	int ask(node x,const Li &li){
		if(!pcmp(plst[x->l-1],li.p1)&&!pcmp(li.p2,plst[x->r])){
			return x->h;
		}
		x->down();
		int ans=INF;
		if(pcmp(li.p1,plst[x->m])){
			apmin(ans,ask(x->lson,li));
		}
		if(pcmp(plst[x->m],li.p2)){
			apmin(ans,ask(x->rson,li));
		}
		return ans;
	}
	void ins(node x,const Li &li){
		if(!pcmp(plst[x->l-1],li.p1)&&!pcmp(li.p2,plst[x->r])){
			apmax(x->h,li.h);
			return;
		}
		x->down();
		if(pcmp(li.p1,plst[x->m])){
			ins(x->lson,li);
		}
		if(pcmp(plst[x->m],li.p2)){
			ins(x->rson,li);
		}
		x->up();
	}
}
int see[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
#endif
	int n=ni;
	vec=(Pt){ni,ni};
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			pt[i*(n+1)+j]=(Pt){i,j};
			plst[i*(n+1)+j]=i*(n+1)+j;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int h=ni;
			int p1=(i-1)*(n+1)+(j-1);
			int p2=i*(n+1)+(j-1);
			int p3=(i-1)*(n+1)+j;
			int p4=i*(n+1)+j;
			li[ls++]=(Li){i,j,h,p1,p2};
			li[ls++]=(Li){i,j,h,p2,p4};
			li[ls++]=(Li){i,j,h,p4,p3};
			li[ls++]=(Li){i,j,h,p3,p1};
		}
	}
	sort(li,li+ls,lcmp);
	sort(plst,plst+(n+1)*(n+1),pcmp);
	for(int i=0,ti=(n+1)*(n+1);i<ti;ps++){
		plst[ps]=plst[i];
		for(;i<ti&&!pcmp(plst[ps],plst[i]);i++);
	}
	seg::rt=seg::build(1,ps-1);
	memset(see,0,sizeof(see));
	for(int i=0;i<ls;i++){
		if(!pcmp(li[i].p1,li[i].p2)){
			swap(li[i].p1,li[i].p2);
		}
		if(!pcmp(li[i].p1,li[i].p2)){
			continue;
		}
		apmax(see[li[i].x][li[i].y],li[i].h-seg::ask(seg::rt,li[i]));
		seg::ins(seg::rt,li[i]);
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans+=see[i][j];
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
