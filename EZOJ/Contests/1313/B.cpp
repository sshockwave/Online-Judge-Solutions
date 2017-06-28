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
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=10010,D=6,d=ni,E=N*D;
namespace G{
	int fr[E],to[E],bro[E],head[N],e=0;
	inline void ae(const int &u,const int &v){
		fr[e]=u,to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfn[N],low[N],tim=0;
	int stk[N],ss=0;
	bool instk[N];
	int bln[N],sz[N];
	void tarjan(int x){
		dfn[x]=low[x]=++tim;
		stk[ss++]=x;
		instk[x]=true;
		for(int i=head[x],v;~i;i=bro[i]){
			if(dfn[v=to[i]]==0){
				tarjan(v),apmin(low[x],low[v]);
			}else if(instk[v]){
				apmin(low[x],low[v]);
			}
		}
		if(dfn[x]==low[x]){
			int v;
			do{
				sz[x]++;
				v=stk[--ss];
				instk[v]=false;
				bln[v]=x;
			}while(v!=x);
		}
	}
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(instk,0,sizeof(instk));
		memset(sz,0,sizeof(sz));
		memset(bln,-1,sizeof(bln));
	}
}
namespace T{
	int son[N][D],lnk[N];//root=0;
	bool end[N];
	inline void init(){
		memset(son,0,sizeof(son));
	}
	int n=0;
	inline int nn(){
		return ++n;
	}
	inline void ins(char s[]){
		int x=0;
		for(;*s;x=son[x][(*s)-'a'],s++){
			if(son[x][(*s)-'a']==0){
				son[x][(*s)-'a']=nn();
			}
		}
		end[x]=true;
	}
	int que[N];
	inline void bfs(){
		int qh=0,qt=0;
		for(int i=0,j;i<d;i++){
			if((j=son[0][i])){
				if(end[j]){
					son[0][i]=-1;
				}else{
					lnk[que[qt++]=j]=0;
					G::ae(0,j);
				}
			}else{
				G::ae(0,0);
			}
		}
		while(qh<qt){
			int x=que[qh++];
			for(int i=0;i<d;i++){
				int j=son[x][i];
				assert(~j);
				if(j){
					if(end[j]){
						son[x][i]=-1;
					}else{
						int k=lnk[x];
						for(;k&&son[k][i]==0;k=lnk[k]);
						k=son[k][i];
						if(k==-1||end[k]){
							son[x][i]=-1;
						}else{
							lnk[j]=k;
							que[qt++]=j;
						}
					}
				}else{
					int k=x;
					for(;k&&son[k][i]==0;k=lnk[k]);
					son[x][i]=son[k][i];
				}
				if(~son[x][i]){
					G::ae(x,son[x][i]);
				}
			}
		}
	}
}
int f[N],g[N],h[N];
namespace P{
	int to[E],bro[E],head[N],e=0;
	int ind[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(ind,0,sizeof(ind));
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
		ind[v]++;
	}
	int que[N],qh=0,qt=0;
	inline void topsort(){
		for(int i=0;i<=T::n;i++){
			if(G::bln[i]==i&&ind[i]==0){
				que[qt++]=i;
			}
		}
		while(qh<qt){
			int x=que[qh++];
			for(int i=head[x],v;~i;i=bro[i]){
				if((--ind[v=to[i]])==0){
					que[qt++]=v;
				}
			}
		}
	}
	inline int work(){
		T::bfs(),G::tarjan(0);
		memset(f,0,sizeof(f));
		for(int i=0;i<G::e;i++){
			int u=G::bln[G::fr[i]],v=G::bln[G::to[i]];
			if(u==v){
				f[u]++;
			}else{
				ae(u,v);
			}
		}
		topsort();
		memset(g,0,sizeof(g));
		int ans=0;
		for(int p=0;p<qt;p++){
			int x=que[p];
			assert(G::bln[x]==x);
			f[x]-=G::sz[x]-1;
			if(f[x]>1){
				return -1;
			}
			g[x]+=f[x];
			ans+=g[x];
			for(int i=head[x];~i;i=bro[i]){
				g[to[i]]+=g[x];
			}
		}
		for(int p=qt-1;p>=0;p--){
			int x=que[p];
			h[x]=f[x];
			for(int i=head[x];~i;i=bro[i]){
				h[x]+=h[to[i]];
			}
			if(f[x]&&g[x]>f[x]&&h[x]>f[x]){
				return -1;
			}
		}
		return ans;
	}
}
char s[N];
int main(){
	T::init(),G::init(),P::init();
	for(int tot=ni;tot--;){
		scanf("%s",s);
		T::ins(s);
	}
	printf("%d\n",P::work());
}
