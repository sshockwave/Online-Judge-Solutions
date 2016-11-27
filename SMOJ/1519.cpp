#include <iostream>
#include <cstdio>
#include <cstring>
#define INF 0x7f7f7f7f
#define N 20
#define EPS 1e-9
using namespace std;
double x[N],y[N];
int n,m,ltop,ans,bln1[N],bln2[N];
inline bool eqzero(double a){
	return a>=-EPS&&a<=EPS;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline double cal(int x2,int y2,int x3,int y3,int x4,int y4){
	return y2*x3*x4*(x3-x4)+y3*x2*x4*(x4-x2)+y4*x2*x3*(x2-x3);
}
inline double cala(double x1,double y1,double x2,double y2){
	double b=(y2*x1*x1-y1*x2*x2)/(x2*x1*x1-x1*x2*x2);
	return (y1-b*x1)/(x1*x1);
}
void dfs(int p){
	if(p==n+1){
//		if(ltop<ans){
//			cout<<"Result:";
//			for(int i=0;i<ltop;i++){
//				cout<<"("<<bln1[i]<<","<<bln2[i]<<")";
//			}
//			cout<<endl;
//		}
		apmin(ans,ltop);
		return;
	}
	for(int i=0;i<ltop;i++){
		/*
		if(bln2[i]!=0&&eqzero(cal(x[p],y[p],x[bln1[i]],y[bln1[i]],x[bln2[i]],y[bln2[i]]))){
			cout<<"same "<<cala(x[p],y[p],x[bln1[i]],y[bln1[i]])<<" with "<<cala(x[p],y[p],x[bln2[i]],y[bln2[i]])<<endl;
			dfs(p+1);
			return;
		}*/
		if(bln2[i]!=0&&eqzero(cala(x[p],y[p],x[bln1[i]],y[bln1[i]])-cala(x[p],y[p],x[bln2[i]],y[bln2[i]]))){
//			cout<<"same "<<cala(x[p],y[p],x[bln1[i]],y[bln1[i]])<<" with "<<cala(x[p],y[p],x[bln2[i]],y[bln2[i]])<<endl;
			dfs(p+1);
			return;
		}
	}
	for(int i=0;i<ltop;i++){
		if(bln2[i]==0&&!eqzero(x[bln1[i]]-x[p])&&cala(x[p],y[p],x[bln1[i]],y[bln1[i]])<0){
			bln2[i]=p;
			dfs(p+1);
			bln2[i]=0;
		}
	}
	bln1[ltop++]=p;
	dfs(p+1);
	bln1[--ltop]=0;
}
int main(){
//	freopen("angrybirds1.in","r",stdin);
	freopen("angrybirds.in","r",stdin);
	freopen("angrybirds.out","w",stdout);
	int tot;
	for(scanf("%d",&tot);tot--;){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",x+i,y+i);
		}
		ltop=0;
		ans=INF;
		dfs(1);
		printf("%d\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
}
