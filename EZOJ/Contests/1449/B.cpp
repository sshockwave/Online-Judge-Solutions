#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef /*long */double db;
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
inline db nexd(){
	db i;
	scanf("%lf",&i);
	return i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=110;
const db EPS=1e-8;
inline bool isz(const db &x){return x>=-EPS&&x<=EPS;}
struct Pt{
#define Pt(x,y) ((Pt){x,y})
	db x,y;
	inline db d2()const{return sqr(x)+sqr(y);}
	inline db len()const{return sqrt(d2());}
	inline Pt operator * (const db &v)const{return Pt(x*v,y*v);}
	inline friend db dist(const Pt &a,const Pt &b){return (a-b).len();}
	inline friend Pt operator + (const Pt &a,const Pt &b){return Pt(a.x+b.x,a.y+b.y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return Pt(a.x-b.x,a.y-b.y);}
	inline friend Pt operator * (const Pt &a,const Pt &b){return Pt(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
	inline friend db dot(const Pt &a,const Pt &b){return a.x*b.x+a.y*b.y;}
	inline friend db crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
}rot;
inline db ints(const Pt &x,const Pt &vec){
	if(isz(x.y))return x.x;
	return x.x+vec.x*-x.y/vec.y;
}
inline void getmid(const Pt &a,const Pt &b,Pt fr,Pt to,Pt &ma,Pt &mb){
	Pt vec=b-a;
	const db len=vec.len();
	fr=Pt(dot(vec,fr-a),crs(vec,fr-a));
	to=Pt(dot(vec,to-a),crs(vec,to-a));
	bool flag=false;
	if(fr.x>to.x){
		swap(fr,to);
		flag=true;
	}
	const db l=max((db)0,min(len,ints(fr,fr.y<0?Pt(rot.x,rot.y):Pt(rot.x,-rot.y))/len));
	const db r=max((db)0,min(len,ints(to,to.y<0?Pt(-rot.x,rot.y):Pt(-rot.x,-rot.y))/len));
	vec=vec*(1/len);
	ma=a+vec*l,mb=a+vec*r;
	if(flag){
		swap(ma,mb);
	}
}
Pt pt[N<<1];
db _dis[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ernd.in","r",stdin);
	freopen("ernd.out","w",stdout);
#endif
	int n=1;
	pt[0]=Pt(nexd(),nexd()),pt[1]=Pt(nexd(),nexd());
	_dis[0]=0,_dis[1]=dist(pt[0],pt[1]);
	int tot=ni;
	db v=nexd();
	rot=Pt(v,sqrt(sqr(v)*(sqr(v)-1)));
	for(;tot--;){
		const Pt a=Pt(nexd(),nexd()),b=Pt(nexd(),nexd());
		db mn=1e100;
		int l,r;
		for(int i=0;i<n;i++){
			for(int j=i+1;j<=n;j++){
				Pt ma,mb;
				getmid(a,b,pt[i],pt[j],ma,mb);
				const db cur=dist(pt[i],ma)+dist(ma,mb)/v+dist(mb,pt[j])-(_dis[j]-_dis[i]);
				if(cur<mn){
					mn=cur,l=i,r=j;
				}
			}
		}
		if(mn<0){
			static Pt tmppt[N<<1];
			static db tmpdis[N<<1];
			int tn=-1;
			for(int i=0;i<=l;i++){
				++tn,tmppt[tn]=pt[i],tmpdis[tn]=_dis[i];
			}
			getmid(a,b,pt[l],pt[r],tmppt[tn+1],tmppt[tn+2]);
			tmpdis[tn+1]=tmpdis[tn]+dist(tmppt[tn],tmppt[tn+1]);
			tmpdis[tn+2]=tmpdis[tn+1]+dist(tmppt[tn+1],tmppt[tn+2])/v;
			tn+=2;
			for(int i=r;i<=n;i++){
				++tn,tmppt[tn]=pt[i],tmpdis[tn]=tmpdis[tn-1]+dist(tmppt[tn-1],tmppt[tn]);
			}
			n=tn;
			memcpy(pt,tmppt,(n+1)*sizeof(pt[0]));
			memcpy(_dis,tmpdis,(n+1)*sizeof(_dis[0]));
		}
	}
	printf("%.10lf\n",_dis[n]);
	return 0;
}
