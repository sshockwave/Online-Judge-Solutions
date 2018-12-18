#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef double db;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
inline char get_c(){
	const static int N=5000000;
	static char *h,*t,buf[N];
	if(h==t){
		h=buf,t=buf+fread(buf,1,N,stdin);
		if(h==t)return EOF;
	}
	return *h++;
}
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=get_c()));
	while(i=i*10-'0'+c,isdigit(c=get_c()));
	return i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=3010,M=310;
int n,m;
db p[M][N],f[M][N],g[N];
struct State{
	int idx;
	db v;
	inline friend bool operator < (const State &a,const State &b){
		return a.v<b.v;
	}
};
priority_queue<State>q;
int pos[N];
inline void step(int x,bool flag){
	const db EPS=1e-10;
	db last;
	if(flag){
		last=0;
		f[x][0]=1;
	}else{
		int &j=pos[x];
		for(;j<=n&&f[x][j]<EPS;j++);
		if(j>n)return;
		last=f[x][j];
		f[x][j]=0;
	}
	for(int i=pos[x]+1;i<=n;i++){
		db tmp=f[x][i];
		f[x][i]=(1-p[x][i])*f[x][i-1]+p[x][i]*last;
		last=tmp;
	}
	g[x]+=f[x][n];
	if(1-g[x]>EPS){
		q.push((State){x,1-g[x]});
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
#endif
	n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			p[j][i]=(db)ni/1000;
		}
	}
	for(int i=1;i<=m;i++){
		g[i]=0;
		pos[i]=0;
		step(i,true);
	}
	db ans=0;
	for(int tot=n;tot--;){
		int x=q.top().idx;
		ans+=q.top().v;
		q.pop();
		step(x,false);
	}
	printf("%.10lf\n",ans);
	return 0;
}
