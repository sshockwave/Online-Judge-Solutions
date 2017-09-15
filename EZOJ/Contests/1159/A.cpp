#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <vector>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=1000010,INF=0x7f7f7f7f;
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	int deg[N],size[N],hei[N],dep[N],minhei[N];
	struct szcmp{
		inline bool operator () (int a,int b){
			return size[a]<size[b];
		}
	};
	priority_queue<int,vector<int>,szcmp>q;
	inline void init(){
		dep[1]=0;
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
		deg[u]++,deg[v]++;
	}
	void dfs(int x){//get size && hei && dep
		hei[x]=0;
		size[x]=1;
		minhei[x]=INF;
		int scnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dep[v=to[i]]=dep[x]+1;
			dfs(v);
			size[x]+=size[v];
			apmax(hei[x],hei[v]);
			apmin(minhei[x],minhei[v]);
			scnt++;
		}
		if(scnt<2){
			minhei[x]=0;
		}
		hei[x]++,minhei[x]++;
	}
	int cur[N];
	inline int bfs(int k){
		int cnt=0;
		for(q.push(1);!q.empty();cnt++){
			int n=0;
			for(;n<k&&!q.empty();cur[++n]=q.top(),q.pop());
			for(int t=1;t<=n;t++){
				for(int i=head[cur[t]];~i;i=bro[i]){
					q.push(to[i]);
				}
			}
		}
		return cnt;
	}
	int cnt[N];
	inline bool isbin(int n){
		memset(cnt,0,n<<2);
		if(deg[1]>2){
			return false;
		}
		for(int i=1;i<=n;i++){
			if(deg[i]>3){
				return false;
			}
			int diff=hei[i]-minhei[i];
			if(diff>1){
				return false;
			}
			if((cnt[dep[i]]+=diff)>1){
				return false;
			}
		}
		return true;
	}
}
inline bool istype1(int n){
	for(int i=1;i<=n;i++){
		if(T::deg[i]>2){
			return false;
		}
	}
	return true;
}
inline int calbin(int k,int n){
	int cnt=0;
	for(;(1<<cnt)<=k&&(1<<(cnt+1))-1<=n;cnt++);
	int rest=n-((1<<cnt)-1);
	return cnt+rest/k+(rest%k!=0);
}
int K[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sup.in","r",stdin);
	freopen("sup.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=tot;i++){
		K[i]=ni;
	}
	T::init();
	for(int i=2;i<=n;i++){
		T::ae(ni,i);
	}
	T::dfs(1);
	if(istype1(n)){
		if(T::deg[1]==1){
			for(int i=1;i<=tot;i++){
				printf("%d ",n);
			}
		}else{
			assert(T::deg[1]==2);
			for(int i=1;i<=tot;i++){
				printf("%d ",K[i]>=2?T::hei[1]:n);
			}
		}
	}else if(T::isbin(n)){
		for(int i=1;i<=tot;i++){
			printf("%d ",calbin(K[i],n));
		}
	}else for(int i=1;i<=tot;i++){
		printf("%d ",T::bfs(K[i]));
	}
	putchar('\n');
	return 0;
}
