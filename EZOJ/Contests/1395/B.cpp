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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2010,D=4;
namespace trie{
	int son[N][D],n;
	int fa[N],thisc[N];
	inline int nn(){
		return ++n;
	}
	int lcp[N][N];
	inline void init(){
		memset(son,0,sizeof(son));
		memset(lcp,0,sizeof(lcp));
	}
	inline void work(int n){
		lcp[1][n]=lcp[n][1]=0;
		for(int i=2;i<=n;i++){
			lcp[i][n]=lcp[n][i]=thisc[i]==thisc[n]?lcp[fa[i]][fa[n]]+1:0;
		}
	}
	int que[N];
	void bfs(){
		int qh=0,qt=0;
		que[qt++]=1;
		thisc[1]=-1;
		while(qh<qt){
			int x=que[qh++];
			lcp[x][1]=lcp[1][x]=0;
			for(int i=1;i<qh;i++){
				int y=que[i];
				lcp[x][y]=lcp[y][x]=thisc[x]==thisc[y]?lcp[fa[x]][fa[y]]+1:0;
			}
			for(int i=0;i<D;i++){
				if(son[x][i]){
					que[qt++]=son[x][i];
				}
			}
		}
	}
}
inline int gchar(){
	char c;
	while(!isalpha(c=getchar()));
	return c=='A'?0:c=='T'?1:c=='C'?2:3;
}
int pval[N];
using trie::n;
int main(){
#ifndef ONLINE_JUDGE
	freopen("gene.in","r",stdin);
	freopen("gene.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	trie::init();
	for(int i=1;i<n;i++){
		int u=ni,v=ni,c=gchar();
		trie::son[u][c]=v;
		trie::fa[v]=u;
		trie::thisc[v]=c;
	}
	trie::bfs();
	for(int ans=1;tot--;){
		if(ni==0){//ask
			int u=ni^ans,l=ni,r=ni;
			int cur=0;
			for(int i=1;i<=n;i++){
				cur+=trie::lcp[u][i]>=l&&pval[i]<=r;
			}
			if(cur){
				ans=cur;
			}
			printf("%d\n",cur);
		}else{//grow
			int x=trie::nn();
			trie::fa[x]=ni^ans;
			pval[x]=ni;
			trie::thisc[x]=gchar();
			trie::son[trie::fa[x]][trie::thisc[x]]=x;
			trie::work(x);
		}
	}
	return 0;
}
