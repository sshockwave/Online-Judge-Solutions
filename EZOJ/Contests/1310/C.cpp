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
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=1000010,E=N*2;
lint f[E],g[E];
namespace G{
	int to[E],bro[E],val[E],head[N],e=0;
	bool vis[E];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	void dfs1(int x,int e){//pos
		for(int i=head[x];~i;i=bro[i]){
			if(i^e^1){
				dfs1(to[i],i);
				apmax(g[e],max(g[i],f[e]+f[i]+val[i]));
				apmax(f[e],f[i]+val[i]);
			}
		}
	}
	void dfs2(int x,int e,lint f1,lint g1){//rev
		lint f2=0,f3=0,f1f=e^1,f2f=-1,f3f=-1;
		lint g2=0,g1f=e^1,g2f=-1;
		for(int i=head[x];~i;i=bro[i]){
			if(i^e^1){
				lint nf=f[i]+val[i];
				if(nf>f1){
					f3=f2,f3f=f2f;
					f2=f1,f2f=f1f;
					f1=nf,f1f=i;
				}else if(nf>f2){
					f3=f2,f3f=f2f;
					f2=nf,f2f=i;
				}else if(nf>f3){
					f3=nf,f3f=i;
				}
				if(g[i]>g1){
					g2=g1,g2f=g1f;
					g1=g[i],g1f=i;
				}else if(g[i]>g2){
					g2=g[i],g2f=i;
				}
			}
		}
		for(int i=head[x];~i;i=bro[i]){
			if(i^e^1){
				lint curf,curg;
				if(f1f!=i){
					curf=f1;
				}else{
					assert(f2f!=i);
					curf=f2;
				}
				if(g1f!=i){
					curg=g1;
				}else{
					assert(g2f!=i);
					curg=g2;
				}
				if(f1f==i){
					assert(f2f!=i&&f3f!=i);
					apmax(curg,f2+f3);
				}else if(f2f==i){
					assert(f1f!=i&&f3f!=i);
					apmax(curg,f1+f3);
				}else{
					assert(f1f!=i&&f2f!=i);
					apmax(curg,f1+f2);
				}
				f[i^1]=curf,g[i^1]=curg;
				dfs2(to[i],i,curf+val[i],curg);
			}
		}
	}
}
int main(){
	int n=ni;
	G::init();
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		G::add(u,v,ni);
	}
	G::dfs1(1,G::e),G::dfs2(1,G::e,0,0);
	lint sum=0;
	for(int i=1;i<n;i++){
		lint p=g[(i<<1)-2],q=g[(i<<1)-1];
		static const lint MOD=2333333333333333ll;
		(sum+=max(p,q)*23333%MOD)%=MOD;
		(sum+=min(p,q)*2333%MOD)%=MOD;
		(sum+=233ll*i*i+23*i+2)%=MOD;
	}
	printf("%lld\n",sum);
}