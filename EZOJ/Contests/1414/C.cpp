#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=62,INF=0x7f7f7f7f;
int n,ans=INF;
namespace km{//maximize
	int val[N][N];
	int lnk1[N],lnk2[N];
	int lab1[N],lab2[N];
	int sla[N],pre[N];
	bool vis1[N],vis2[N];
	inline void bfs(int x){
		memset(sla,127,(n+1)*sizeof(sla[0]));
		memset(vis1+1,0,n*sizeof(vis1[0]));
		memset(vis2+1,0,n*sizeof(vis2[0]));
		int y;
		do{
			vis1[x]=true;
			y=0;
			for(int i=1;i<=n;i++){
				if(vis2[i])continue;
				int td=lab1[x]+lab2[i]-val[x][i];
				if(td<sla[i]){
					sla[i]=td,pre[i]=x;
				}
				if(sla[i]<sla[y]){
					y=i;
				}
			}
			int d=sla[y];
			for(int i=1;i<=n;i++){
				if(vis1[i]){
					lab1[i]-=d;
				}
				if(vis2[i]){
					lab2[i]+=d;
				}else{
					sla[i]-=d;
				}
			}
			vis2[y]=true;
		}while((x=lnk2[y]));
		for(;y;lnk2[y]=pre[y],swap(y,lnk1[pre[y]]));
	}
}
struct Pt{
	int x,y;
	inline friend bool operator == (const Pt &a,const Pt &b){return a.x==b.x&&a.y==b.y;}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend int crs(const Pt &a,const Pt &b){return a.x*b.y-a.y*b.x;}
}mat[N][N];
inline Pt eval(){
	using namespace km;
	memset(lnk1+1,0,n*sizeof(lnk1[0]));
	memset(lnk2+1,0,n*sizeof(lnk2[0]));
	memset(lab1+1,128,n*sizeof(lab1[0]));
	memset(lab2+1,0,n*sizeof(lab2[0]));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			apmax(lab1[i],val[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		if(lnk1[i]==0){
			bfs(i);
		}
	}
	Pt sum=(Pt){0,0};
	for(int i=1;i<=n;i++){
		sum=sum+mat[i][lnk1[i]];
	}
	apmin(ans,sum.x*sum.y);
	return sum;
}
inline void solve(const Pt a,const Pt b){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			km::val[i][j]=crs(mat[i][j]-a,b-a);
		}
	}
	Pt c=eval();
	if(c==a||c==b)return;
	solve(a,c),solve(c,b);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mat[i][j].x=ni;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mat[i][j].y=ni;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			km::val[i][j]=-mat[i][j].x;
		}
	}
	Pt a=eval();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			km::val[i][j]=mat[i][j].x;
		}
	}
	Pt b=eval();
	solve(a,b);
	printf("%d\n",ans);
	return 0;
}
