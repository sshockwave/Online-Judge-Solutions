#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=1010;
inline int sig(lint x){
	if(x==0){
		return 0;
	}
	return x>0?1:-1;
}
struct Point{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
	inline void in(){
		x=ni,y=ni;
	}
	typedef const Point& arg;
	inline friend Point operator + (arg a,arg b){
		return Point(a.x+b.x,a.y+b.y);
	}
	inline friend Point operator - (arg a,arg b){
		return Point(a.x-b.x,a.y-b.y);
	}
	inline friend lint dot(arg a,arg b){
		return (lint)a.x*b.x+(lint)a.y*b.y;
	}
	inline friend lint crs(arg a,arg b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
	inline friend bool itsect(arg a,arg b,arg c,arg d){//ab - cd
		return sig(crs(b-a,c-a))*sig(crs(b-a,d-a))<=0&&sig(crs(d-c,a-c))*sig(crs(d-c,b-c))<=0;
	}
	inline lint d2(){
		return dot(*this,*this);
	}
	inline friend ostream & operator << (ostream & out,Point a){
		out<<"("<<a.x<<","<<a.y<<")";
		return out;
	}
}pt[N];
struct Triangle{
	Point a,b,c;
	inline void in(){
		a.in(),b.in(),c.in();
	}
	inline void sort();
}tr[N];
inline bool ycmp(const Point &a,const Point &b){
	if(a.y==b.y){
		return a.x<b.x;
	}
	return a.y<b.y;
}
namespace W{
	Point base;
	struct Mark{
		Point pt;
		int bln;
		bool type;//true:start false:close
		inline friend bool operator < (const Mark &a,const Mark &b){
			int cr=crs(a.pt-base,b.pt-base);
			if(cr==0){
				if(a.bln&&b.bln){
					return a.type>b.type;
				}else if(a.bln==0&&b.bln==0){
					return (a.pt-base).d2()<(b.pt-base).d2();
				}else{
					return (a.bln&&a.type)||(b.bln&&(!b.type));
				}
			}
			return cr>0;
		}
	}mk[N*4];
	int ms;
	inline bool tcmp(const Point &a,const Point &b){
		return crs(a-base,b-base)>0;
	}
	struct Line{//tr[id].a&c
		int id;
		inline friend bool operator < (const Line &_a,const Line &_b){
			int a=_a.id,b=_b.id;
			if(a==b){
				return false;
			}
			if(itsect(base,tr[b].a,tr[a].a,tr[a].c)||itsect(base,tr[b].c,tr[a].a,tr[a].c)){
				return true;
			}
			if(itsect(base,tr[a].a,tr[b].a,tr[b].c)||itsect(base,tr[a].c,tr[b].a,tr[b].c)){
				return false;
			}
			return true;
		}
	};
	set<Line>line;
	inline void init(Point b){
		ms=0;
		base=b;
	}
	inline void add(const Mark &a){
		mk[ms++]=a;
	}
	inline int work(int n){//n triangles
		line.clear();
		for(int i=1;i<=n;i++){
			tr[i].sort();
			if(ycmp(base,tr[i].c)){
				add((Mark){tr[i].c,i,false});
				if(ycmp(base,tr[i].a)){
					add((Mark){tr[i].a,i,true});
				}else{
					line.insert((Line){i});
				}
			}else if(ycmp(base,tr[i].a)){
				add((Mark){tr[i].a,i,true});
			}
		}
		sort(mk,mk+ms);
		int ans=0;
		for(int i=0;i<ms;i++){
			if(mk[i].bln){
				if(mk[i].type){
					line.insert((Line){mk[i].bln});
				}else{
					line.erase((Line){mk[i].bln});
				}
			}else{
				int tp=line.begin()->id;
				if(line.size()==0||!itsect(base,mk[i].pt,tr[tp].a,tr[tp].c)){
					ans++;
				}
			}
		}
		return ans;
	}
}
inline void Triangle::sort(){
	if(W::tcmp(c,b)){swap(b,c);}
	if(W::tcmp(b,a)){swap(a,b);}
	if(W::tcmp(c,b)){swap(b,c);}
}
int main(){
	int n=ni,t=ni;
	for(int i=1;i<=n;i++){
		pt[i].in();
	}
	for(int i=1;i<=t;i++){
		tr[i].in();
	}
	sort(pt+1,pt+n+1,ycmp);
	int ans=0;
	for(int i=1;i<n;i++){
		W::init(pt[i]);
		for(int j=i+1;j<=n;j++){
			W::add((W::Mark){pt[j],0,false});
		}
		ans+=W::work(t);
	}
	printf("%d\n",ans);
}