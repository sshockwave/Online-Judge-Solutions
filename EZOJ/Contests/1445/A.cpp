#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef long double db;
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
inline db getdb(){
	double i;
	scanf("%lf",&i);
	return i;
}
namespace solve{
	struct Pt{
		db x,y;
		inline db d2()const{return sqr(x)+sqr(y);}
		inline db len()const{return sqrt(d2());}
		inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
		inline friend db crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
		inline friend db dot(const Pt &a,const Pt &b){return a.x*b.x+a.y*b.y;}
	};
	//constants
	db hei,ang;
	db bot_rad;
	//variables
	db ans1,ans2;
	inline Pt cgetpt(){
		return (Pt){getdb(),getdb()};
	}
	inline db calc_tri(const db d,const db b){
		const db c=((Pt){d,b}).len();
		if(c<=bot_rad)return d*b/2;
		const db sqrad=sqr(bot_rad);
		const db s=asin(b/c)*sqrad/2;
		if(d>=bot_rad)return s;
		const db x=sqrt(sqrad-sqr(d));
		return s-asin(x/((Pt){d,x}).len())*sqrad/2+x*d/2;
	}
	inline db calc2(const db d,const db l,const db r){
		assert(l<=r);
		db ans=0;
		if(l<=0){
			ans+=calc_tri(d,-l);
		}else{
			ans-=calc_tri(d,l);
		}
		if(r>=0){
			ans+=calc_tri(d,r);
		}else{
			ans-=calc_tri(d,-r);
		}
		return ans;
	}
	inline db int_sqrt(const db x){
		const db hyp=sqrt(sqr(x)+1);
		const db s=x/hyp,c=1/hyp;
		return s/sqr(c)+log((1+s)/(1-s))/2;
	}
	inline db int_func(db lend,db rend,const db d){
		return sqr(d)*(int_sqrt(rend/d)-int_sqrt(lend/d))/2;
	}
	inline db calc1(const db d,db lend,db rend){
		const db r=bot_rad;
		if(d>=r)return 0;
		const db tsq=sqrt(sqr(r)-sqr(d));
		apmax(lend,-tsq);
		apmin(rend,tsq);
		if(lend>=rend)return 0;
		return rend-lend-int_func(lend,rend,d)/r;
	}
	inline void main(db d,db l,db r){
		assert(d>=0);
		ans1+=hei*calc1(d,l,r);
		ans2+=calc2(d,l,r);
	}
}
inline void work(const solve::Pt &lit,solve::Pt a,solve::Pt b){
	using namespace solve;
	const solve::Pt vec1=b-a,vec2=lit-a;
	const db len=vec1.len();
	const db dt=dot(vec1,vec2)/len;
	main(crs(vec1,vec2)/len,-dt,len-dt);
}
inline void Main(){
	using namespace solve;
	Pt lit=cgetpt();
	hei=getdb(),ang=getdb()/2*M_PI/180;
	bot_rad=hei*tan(ang);
	ans1=ans2=0;
	Pt pt1,a,b;
	for(int i=1,n=ni;i<=n;i++,a=b){
		b=cgetpt();
		if(i==1){
			pt1=b;
		}else{
			work(lit,a,b);
		}
	}
	work(lit,b,pt1);
	printf("%.10lf %.10lf\n",(double)ans1,(double)ans2);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("deep.in","r",stdin);
	freopen("deep.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
