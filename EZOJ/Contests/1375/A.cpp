#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef double db;
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
const int N=210,K=16;
const db EPS=1e-8,DINF=1e100;
inline int sig(db x){
	return x<-EPS?-1:x>EPS;
}
namespace lp{
	const int N=::N,M=::N*3;
	db a[M][N];
	int nvar[N],mvar[M];
	int n,m;
	inline void pivot(int x,int y){
		swap(nvar[x],mvar[y]);
		db c=-1/a[y][x];
		a[y][x]=-1;
		for(int i=0;i<=n;i++){
			a[y][i]*=c;
		}
		for(int j=0;j<=m;j++){
			if(j==y)continue;
			c=a[j][x],a[j][x]=0;
			for(int i=0;i<=n;i++){
				a[j][i]+=a[y][i]*c;
			}
		}
	}
	inline void simplex(){
		while(true){
			int p=0,q=0;
			for(int i=1;i<=n;i++){
				if(sig(a[0][i])==1&&(p==0||nvar[i]<nvar[p])){
					p=i;
				}
			}
			if(p==0)return;
			double dt=DINF;
			for(int j=1;j<=m;j++){
				if(sig(a[j][p])==-1){
					apmin(dt,-a[j][0]/a[j][p]);
				}
			}
			for(int j=1;j<=m;j++){
				if(sig(a[j][p])==-1&&sig(dt+a[j][0]/a[j][p])==0&&(q==0||mvar[j]<mvar[q])){
					q=j;
				}
			}
			if(q==0)return;
			pivot(p,q);
		}
	}
}
bool prefill[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("prince.in","r",stdin);
	freopen("prince.out","w",stdout);
#endif
	int n=ni,len=ni;
	int r=len-ni,l=ni;
	for(int i=1;i<=l;i++){
		prefill[i]=1;
	}
	for(int i=l+1;i<=len;i++){
		prefill[i]=0;
	}
	for(int i=len+1;i<=n;i++){
		prefill[i]=prefill[i-len];
	}
	{//lp init
		lp::n=n,lp::m=0;
		using namespace lp;
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			int x=ni,y=ni;
			a[0][0]+=x;
			a[0][i]=y-x;
		}
		for(int i=1;i<=n;i++){
			m++;
			a[m][0]=1;
			a[m][i]=-1;
		}
		for(int lend=1,rend=len;rend<=n;lend++,rend++){
			a[++m][0]=r;
			for(int j=lend;j<=rend;j++){
				a[m][j]=-1;
			}
			a[++m][0]=-l;
			for(int j=lend;j<=rend;j++){
				a[m][j]=1;
			}
		}
		for(int i=1;i<=n;i++){
			nvar[i]=i;
		}
		for(int j=1;j<=m;j++){
			mvar[j]=j+n;
		}
		for(int i=1;i<=n;i++){
			if(prefill[i]){
				pivot(i,i);
			}
		}
	}
	lp::simplex();
	printf("%d\n",(int)(lp::a[0][0]+1e-8));
	return 0;
}
