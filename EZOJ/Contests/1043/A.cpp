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
template<class T>inline T sqr(T x){
	return x*x;
}
const int N=25;
int n,es=0;
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
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}e[N*N];
double dis[N][N],dis2[N][N];
inline double work(double avg){
	for(int i=1;i<=es;i++){
		e[i].w=sqr(dis[e[i].u][e[i].v]-avg);
	}
	sort(e+1,e+es+1);
	memset(fa+1,0,n<<2);
	double val1=0,val2=0;
	for(int i=1;i<=es;i++){
		if(root(e[i].u)!=root(e[i].v)){
			fa[root(e[i].u)]=root(e[i].v);
			val1+=dis2[e[i].u][e[i].v];
			val2+=dis[e[i].u][e[i].v];
		}
	}
	return val1*(n-1)-val2*val2;
}
double x[N],y[N];
inline double Main(){
	n=ni,es=0;
	for(int i=1;i<=n;i++){
		scanf("%lf",x+i);
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",y+i);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			dis2[i][j]=sqr(x[i]-x[j])+sqr(y[i]-y[j]);
			dis[i][j]=sqrt(dis2[i][j]);
			e[++es]=(Edge){i,j};
		}
	}
	assert(es==n*(n-1)/2);
	double ans=1e100;
	for(int i=1;i<=es;i++){
		for(int j=1;j<=i;j++){
			apmin(ans,work((dis[e[i].u][e[i].v]+dis[e[j].u][e[j].v])/2));
		}
	}
	return sqrt(ans)/(n-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%.3lf\n",Main()));
	return 0;
}
