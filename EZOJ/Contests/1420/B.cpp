#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=78*23,INF=0x7f7f7f7f;
int totflow;
namespace G{
	const int N=::N*::N*2,E=N*4*2;
	int to[E],bro[E],cap[E],val[E],head[N],e=0,n=0,s,t;
	inline int nn(){
		n++;
		head[n]=-1;
		return n;
	}
	inline void init(){
		s=nn(),t=nn();
	}
	inline void ae(int u,int v,int c,int w){
		to[e]=v,bro[e]=head[u],cap[e]=c,val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int c,int w){
		ae(u,v,c,w),ae(v,u,0,-w);
	}
	struct state{
		int x,d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	int dis[N];
	inline void dij(){
		mset(dis+1,127,n);
		priority_queue<state>q;
		q.push((state){s,dis[s]=0});
		while(!q.empty()){
			int x=q.top().x,d=q.top().d;
			q.pop();
			if(d>dis[x])continue;
			if(d>dis[t])break;
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]){
					q.push((state){v,dis[v]=dis[x]+val[i]});
				}
			}
		}
	}
	int vis[N],tim=0;
	int aug(int x,int a){
		if(x==t||a==0)return a;
		vis[x]=tim;
		int r=a,d;
		for(int i=head[x],v;~i;i=bro[i]){
			if(cap[i]&&dis[v=to[i]]==dis[x]+val[i]&&vis[v]<tim){
				d=aug(v,min(r,cap[i]));
				cap[i]-=d,cap[i^1]+=d,r-=d;
				if(r==0)break;
			}
		}
		return a-r;
	}
	inline void mcmf(){
		for(int flow=0,cost=0;dij(),dis[t]<INF;){
			++tim;
			int dt=aug(s,INF);
			cout<<"                                                  \r";
			cout<<"flow+="<<dt<<"\tper cost="<<dis[t]<<"\t"<<((double)flow/totflow*100)<<"%\r";
			flow+=dt;
			cost+=dt*dis[t];
		}
	}
}
int mat[N][N];
int nd[N][N];
int te[N][N][5];
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
int main(){
	int n=ni,d=ni,len=(n+1)*d;
	totflow=n*n;
	G::init();
	for(int i=1;i<len;i++){
		for(int j=1;j<len;j++){
			nd[i][j]=G::nn();
		}
	}
	for(int i=1;i<len;i++){
		for(int j=1;j<len;j++){
			int ou=G::nn();
			G::add(i%d==0&&j%d==0?G::s:nd[i][j],ou,1,0);
			for(int d=1;d<=4;d++){
				int x=i+dx[d],y=j+dy[d];
				te[i][j][d]=G::e;
				if(x<1||x>=len||y<1||y>=len){
					G::add(ou,G::t,1,1);
				}else{
					G::add(ou,nd[x][y],1,1);
				}
			}
		}
	}
	G::mcmf();
	cout<<"                                                  \r";
	cout<<"Finished. Outputting"<<endl;
	for(int i=0;i<=len;i++){
		for(int j=0;j<=len;j++){
			if(i<1||i>=len||j<1||j>=len){
				putchar('0'),putchar(' ');
			}else{
				int d;
				for(d=1;d<=4;d++){
					if(G::cap[te[i][j][d]]==0)break;
				}
				if(d>4){
					d=0;
				}
				putchar('0'+d),putchar(' ');
			}
		}
		putchar('\n');
	}
	return 0;
}
