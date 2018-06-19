#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef /*long */double db;
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
inline db nexd(){
	db i;
	scanf("%lf",&i);
	return i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
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
}ang1,ang2;
namespace G{
	const int N=::N*2*(::N*2+1),E=(N+N)<<1;//cout
	Pt pt[N];
	int to[E],bro[E],head[N],e=0,n=0;
	db val[E];
	inline int nn(const Pt &x){
		assert(n<N);
		return ++n,pt[n]=x,head[n]=-1,n;
	}
	inline void ae(int u,int v,db w){
		assert(e<E);
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v){
		const db w=dist(pt[u],pt[v]);
		ae(u,v,w),ae(v,u,w);
	}
	inline void add_oneway(int u,int v,db ratio){
		const db w=dist(pt[u],pt[v])*ratio;
		ae(u,v,w);
	}
	struct State{
		int x;
		db d;
		inline friend bool operator < (const State &a,const State &b){
			return a.d>b.d;
		}
	};
	db dis[N];
	inline void dij(){
		for(int i=1;i<=n;i++){
			dis[i]=1e100;
		}
		priority_queue<State>q;
		q.push((State){1,dis[1]=0});
		while(!q.empty()){
			const int x=q.top().x;
			const db d=q.top().d;
			q.pop();
			if(d!=dis[x])continue;
			for(int i=head[x],v;~i;i=bro[i]){
				if(dis[v=to[i]]>dis[x]+val[i]){
					q.push((State){v,dis[v]=dis[x]+val[i]});
				}
			}
		}
	}
}
struct Line{
	Pt a,b;
	inline db len()const{return dist(a,b);}
}lin[N];
inline db ints(const Pt &x,const Pt &vec){
	if(isz(x.y))return x.x;
	return x.x+vec.x*-x.y/vec.y;
}
db pos[G::N];
vi lst[N];
inline void add_in(const int nd,const Pt &p,int n){
	for(int i=1;i<=n;i++){
		Pt vec=lin[i].b-lin[i].a;
		const db len=vec.len();
		const db revlen=1/len;
		const Pt q=Pt(dot(vec,p-lin[i].a)*revlen,-cabs(crs(vec,p-lin[i].a))*revlen);
		const db l=ints(q,ang1),r=ints(q,ang2);
		assert(l<=r);
		vec=vec*revlen;
		if(l<0){
			G::add(nd,lst[i][0]);
		}else if(l<=len){
			const int x=G::nn(lin[i].a+vec*l);
			lst[i].push_back(x);
			pos[x]=l;
			G::add(nd,x);
		}
		if(r>len){
			G::add(nd,lst[i][1]);
		}else if(r>=0){
			const int x=G::nn(lin[i].a+vec*r);
			lst[i].push_back(x);
			pos[x]=r;
			G::add(nd,x);
		}
	}
}
inline bool pos_cmp(const int &a,const int &b){
	return pos[a]<pos[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ernd.in","r",stdin);
	freopen("ernd.out","w",stdout);
#endif
	const Line p=(Line){Pt(nexd(),nexd()),Pt(nexd(),nexd())};
	const int s=G::nn(p.a),t=G::nn(p.b);
	assert(s==1&&t==2);
	int n=ni;
	const db v=nexd();
	ang1=Pt(-1,sqrt(sqr(v)-1));
	ang2=Pt(1,ang1.y);
	for(int i=1;i<=n;i++){
		lin[i]=(Line){Pt(nexd(),nexd()),Pt(nexd(),nexd())};
		lst[i].push_back(G::nn(lin[i].a)),lst[i].push_back(G::nn(lin[i].b));
		pos[lst[i][0]]=0,pos[lst[i][1]]=lin[i].len();
	}
	G::add(s,t);
	add_in(s,p.a,n),add_in(t,p.b,n);
	for(int i=1;i<=n;i++){
		add_in(lst[i][0],lin[i].a,n),add_in(lst[i][1],lin[i].b,n);
	}
	for(int i=1;i<=n;i++){
		sort(lst[i].begin(),lst[i].end(),pos_cmp);
		const db len=lin[i].len();//cout
		for(vi::iterator it=lst[i].begin(),it2=it+1,ti=lst[i].end();it2!=ti;++it,++it2){
			assert(pos[*it]>=-EPS&&pos[*it]<=len+EPS);
			G::add_oneway(*it,*it2,1/v);
		}
	}
	printf("%.10lf\n",(G::dij(),G::dis[t]));
	return 0;
}
