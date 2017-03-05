#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define EPS 1e-8
#define N 510
#define INF 0x30303030
using namespace std;
struct coor{
	double x,y;
}src[N],need[N];
coor operator - (coor a,coor b){
	return (coor){a.x-b.x,a.y-b.y};
}
double operator * (coor a,coor b){
	return a.x*b.y-b.x*a.y;
}
bool con[N][N];
int dis[N][N],m,n;
inline void apmin(int &a,int b){
	assert(b>=0);
	if(a>b){
		a=b;
	}
}
inline bool is_zero(double x){
	return x>=-EPS&&x<=EPS;
}
inline bool is_zero(coor x){
	return is_zero(x.x)&&is_zero(x.y);
}
inline bool judge(coor vec,coor p){
	if(is_zero(vec)){
		return false;
	}
	for(int i=0;i<n;i++){
		if(vec*(need[i]-p)<-EPS){
			return false;
		}
	}
	return true;
}
int main(){
	scanf("%d%d",&m,&n);
	float tmp;
	for(int i=0;i<m;i++){
		scanf("%lf%lf%lf",&src[i].x,&src[i].y,&tmp);
	}
	for(int i=0;i<n;i++){
		scanf("%lf%lf%lf",&need[i].x,&need[i].y,&tmp);
	}
	memset(con,0,sizeof(con));
	memset(dis,48,sizeof(dis));
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			if(judge(src[j]-src[i],src[i])){
				con[i][j]=true;
				dis[i][j]=1;
			}
		}
	}
	int ans=INF;
	for(int k=0;k<m;k++){
		for(int i=0;i<m;i++){
			if(con[i][k]){
				for(int j=0;j<m;j++){
					if(con[k][j]){
						apmin(ans,dis[j][i]+2);
					}
				}
			}
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				apmin(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	if(ans==INF){
		puts("-1");
	}else{
		printf("%d",ans);
	}
}
