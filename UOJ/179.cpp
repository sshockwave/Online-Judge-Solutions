#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=22,M=N;
const double EPS=1e-8,DINF=1e100;
inline int sgn(double x){
	return x>EPS?1:x<-EPS?-1:0;
}
namespace lp{
	double ans[N+M];
	int n,m;
	double a[M][N];
	int nvar[N],mvar[M];
	inline void pivot(int x,int y){
		assert(x>=1&&x<=n);
		assert(y>=1&&y<=m);
		assert(sgn(a[y][x]));
		swap(nvar[x],mvar[y]);
		double c=-1/a[y][x];
		a[y][x]=-1;
		for(int i=0;i<=n;i++){
			a[y][i]*=c;
		}
		for(int j=0;j<=m;j++){
			if(j==y)continue;
			c=a[j][x];
			a[j][x]=0;
			for(int i=0;i<=n;i++){
				a[j][i]+=a[y][i]*c;
			}
		}
	}
	inline double delta(int i,int j){
		return sgn(a[j][i])==-1?-a[j][0]/a[j][i]*a[0][i]:DINF;
	}
	inline void simplex(){
		for(int p,q;;){
			p=q=0;
			for(int i=1;i<=n;i++){
				if(sgn(a[0][i])==1&&(p==0||nvar[i]<nvar[p])){
					p=i;
				}
			}
			if(p==0)return;
			double dt=DINF;
			for(int j=1;j<=m;j++){
				if(sgn(a[j][p])==-1){
					double cur=-a[j][0]/a[j][p];
					if(sgn(cur-dt)==0&&mvar[j]<mvar[q]){
						q=j;
					}else if(cur<dt){
						q=j,dt=cur;
					}
				}
			}
			if(q==0)throw "Unbounded";
			pivot(p,q);
		}
	}
	inline double solve(int n,int m){
		memset(nvar,0,sizeof(nvar));
		memset(mvar,0,sizeof(mvar));
		lp::n=n,lp::m=m;
		for(int i=1;i<=n;i++){
			nvar[i]=i;
		}
		for(int j=1;j<=m;j++){
			mvar[j]=n+j;
		}
		a[0][0]=0;
		int pt=1;
		for(int j=2;j<=m;j++){
			if(a[j][0]<a[pt][0]){
				pt=j;
			}
		}
		if(sgn(a[pt][0])==-1){//initialize
			static double *b=new double[N];
			memcpy(b+1,a[0]+1,sizeof(double)*n);
			memset(a[0]+1,0,sizeof(double)*n);
			a[0][++lp::n]=-1;
			for(int j=1;j<=m;j++){
				a[j][lp::n]=1;
			}
			pivot(lp::n,pt);
			simplex();
			if(sgn(a[0][0]))throw "Infeasible";
			for(int j=1;j<=m;j++){
				if(mvar[j]==0){
					for(int i=1;i<=n;i++){
						if(sgn(a[j][i])){
							pivot(i,j);
							break;
						}
					}
					break;
				}
			}
			for(int i=1;i<=lp::n;i++){
				if(nvar[i]==0){
					nvar[i]=nvar[lp::n];
					for(int j=1;j<=m;j++){
						a[j][i]=a[j][lp::n];
					}
					break;
				}
			}
			lp::n=n;
			memset(a[0],0,sizeof(double)*(n+1));
			for(int i=1;i<=n;i++){
				if(nvar[i]>n)continue;
				a[0][i]+=b[nvar[i]];
			}
			for(int j=1;j<=m;j++){
				if(mvar[j]>n)continue;
				for(int i=0;i<=n;i++){
					a[0][i]+=b[mvar[j]]*a[j][i];
				}
			}
		}
		simplex();
		memset(ans,0,sizeof(ans));
		for(int j=1;j<=m;j++){
			ans[mvar[j]]=a[j][0];
		}
		return a[0][0];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("linear.in","r",stdin);
	freopen("linear.out","w",stdout);
#endif
	int n=ni,m=ni,t=ni;
	memset(lp::a,0,sizeof(lp::a));
	for(int i=1;i<=n;i++){
		scanf("%lf",lp::a[0]+i);
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%lf",lp::a[i]+j);
			lp::a[i][j]=-lp::a[i][j];
		}
		scanf("%lf",lp::a[i]);
	}
	try{
		printf("%.10lf\n",lp::solve(n,m));
		if(t){
			for(int i=1;i<=n;i++){
				printf("%.10lf ",lp::ans[i]);
			}
			putchar('\n');
		}
	}catch(const char str[]){
		puts(str);
	}
	return 0;
}
