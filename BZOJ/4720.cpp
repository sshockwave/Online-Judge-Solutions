#include <iostream>
#include <cstdio>
#include <cstring>
//#define NDEBUG
#include <cassert>
#include <cctype>
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
const int N=2010,INF=0x7f7f7f7f;
const double DINF=1e10;
namespace G{
	const int N=310;
	int n,e,dis[N][N];
	inline void init(){
		n=ni,e=ni;
	}
	inline void build(){
		memset(dis,127,sizeof(dis));
		for(int i=1;i<=n;i++){
			dis[i][i]=0;
		}
		while(e--){
			int u=ni,v=ni,w=ni;
			apmin(dis[u][v],w);
			apmin(dis[v][u],w);
		}
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				if(dis[i][k]<INF){
					for(int j=1;j<=n;j++){
						if(dis[k][j]<INF){
							apmin(dis[i][j],dis[i][k]+dis[k][j]);
						}
					}
				}
			}
		}
	}
}
int rom[N][2];
double p[N],f[N][2];
int main(){
	int n=ni,m=ni;
	G::init();
	for(int i=1;i<=n;i++){
		rom[i][0]=ni;
	}
	for(int i=1;i<=n;i++){
		rom[i][1]=ni;
	}
	for(int i=1;i<=n;i++){
		scanf("%lf",p+i);
	}
	G::build();
	for(int i=0;i<=m;i++){
		f[i][0]=f[i][1]=DINF;
	}
	f[0][0]=f[1][1]=0;
	for(int i=2;i<=n;i++){
		int cc=G::dis[rom[i-1][0]][rom[i][0]],
			cd=G::dis[rom[i-1][0]][rom[i][1]],
			dc=G::dis[rom[i-1][1]][rom[i][0]],
			dd=G::dis[rom[i-1][1]][rom[i][1]];
		for(int j=min(i,m);j>0;j--){
			f[j][0]=min(f[j][0]+cc,f[j][1]+dc*p[i-1]+cc*(1-p[i-1]));
			f[j][1]=min(f[j-1][0]+cd*p[i]+cc*(1-p[i]),f[j-1][1]+(dd*p[i]+dc*(1-p[i]))*p[i-1]+(cd*p[i]+cc*(1-p[i]))*(1-p[i-1]));
		}
		f[0][0]+=cc;
	}
	double ans=DINF;
	for(int i=0;i<=m;i++){
		apmin(ans,min(f[i][0],f[i][1]));
	}
	printf("%.2lf\n",ans);
	return 0;
}
