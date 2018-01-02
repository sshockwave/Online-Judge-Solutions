#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <vector>
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
const int N=110;
namespace G{
	const int N=610;
	int n=0;
	vector<int>to[N];
	int lnk[N],vis[N],tim=0;
	inline void init(){
		n=0;
	}
	inline int nn(){
		to[++n].clear();
		return n;
	}
	inline void add(int u,int v){
		to[u].push_back(v);
		to[v].push_back(u);
	}
	bool dfs(int x){
		assert(lnk[x]==0);
		if(x==0)return true;
		random_shuffle(to[x].begin(),to[x].end());
		assert(vis[x]<tim);
		vis[x]=tim;
		for(vector<int>::iterator it=to[x].begin(),ti=to[x].end();it!=ti;it++){
			int v=*it,w=lnk[v];
			if(vis[w]<tim){
				lnk[x]=v,lnk[v]=x,lnk[w]=0;
				if(dfs(w))return true;
				lnk[w]=v,lnk[v]=w,lnk[x]=0;
			}
		}
		return false;
	}
	inline int max_match(){
		memset(lnk+1,0,n<<2);
		int ans=0;
		for(int i=1;i<=n;i++){
			if(lnk[i]==0){
				tim++;
				ans+=dfs(i);
			}
		}
		return ans;
	}
}
int lnode[N*3],rnode[N][3];
inline void Main(){
	int n=ni,m=ni;
	G::init();
	for(int i=1;i<=n;i++){
		lnode[i]=G::nn();
	}
	int nst=G::n+1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<3;j++){
			rnode[i][j]=G::nn();
		}
		for(int j=0;j<3;j++){
			G::add(rnode[i][j],rnode[i][(j+1)%3]);
		}
	}
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		for(int i=0;i<3;i++){
			G::add(lnode[u],rnode[v][i]);
		}
	}
	printf("%d\n",G::max_match()-n);
	for(int i=1;i<=n;i++){
		printf("%d ",(G::lnk[i]-nst)/3+1);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("npc.in","r",stdin);
	freopen("npc.out","w",stdout);
#endif
	//srand(time(0));
	for(int tot=ni;tot--;){
		Main();
	}
	return 0;
}
