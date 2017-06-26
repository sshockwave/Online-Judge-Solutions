#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=110,INF=0x7f7f7f7f;
const double EPS=1e-8,DINF=1e100;
int lnk[N];
struct Graph{
	static const int D=N*2,E=N*N*2;
	int to[E],bro[E],cap[E],head[D],etop;
	double val[E];
	inline void reset(){
		memset(head,-1,sizeof(head));
		etop=0;
	}
	inline void add_edge(int u,int v,int c,double w){
		to[etop]=v;
		bro[etop]=head[u];
		cap[etop]=c;
		val[etop]=w;
		head[u]=etop++;
	}
	inline void add(int u,int v,int c,double w){
		add_edge(u,v,c,w);
		add_edge(v,u,0,-w);
	}
	double dis[D];
	int que[D],pre[D];
	bool inque[D];
	inline bool spfa(int s,int t){
		memset(pre,-1,sizeof(pre));
		memset(inque,0,sizeof(inque));
		for(int i=s+1;i<=t;i++){
			dis[i]=DINF;
		}
		dis[s]=0;
		int qhead=0,qtail=0;
		que[qtail++]=s;
		inque[s]=true;
		bool flag=false;
		while(qhead!=qtail){
			int x=que[qhead++];
			if(qhead==D){
				qhead=0;
			}
			if(x==t){
				flag=true;
				//continue;
			}
			for(int i=head[x],v;~i;i=bro[i]){
				if(cap[i]&&dis[v=to[i]]>dis[x]+val[i]+EPS){
					dis[v]=dis[x]+val[i];
					pre[v]=i^1;
					if(!inque[v]){
						inque[v]=true;
						que[qtail++]=v;
						if(qtail==D){
							qtail=0;
						}
					}
				}
			}
			inque[x]=false;
		}
		return flag;
	}
	inline double mcmf(int s,int t){
		double cost=0;
		while(spfa(s,t)){
			cost+=dis[t];
			for(int p=pre[t];~p;p=pre[to[p]]){
				cap[p]++,cap[p^1]--;
			}
		}
		return cost;
	}
	inline void getlnk(int n){
		int dn=n<<1;
		for(int x=1;x<=n;x++){
			for(int i=head[x],v;~i;i=bro[i]){
				v=to[i];
				if(v>n&&v<=dn&&cap[i]<INF){
					lnk[x]=v-n;
					break;
				}
			}
		}
	}
}G;
int a[N][N],b[N][N];
inline double check(double c,int n){
	int s=0,t=(n<<1)|1;
	G.reset();
	for(int i=1;i<=n;i++){
		G.add(s,i,1,0);
		G.add(i+n,t,1,0);
		for(int j=1;j<=n;j++){
			G.add(i,j+n,INF,c*b[i][j]-a[i][j]);
		}
	}
	return G.mcmf(s,t);
}
int main(){
//	freopen("A.in","r",stdin);
	int n=ni,sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=ni;
			sum+=a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			b[i][j]=ni;
		}
	}
	double l=0,r=(double)sum/n+1,mid;
	while(r-l>=EPS){
		mid=(l+r)/2;
		if(check(mid,n)<=EPS){//tocheck
			l=mid;
		}else{
			r=mid;
		}
	}
	check(l,n);
	G.getlnk(n);
	int up=0,down=0;
	for(int i=1;i<=n;i++){
		up+=a[i][lnk[i]];
		down+=b[i][lnk[i]];
	}
	printf("%.6lf",(double)up/down);
}
