#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=410,T=1;
int n;
struct Pt{
#define Pt(x,y) ((Pt){x,y})
	int x,y;
	inline int d2(){return x*x+y*y;}
	inline friend Pt operator + (const Pt &a,const Pt &b){return Pt(a.x+b.x,a.y+b.y);}
	inline friend Pt operator - (const Pt &a,const Pt &b){return Pt(a.x-b.x,a.y-b.y);}
}pt[N];
int d2[N][N];
struct Edge{
	int u,v,w;
	inline friend bool operator < (const Edge &a,const Edge &b){
		return a.w<b.w;
	}
}edg[N*N],edglst[T][N*N];
bool deci[N*N];
namespace djset{
	int fa[N];
	inline int grt(int x){
		return fa[x]?fa[x]=grt(fa[x]):x;
	}
}
int dislst[N][N],dispt[N];
int aff[N];
inline bool check(const int mx){
	const int es=n*(n-1)/2;
	for(int tt=0;tt<=T;tt++){
		Edge *edg;
		if(tt==0){
			edg=::edg;
			sort(edg+1,edg+es+1);
		}else{
			edg=::edglst[tt-1];
		}
		for(int i=1;i<=n;i++){
			djset::fa[i]=0;
			aff[i]=1;
			for(int &j=dispt[i]=1;j<=n&&d2[i][dislst[i][j]]<=0;j++);
		}
		int cnt=0;
		for(int i=1;i<es;i++){
			deci[i]=false;
			const int u=edg[i].u,v=edg[i].v,w=edg[i].w;
			using djset::grt;
			if(grt(u)==grt(v))continue;
			bool flag=true;
			int tj1,tj2;
			for(int &j=tj1=dispt[u];j<=n&&d2[u][dislst[u][j]]<=w;j++){
				if(++aff[dislst[u][j]]>mx){
					flag=false;
					for(;j>=dispt[u];j--){
						--aff[dislst[u][j]];
					}
					break;
				}
			}
			if(!flag)continue;
			for(int &j=tj2=dispt[v];j<=n&&d2[v][dislst[v][j]]<=w;j++){
				if(++aff[dislst[v][j]]>mx){
					flag=false;
					for(;j>=dispt[v];j--){
						--aff[dislst[v][j]];
					}
					break;
				}
			}
			if(!flag){
				for(int j=dispt[u];j<=n&&d2[u][dislst[u][j]]<=w;j++){
					--aff[dislst[u][j]];
				}
				continue;
			}
			++cnt;
			deci[i]=true;
			djset::fa[grt(u)]=grt(v);
			dispt[u]=tj1,dispt[v]=tj2;
		}
		if(cnt==n-1)return true;
	}
	return false;
}
int base;
inline bool discmp(int a,int b){
	return d2[base][a]<d2[base][b];
}
inline void Main(const int n){
	::n=n;
	int es=0;
	for(int i=1;i<=n;i++){
		pt[i]=Pt(ni,ni);
		d2[i][i]=0;
		for(int j=1;j<i;j++){
			d2[j][i]=d2[i][j]=(pt[i]-pt[j]).d2();
			edg[++es]=(Edge){i,j,d2[i][j]};
		}
	}
	//input complete
	if(n==1)return;
	sort(edg+1,edg+es+1);
	for(int i=0;i<T;i++){
		for(int j=1;j<=es;j++){
			edglst[i][j]=edg[j];
		}
		random_shuffle(edglst[i]+1,edglst[i]+es+1);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dislst[i][j]=j;
		}
		base=i;
		sort(dislst[i]+1,dislst[i]+n+1,discmp);
	}
	int l=2,r=min(n,8);
	while(l<r){
		const int m=(l+r)>>1;
		if(check(m)){
			r=m;
		}else{
			l=m+1;
		}
	}
	bool flag=check(l);
	assert(flag);
	for(int i=1;i<=n*(n-1)/2;i++){
		if(deci[i]){
			printf("%d %d\n",edg[i].u,edg[i].v);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chaw.in","r",stdin);
	freopen("chaw.out","w",stdout);
#endif
	srand(time(0));
	int n;
	for(;scanf("%d",&n)!=EOF;){
		Main(n);
	}
	return 0;
}
