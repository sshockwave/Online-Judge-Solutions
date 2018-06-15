#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=1010;
const db EPS=1e-8;
inline bool isz(const db &x){
	return x>=-EPS&&x<=EPS;
}
struct Pt{
#define Pt(x,y) ((Pt){x,y})
	db x,y;
	inline db d2()const{return sqr(x)+sqr(y);}
	inline db abs()const{return sqrt(d2());}
	inline Pt operator * (const db &b)const{return Pt(x*b,y*b);}
	inline friend db dist(const Pt &a,const Pt &b){return (a-b).abs();}
	inline Pt operator - (){return Pt(-x,-y);}
	inline friend Pt operator + (const Pt &a,const Pt &b){return Pt(a.x+b.x,a.y+b.y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return Pt(a.x-b.x,a.y-b.y);}
	inline friend Pt operator * (const Pt &a,const Pt &b){return Pt(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
	inline friend db crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
	inline friend db dot(const Pt &a,const Pt &b){return a.x*b.x+a.y*b.y;}
}pt[N];
const Pt I=Pt(0,1);
int n,rad,rad2;
namespace circ{
	inline void circ_ints(const Pt &a,db r_a,const Pt &b,db r_b,Pt &s1,Pt &s2){
		const db d2=(a-b).d2(),d=sqrt(d2);
		r_a=sqr(r_a),r_b=sqr(r_b);
		const db x=(r_a-r_b+d2)/(d*2);
		Pt vec=b-a;
		vec=vec*(1/vec.abs());
		const Pt m=a+vec*x,t=vec*I*sqrt(r_a-sqr(x));
		s1=m+t,s2=m-t;
		assert(isz((s1-a).d2()-r_a));
		assert(isz((s1-b).d2()-r_b));
		assert(isz((s2-a).d2()-r_a));
		assert(isz((s2-b).d2()-r_b));
	}
	inline void solve_eqn(db a1,db b1,db c1,db a2,db b2,db c2,db &x,db &y){
		const db bot=crs(Pt(a1,b1),Pt(a2,b2));
		assert(!isz(bot));
		x=(c1*b2-c2*b1)/bot,y=(a1*c2-a2*c1)/bot;
		assert(isz(a1*x+b1*y-c1));
		assert(isz(a2*x+b2*y-c2));
	}
	struct Ev{
		int x,op;
		Pt vec;
		inline friend bool operator < (const Ev &a,const Ev &b){//add first
			const db c=crs(a.vec,b.vec);
			return !isz(c)?c>0:a.op>b.op;
		}
	}ev[N*4];
	int es;
	int cnt[N],totcnt;
	inline void alt(int x,int v){
		assert(v==1||v==-1);
		if(cnt[x]==0){
			++totcnt;
		}
		cnt[x]+=v;
		if(cnt[x]==0){
			--totcnt;
		}
	}
	inline bool inc(const Pt &a,const Pt &b){
		return crs(a,b)>=-EPS;
	}
	inline bool inc(const Pt &a,const Pt &b,const Pt &c){
		return crs(a,b)>=-EPS&&crs(b,c)>=-EPS;
	}
	inline bool enlst(const Pt &l,const Pt &r,const Pt &s1,const Pt &s2,int i){
		assert(crs(s1,s2)>=-EPS);
		if(inc(l,s1,r)){
			alt(i,1),ev[++es]=(Ev){i,-1,s1};
		}else if(inc(r,s1)){
			alt(i,1);
			return true;
		}
		if(inc(l,s2,r)){
			ev[++es]=(Ev){i,1,s2};
		}else if(inc(s2,l)){
			alt(i,1);
			return true;
		}
		return false;
	}
	inline bool main(const Pt &x,const Pt &y,const Pt l,const Pt r){
		mset(cnt+1,0,n),totcnt=0;
		es=0;
		for(int i=1;i<=n;i++){
			const Pt p=pt[i];
			if((p-x).d2()<=rad2+EPS||(p-y).d2()<=rad2+EPS){
				alt(i,1);
				continue;
			}
			{//calc x
				Pt s1,s2;
				circ_ints((x+p)*0.5,dist(p,x)*0.5,p,rad,s1,s2);
				s1=s1-x,s2=s2-x;
				if(crs(s2,s1)<0){
					swap(s1,s2);
				}
				s2=-s2;
				if(enlst(l,r,s1,s2,i))continue;
			}
			{//calc y
				Pt s1,s2;
				circ_ints((y+p)*0.5,dist(p,y)*0.5,p,rad,s1,s2);
				s1=s1-y,s2=s2-y;
				if(crs(s2,s1)<0){
					swap(s1,s2);
				}
				s1=-s1;
				s1=s1*I,s2=s2*I;
				if(enlst(l,r,s1,s2,i))continue;
			}
		}
		sort(ev+1,ev+es+1);
		ev[0].vec=l;
		for(int i=0;i<=es;i++){
			if(i){
				alt(ev[i].x,ev[i].op);
			}
			const Pt v=ev[i].vec;
			if(totcnt==n){
				Pt A;
				solve_eqn(v.x,v.y,dot(y,v),v.y,-v.x,crs(x,v),A.x,A.y);
				const Pt iden=v*(1/v.abs());
				Pt B=A+iden-iden*I;
				puts("OK");
				printf("%.10lf %.10lf\n",A.x,A.y);
				printf("%.10lf %.10lf\n",B.x,B.y);
				return true;
			}
		}
		return false;
	}
}
namespace hull{
	int pv[N],nx[N];
	inline bool x_cmp(int a,int b){
		return pt[a].x!=pt[b].x?pt[a].x<pt[b].x:pt[a].y<pt[b].y;
	}
	inline bool turn_rig(int a,int b,int c){
		return crs(pt[b]-pt[a],pt[c]-pt[a])<=0;
	}
	int lst[N],stk[N];
	inline void work(){
		int ss=0;
		for(int i=1;i<=n;i++){
			for(;ss>=2&&!turn_rig(stk[ss-1],stk[ss],lst[i]);ss--);
			stk[++ss]=lst[i];
		}
		for(int i=1;i<ss;i++){
			nx[stk[i+1]]=stk[i],pv[stk[i]]=stk[i+1];
		}
	}
	inline int main(){
		for(int i=1;i<=n;i++){
			lst[i]=i;
		}
		sort(lst+1,lst+n+1,x_cmp);
		work();
		reverse(lst+1,lst+n+1);
		work();
		return stk[1];
	}
}
inline Pt polar_max(const Pt &a,const Pt &b){
	return crs(a,b)>=0?b:a;
}
inline Pt polar_min(const Pt &a,const Pt &b){
	return crs(a,b)>=0?a:b;
}
inline void Main(){
	n=ni,rad=ni,rad2=sqr(rad);
	for(int i=1;i<=n;i++){
		pt[i]=Pt((db)ni,(db)ni);
	}
	if(n==0){
		puts("OK");
		puts("0 0");
		printf("%d %d\n",rad,rad);
		return;
	}else if(n==1){
		puts("OK");
		printf("%.10lf %.10lf\n",pt[1].x,pt[1].y);
		printf("%.10lf %.10lf\n",pt[1].x+rad,pt[1].y+rad);
		return;
	}
	using hull::pv;
	using hull::nx;
	int a=hull::main(),b=nx[a];
	for(;dot(pt[pv[a]]-pt[a],pt[nx[b]]-pt[b])<-EPS;b=nx[b]);
	const int a_1=a,b_1=b;
	do{
		const Pt l=polar_max(pt[pv[a]]-pt[a],(pt[b]-pt[pv[b]])*I);
		const Pt r=polar_min(pt[a]-pt[nx[a]],(pt[nx[b]]-pt[b])*I);
		if(circ::main(pt[a],pt[b],l,r))return;
		if(crs(pt[a]-pt[nx[a]],(pt[nx[b]]-pt[b])*I)>=0){
			a=nx[a];
		}else{
			b=nx[b];
		}
	}while(a!=a_1||b!=b_1);
	puts("NO");
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("battleship.in","r",stdin);
	freopen("battleship.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
