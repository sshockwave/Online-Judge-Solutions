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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=510,N2=N*N,INF=0x7f7f7f7f;
struct Pt{
	int x,y;
	inline lint d2(){
		return x*x+y*y;
	}
	inline friend bool operator < (const Pt &a,const Pt &b){
		return true;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){
		return (Pt){a.x-b.x,a.y-b.y};
	}
}pt[N],base,vc[N][N];
int node[N][N],ns;
int nxt[N2][33];
double sum[N2][33];
inline int ask(int x,Pt vec){//return first encountered node
	return 1;
}
Pt sur[N];
int lst[N],tonode[N];
inline void Main(){
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	ns=0;
	for(int i=1;i<=n;i++){
		Pt *vec=vc[i];
		int vcs=0;
		for(int j=1;j<=n;j++){
			if(i!=j){
				vec[++vcs]=pt[j]-pt[i];
				node[i][vcs]=++ns;
			}
		}
		assert(vcs==n-1);
		sort(vec+1,vec+vcs+1);
	}
	for(int i=1;i<=n;i++){
		int vcs=0;
		for(int j=1;j<=n;j++){
			if(i!=j){
				vcs++;
				nxt[node[i][vcs]][0]=ask(j,vc[i][vcs]);
				sum[node[i][vcs]][0]=sqrt(vc[i][vcs].d2());
			}
		}
	}
	for(int j=0;j<32;j++){
		for(int i=1;i<=ns;i++){
			if(sum[i][j]<INF){//tocheck
				nxt[i][j+1]=nxt[nxt[i][j]][j];
				sum[i][j+1]=sum[i][j]+sum[nxt[i][j]][j];
			}
		}
	}
	while(tot--){
		Pt s=(Pt){ni,ni};
		Pt t=(Pt){ni,ni};
		lint l=ni,l2=l*l;
		int ss=0;
		for(int i=1;i<=n;i++){
			if((pt[i]-s).d2()<=l2){
				sur[++ss]=pt[i]-s;
				tonode[ss]=i;
				lst[ss]=ss;
			}
		}
		sort(lst+1,lst+ss+1,lcmp);
		Pt dt=t-s;
		if(dt.d2()<=l2){
			int b=sqrt(l2/dt.d2())+1;
			dt.x*=b,dt.y*=b;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
