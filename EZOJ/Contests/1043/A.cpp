#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=25;
const double EPS=1e-8;
struct Point{
	double x,y;
	inline friend Point operator - (const Point &a,const Point &b){
		return (Point){a.x-b.x,a.y-b.y};
	}
	inline double d2(){
		return x*x+y*y;
	}
}pt[N];
int n,es=0;
double dis[N][N],dis2[N][N];
int fa[N];
inline int root(int x){
	if(fa[x]==0){
		return x;
	}
	return fa[x]=root(fa[x]);
}
struct Edge{
	int u,v;
	double w;
	bool vis;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}e[N*N];
inline double calc(double sumx){
	for(int i=1;i<=es;i++){
		e[i].w=dis2[e[i].u][e[i].v]*(n-1)-dis[e[i].u][e[i].v]*sumx;
		e[i].vis=false;
	}
	sort(e+1,e+es+1);
	memset(fa+1,0,n<<2);
	double asum=0;
	for(int i=1;i<=es;i++){
		int u=root(e[i].u),v=root(e[i].v);
		if(u!=v){
			e[i].vis=true;
			asum+=dis[e[i].u][e[i].v];
			fa[u]=v;
		}
	}
	return asum;
}
namespace task1{
	double ans,val1,val2;
	bool con[N][N];
	int fa[N];
	inline int root(int x){
		if(fa[x]==0){
			return x;
		}
		return fa[x]=root(fa[x]);
	}
	inline bool check(){
		memset(fa+1,0,n<<2);
		for(int i=1;i<=n;i++){
			for(int j=1;j<i;j++){
				if(con[i][j]){
					int u=root(i),v=root(j);
					if(u==v){
						return false;
					}
					fa[u]=v;
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(root(i)!=root(1)){
				return false;
			}
		}
		return true;
	}
	void dfs(int x,int y,int cnt){
		if(x==y){
			x++,y=1;
		}
		if(x>n){
			if(cnt==0&&check()){
				apmin(ans,val1*(n-1)-val2*val2);
			}
			return;
		}
		if(cnt){
			con[x][y]=con[y][x]=true,val1+=dis2[x][y],val2+=dis[x][y];
			dfs(x,y+1,cnt-1);
			con[x][y]=con[y][x]=false,val1-=dis2[x][y],val2-=dis[x][y];
		}
		dfs(x,y+1,cnt);
	}
	inline double Main(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=j){
					dis2[i][j]=(pt[i]-pt[j]).d2();
					dis[i][j]=sqrt(dis2[i][j]);
				}
			}
		}
		ans=1e100;
		memset(con,0,sizeof(con));
		val1=0,val2=0;
		dfs(1,1,n-1);
		return sqrt(ans)/(n-1);
	}
}
inline double Main(){
	n=ni,es=0;
	for(int i=1;i<=n;i++){
		scanf("%lf",&pt[i].x);
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",&pt[i].y);
	}
	if(n<=5){
		return task1::Main();
	}
	double l=0,r=0,m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis2[i][j]=(pt[i]-pt[j]).d2();
			dis[i][j]=sqrt(dis2[i][j]);
			r+=dis[i][j];
			if(i<j){
				e[++es]=(Edge){i,j};
			}
		}
	}
	assert(es==n*(n-1)/2);
	while(r-l>EPS){
		m=(l+r)/2;
		if(calc(m)<m){//tocheck
			l=m;
		}else{
			r=m;
		}
	}
	calc(l);
	double val1=0,val2=0;
	for(int i=1;i<=n;i++){
		if(e[i].vis){
			val1+=dis2[e[i].u][e[i].v];
			val2+=dis[e[i].u][e[i].v];
		}
	}
	return sqrt(max((n-1)*val1-val2*val2,0.0))/(n-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%.3lf\n",Main()));
	return 0;
}
