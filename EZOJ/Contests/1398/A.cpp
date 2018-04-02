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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=500010,INF=0x7f7f7f7f;
int leflst[N],lefst[N],lefed[N];
inline int popedge(int x){
	if(lefst[x]<lefed[x]){
		return leflst[lefst[x]++];
	}else return leflst[lefst[x]-1];
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e;
	int deg[N];
	inline void init(int n){
		memset(head+1,-1,n*sizeof(head[0]));
		memset(deg+1,0,n*sizeof(deg[0]));
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
		deg[u]++,deg[v]++;
	}
	int g;
	int gcen(int x,int fa,int lefcnt){
		int sum=deg[x]==1,mx=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				int tmp=gcen(v,x,lefcnt);
				sum+=tmp,apmax(mx,tmp);
			}
		}
		apmax(mx,lefcnt-sum);
		if((mx<<1)<=lefcnt){
			g=x;
		}
		return sum;
	}
	void dfs(int x,int fa,int &ls){
		if(deg[x]==1){
			leflst[ls++]=x;
		}else for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x,ls);
			}
		}
	}
}
struct qcmp{
	inline bool operator () (const int &a,const int &b){
		return lefed[a]-lefst[a]<lefed[b]-lefst[b];
	}
};
int pruf[N],prufnd[N],prufcnt[N];
inline void Main(){
	int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	if(n<=2){
		puts("0");
		return;
	}
	int lefcnt=0,mxd=0;
	for(int i=1;i<=n;i++){
		lefcnt+=T::deg[i]==1;
		apmax(mxd,T::deg[i]);
	}
	printf("%d\n",max(mxd-1,(lefcnt+1)>>1));
	T::gcen(1,0,lefcnt);
	assert(T::deg[T::g]>1);
	int m=0;
	priority_queue<int,vector<int>,qcmp>q;
	for(int i=T::head[T::g];~i;i=T::bro[i]){
		m++,lefst[m]=lefed[m]=lefed[m-1];
		T::dfs(T::to[i],T::g,lefed[m]);
		q.push(m);
		prufcnt[m]=0;
	}
	for(int i=1;i<=m-2;i++){
		pruf[i]=q.top(),q.pop();
		prufnd[i]=popedge(pruf[i]);
		prufcnt[pruf[i]]++;
		q.push(pruf[i]);
	}
	priority_queue<int>s;
	for(int i=1;i<=m;i++){
		if(prufcnt[i]==0){
			s.push(i);
		}
	}
	for(int i=1;i<=m-2;i++){
		printf("%d %d\n",popedge(s.top()),prufnd[i]);
		s.pop();
		if(--prufcnt[pruf[i]]==0){
			s.push(pruf[i]);
		}
	}
	{//last two
		int x=s.top(),y=(s.pop(),s.top());
		printf("%d %d\n",popedge(x),popedge(y));
	}
	for(int x;x=q.top(),lefed[x]-lefst[x]>0;){
		q.pop();
		int y=q.top();
		q.pop();
		printf("%d %d\n",popedge(x),popedge(y));
		q.push(x),q.push(y);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("struct.in","r",stdin);
	freopen("struct.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		Main();
	}
	return 0;
}
