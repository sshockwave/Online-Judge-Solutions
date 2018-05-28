#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T sqr(const T &x){return x*x;}
const int N=110;
const db EPS=1e-5,ZERO=0;
struct Pt{
	db x,y;
	inline db d2(){
		return x*x+y*y;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){
		return (Pt){a.x-b.x,a.y-b.y};
	}
}pt[N];
db dis[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("restore.in","r",stdin);
	freopen("restore.out","w",stdout);
#endif
	int n=ni;
	int a=0,b=0,c=0;
	db v=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			double tmp;
			scanf("%lf",&tmp);
			dis[i][j]=tmp;
			if(dis[i][j]>v){
				a=i,b=j,v=dis[i][j];
			}
		}
	}
	pt[a]=(Pt){0,0};
	pt[b]=(Pt){v,0};
	for(int i=1;i<=n;i++){
		if(dis[a][i]<=EPS){
			pt[i]=pt[a];
		}else if(dis[b][i]<=EPS){
			pt[i]=pt[b];
		}else{
			db r1=dis[a][i],r2=dis[b][i];
			if(cabs(r1+r2-v)<=EPS){
				pt[i]=(Pt){r1,0};
			}else{
				Pt pt1,pt2;
				pt1.x=pt2.x=(pt[b].x+(sqr(r1)-sqr(r2))/pt[b].x)/2;
				pt1.y=sqrt(max(r1*r1-sqr(pt1.x),ZERO)),pt2.y=-pt1.y;
				if(c==0){
					pt[c=i]=pt1;
				}else{
					db d2=sqr(dis[c][i]);
					pt[i]=cabs((pt1-pt[c]).d2()-d2)<=cabs((pt2-pt[c]).d2()-d2)?pt1:pt2;
				}
				assert(cabs(sqrt((pt[i]-pt[c]).d2())-dis[i][c])<=1e-3);
			}
			assert(cabs(sqrt((pt[i]-pt[a]).d2())-dis[i][a])<=1e-3);
			assert(cabs(sqrt((pt[i]-pt[b]).d2())-dis[i][b])<=1e-3);
		}
		printf("%.10lf %.10lf\n",double(pt[i].x),double(pt[i].y));
	}
	for(int i=1;i<=n;i++){//cout
		for(int j=1;j<=n;j++){
			assert(cabs(sqrt((pt[i]-pt[j]).d2())-dis[i][j])<=1e-3);
		}
	}
	return 0;
}
