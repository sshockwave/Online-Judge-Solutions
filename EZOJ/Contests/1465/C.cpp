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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=55,INF=0x7f7f7f7f;
int n;
namespace G{
	int dis[N][N];
	int to[N],bln[N],to_ed[N];
	inline int geted(int x){
		x=bln[x];
		if(to_ed[x]==x)return x;
		int fa=to_ed[x];
		to_ed[x]=x;
		return to_ed[x]=geted(fa);
	}
	inline int upd_to(int x){
		to[x]=0;
		for(int i=1;i<=n;i++){
			bln[i]=bln[bln[i]];
			assert(bln[bln[i]]==bln[i]);
			if(bln[i]==x)continue;
			if(dis[x][i]<dis[x][to[x]]){
				to[x]=i;
			}
		}
		to_ed[x]=to[x];
		const int v=dis[x][to[x]];
		for(int i=0;i<=n;i++){
			dis[x][i]-=v;
		}
		return v;
	}
	inline int zhuliu(){
		//0 is root
		for(int i=0;i<=n;i++){
			bln[i]=i;
		}
		int ans=0;
		to[0]=to_ed[0]=0;
		for(int i=1;i<=n;i++){
			ans+=upd_to(i);
		}
		for(int x=1;x<=n;x++){
			if(bln[x]!=x)continue;
			for(;geted(x)==x;){
				for(int y=to[x];y=bln[y],y!=x;y=to[y]){
					bln[y]=x;
					for(int i=0;i<=n;i++){
						apmin(dis[x][i],dis[y][i]);
					}
				}
				ans+=upd_to(x);
			}
			assert(geted(x)==0||geted(x)>x);
		}
		return ans;
	}
}
int a[N],b[N],p[N],pos[N];
bool vis[N];
inline void putdis(){
	for(int i=1;i<=n;i++){
		using namespace G;
		dis[i][0]=a[i]^b[i];
		for(int j=1;j<=n;j++){
			dis[i][j]=pos[j]<=pos[i]?a[i]^b[j]:INF;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("pl.in","r",stdin);
	freopen("pl.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=ni;
	}
	mset(pos+1,127,n);
	putdis();
	const int ans=G::zhuliu();
	printf("%d\n",ans);
	mset(vis+1,0,n);
	for(int i=1;i<=n;i++){
		for(int &j=p[i]=1;j<=n;j++){
			if(vis[j])continue;
			vis[j]=true,pos[j]=i;
			putdis();
			if(G::zhuliu()==ans)break;
			vis[j]=false,pos[j]=INF;
		}
		printf("%d ",p[i]);
	}
	putchar('\n');
	return 0;
}
