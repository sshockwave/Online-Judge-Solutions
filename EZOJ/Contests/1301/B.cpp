#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef long double ld;
#define cout cerr
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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=35;
const double EPS=1e-6;
struct Point{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
	inline void operator += (const Point &b){
		x+=b.x,y+=b.y;
	}
	inline friend Point operator + (const Point &a,const Point &b){
		return Point(a.x+b.x,a.y+b.y);
	}
	inline friend Point operator - (const Point &a,const Point &b){
		return Point(a.x-b.x,a.y-b.y);
	}
	inline friend Point operator * (const Point &a,const double &b){
		return Point(a.x*b,a.y*b);
	}
	inline friend Point operator / (const Point &a,const double &b){
		return Point(a.x/b,a.y/b);
	}
	inline friend double dot(const Point &a,const Point &b){
		return a.x*b.x+a.y*b.y;
	}
	inline friend double cross(const Point &a,const Point &b){
		return a.x*b.y-a.y*b.x;
	}
	inline friend bool turn_left(const Point &a,const Point &b,const Point &c){
		return cross(b-a,c-a)>-EPS;
	}
	inline friend Point vtimes(const Point &a,const Point &b){
		return Point(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
	}
	inline void in(){
		x=ni,y=ni;
	}
	inline double dis2(){
		return dot(*this,*this);
	}
}sun,planet,pt[N];
inline ostream & operator << (ostream & out,const Point &a){
	out<<"("<<a.x<<","<<a.y<<")";
	return out;
}
int main(){
	freopen("planet.in","r",stdin);
	freopen("planet.out","w",stdout);
	sun.in(),planet.in();
	int R=ni,n=ni,t1=ni,t2=ni,t=ni,sumx=0,sumy=0;
	double ang1=M_PI*2*t/t1,ang2=M_PI*2*t/t2;
	for(int i=1;i<=n;i++){
		int x=ni,y=ni;
		sumx+=x,sumy+=y;
		pt[i].x=x,pt[i].y=y;
		cout<<"pt["<<i<<"]="<<pt[i]<<endl;
	}
	Point g((double)sumx/n,(double)sumy/n),d(cos(ang2),sin(ang2));
	cout<<"g="<<g<<endl;
	for(int i=1;i<=n;i++){
		pt[i]=vtimes(pt[i]-g,d);
	}
	g=vtimes(g-planet,Point(cos(ang1),sin(ang1)))+planet;
	cout<<"ng:"<<g<<endl;
	for(int i=1;i<=n;i++){
		pt[i]+=g;
	}
	Point lmost,rmost;
	d=planet-sun;
	double dis2=d.dis2(),dis=sqrt(dis2);
	{//cal lmost,rmost
		lmost.x=rmost.x=(dis2-R*R)/dis;
		lmost.y=sqrt((ld)R*R-(ld)R*R/dis2*R*R);
		rmost.y=-lmost.y;
		lmost=vtimes(d,lmost)/dis+sun;
		rmost=vtimes(d,rmost)/dis+sun;
	}
	Point cur=rmost;
	double ans=0;
	bool flag=true;
	for(int i=1;i<=n;i++){
		if(turn_left(sun,lmost,pt[i])){
			flag=false;
			break;
		}
		if(turn_left(sun,rmost,pt[i])&&turn_left(sun,cur,pt[i])&&(pt[i]-sun).dis2()<=dis2){
			cur=pt[i];
		}
	}
	if(flag){//tochange
		Point p=cur-sun;
		double cr=cross(d,p);
		Point join=(Point(-p.y,p.x)*cr-p*sqrt(R*R*p.dis2()-cr*cr))/p.dis2()-planet;
		cout<<"Join:"<<join<<endl;
		ans+=acos(dot(join,lmost-planet))*R;
	}
	cur=lmost;
	flag=true;
	for(int i=1;i<=n;i++){
		if(!turn_left(sun,rmost,pt[i])){
			flag=false;
			break;
		}
		cout<<"pt["<<i<<"]="<<pt[i]<<endl;
		if(!turn_left(sun,lmost,pt[i])&&!turn_left(sun,cur,pt[i])&&(pt[i]-sun).dis2()<=dis2){
			cur=pt[i];
		}
	}
	if(flag){
		Point p=cur-sun;
		double cr=cross(d,p);
		double dist=cr/sqrt(p.dis2()),rev=sqrt(R*R-dist*dist);
		Point rot(-p.y,p.x);
		Point fin=planet+rot/sqrt(rot.dis2())*dist-p*rev/sqrt(p.dis2());
		ans+=acos(dot(fin-planet,rmost-planet)/R/R)*R;
	}
	cout<<ans<<endl;
	printf("%.2lf\n",ans);
	return 0;
}