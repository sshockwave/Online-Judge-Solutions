#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
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
template<class T>inline T abs(const T &x){return x>=0?x:-x;}
const int N=510,N2=N*N,INF=0x7f7f7f7f;
struct Pt{
	int x,y;
	inline void gobig(){
		int t=min(INF/max(abs(x),1),INF/max(abs(y),1));
		x*=t,y*=t;
	}
	inline lint d2()const{
		return (lint)x*x+(lint)y*y;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){
		return (Pt){a.x-b.x,a.y-b.y};
	}
	inline friend lint crs(const Pt &a,const Pt &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
	inline friend bool polarcmp(const Pt &a,const Pt &b){
		assert((a.x||a.y)&&(b.x||b.y));
		lint tmp=(lint)a.y*b.y;
		if(tmp<0)return b.y<0;
		if(tmp>0){
			tmp=crs(a,b);
			return tmp?tmp>0:a.d2()<b.d2();
		}
		tmp=crs(a,b);
		if(tmp)return tmp>0;
		assert(a.y==0&&b.y==0);
		assert(a.x&&b.x);
		if(a.x>0)return b.x>a.x||b.x<0;
		return b.x<a.x;
	}
	inline friend ostream & operator << (ostream & out,const Pt &b){
		out<<"("<<b.x<<","<<b.y<<")";
		return out;
	}
}pt[N],base;
int n;
inline bool dcmp(int a,int b){
	return (pt[a]-base).d2()<(pt[b]-base).d2();
}
struct Nail{
	int id,dlst[N],ls;
	int *vec[N];
	inline void work(int _id){
		base=pt[id=_id];
		ls=0;
		for(int i=1;i<=n;i++){
			if(i!=id){
				dlst[++ls]=i;
			}
		}
		sort(dlst+1,dlst+ls+1,dcmp);
		for(int i=1,j,x;x=dlst[i],i<=ls;i++){
			for(j=1;j<i;j++){
				if(polarcmp(pt[x]-base,pt[vec[i-1][j]]-base)){
					for(int k=i;k>j;k--){
						vec[i][k]=vec[i-1][k-1];
					}
					vec[i][j]=x;
					break;
				}
				vec[i][j]=vec[i-1][j];
			}
			if(j==i){
				vec[i][i]=x;
			}
		}
	}
	inline int gnxt(Pt vc,double len){
		base=pt[id];
		double len2=len*len;
		int l=0,r=ls;
		while(l<r){
			int m=((l+r)>>1)+1;
			if((pt[dlst[m]]-base).d2()>len2){
				r=m-1;
			}else{
				l=m;
			}
		}
		if(l==0)return -1;
		int x=l;
		int *tmp=vec[l];
		l=0,r=x;
		vc.gobig();
		while(l<r){
			int m=((l+r)>>1)+1;
			if(polarcmp(pt[tmp[m]]-base,vc)){
				l=m;
			}else{
				r=m-1;
			}
		}
		return l?tmp[l]:tmp[x];
	}
}nail[N];
int pos[N];
int lst[N*32];
double _dis[N*32];
inline lint work(){
	Pt s=(Pt){ni,ni};
	Pt vc=((Pt){ni,ni})-s;
	double len=ni,len2=len*len;
	int x=-1,pmx=-1;
	vc.gobig();
	for(int i=1;i<=n;i++){
		if((pt[i]-s).d2()<=len2){
			if(polarcmp(pt[i]-s,vc)&&(x==-1||polarcmp(pt[x]-s,pt[i]-s))){
				x=i;
			}
			if(pmx==-1||polarcmp(pt[pmx]-s,pt[i]-s)){
				pmx=i;
			}
		}
	}
	if(x==-1){
		x=pmx;
	}
	if(x==-1)return 1;
	vc=pt[x]-s;
	len-=sqrt(vc.d2());
	lint ans=1;
	while(true){
		memset(pos+1,-1,n<<2);
		int ls=0;
		_dis[0]=0;
		while(true){
			lst[++ls]=x;
			ans++;
			int y=nail[x].gnxt(vc,len);
			if(y==-1)return ans;
			vc=pt[y]-pt[x];
			if(~pos[x]&&lst[pos[x]+1]==y)break;
			pos[x]=ls;
			_dis[ls]=_dis[ls-1]+sqrt((pt[x]-pt[y]).d2());
			len-=_dis[ls]-_dis[ls-1];
			x=y;
		}
		ans--;
		double d=_dis[ls-1]-_dis[pos[x]-1];
		int lpcnt=len/d+1e-8;
		ans+=(lint)(ls-pos[x])*lpcnt;
		len-=lpcnt*d;
	}
}
inline void Main(){
	n=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1;i<=n;i++){
		nail[i].work(i);
	}
	for(;tot--;printf("%lld\n",work()));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	for(int i=1;i<=N-10;i++){
		for(int j=1;j<=N-10;j++){
			nail[i].vec[j]=new int[j]-1;
		}
	}
	for(int tot=ni;tot--;Main());
	return 0;
}
