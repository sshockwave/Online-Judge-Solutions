#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <cmath>
using namespace std;
typedef double db;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=5010;
const db EPS=1e-8;
struct Pt{
	int x,y;
	inline lint d2(){return (lint)x*x+(lint)y*y;}
	inline db ang(){return atan2(y,x);}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};};
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};};
	inline friend lint dot(const Pt &a,const Pt &b){return (lint)a.x*b.x+(lint)a.y*b.y;};
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;};
}pt[N<<1],seg[N],base;
db ang[N<<1],cosang[N],sinang[N];
int lst[N<<1];
inline bool lcmp(int a,int b){
	return ang[a]<ang[b];
}
inline bool polarcmp(int i,int j){
	return crs(pt[i]-base,pt[j]-base)>0;
}
bool mark[N<<1];
int lnk[N<<1];
void solve(int l,int r){
	if(l>r)return;
	int p=l;
	for(int i=l+1;i<=r;i++){
		int x=lst[i],y=lst[p];
		if(pt[x].y<pt[y].y){
			p=i;
		}else if(pt[x].y==pt[y].y&&pt[x].x<pt[y].x){
			p=i;
		}
	}
	swap(lst[l],lst[p]);
	base=pt[lst[l]];
	sort(lst+l+1,lst+r+1,polarcmp);
	int cnt[2]={0,0};
	for(p=l+1;mark[lst[l]]==mark[lst[p]]||cnt[0]!=cnt[1];cnt[mark[lst[p]]]++,p++);
	lnk[lst[l]]=lst[p],lnk[lst[p]]=lst[l];
	solve(l+1,p-1),solve(p+1,r);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("nonintersect.in","r",stdin);
	freopen("nonintersect.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=(n<<1);i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1;i<=n;i++){
		seg[i]=(Pt){ni,ni};
		ang[i]=(pt[seg[i].x]-pt[seg[i].y]).ang();
		if(ang[i]>M_PI){
			ang[i]-=M_PI;
		}else if(ang[i]<0){
			ang[i]+=M_PI;
		}
	}
	sort(ang+1,ang+n+1);
	{//get mark
		cosang[0]=sinang[0]=0;
		for(int i=1;i<=n;i++){
			cosang[i]=cosang[i-1]+cos(ang[i]);
			sinang[i]=sinang[i-1]+sin(ang[i]);
		}
		db alpa,alpb,val=-1;
		for(int i=0;i<=n;i++){
			db a=cosang[i]*2-cosang[n],b=sinang[i]*2-sinang[n];
			db cur=sqr(a)+sqr(b);
			if(cur>val){
				val=cur;
				alpa=a,alpb=b;
			}
		}
		for(int i=1;i<=(n<<1);i++){
			ang[i]=alpa*pt[i].x+alpb*pt[i].y,lst[i]=i;
		}
		sort(lst+1,lst+(n<<1)+1,lcmp);
		memset(mark,0,sizeof(mark));
		for(int i=1;i<=n;i++){
			mark[lst[i]]=true;
		}
	}
	solve(1,n<<1);
	for(int i=1;i<=(n<<1);i++){
		if(lnk[i]<i){
			printf("%d %d\n",lnk[i],i);
		}
	}
	return 0;
}
