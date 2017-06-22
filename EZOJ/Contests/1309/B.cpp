#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=6,E=15;
int n;
namespace k1{
	const int N=55,E=N*2,MOD=998244353;
	inline int add(const int &a,const int &b){
		return (a+b)%MOD;
	}
	inline int sub(const int &a,const int &b){
		return add(a,MOD-b);
	}
	inline int mul(const int &a,const int &b){
		return (lint)a*b%MOD;
	}
	inline void apadd(int &a,const int &b){
		a=add(a,b);
	}
	int to[E],bro[E],head[N],e=0;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int ans=0;
	int size[N];
	void dfs(int x){
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			size[x]+=size[v];
			apadd(ans,sub(mul(size[v],n-size[v]),1));
		}
	}
	inline int work(){
		memset(head,-1,sizeof(head));
		for(int i=1;i<n;i++){
			ae(ni,i);
		}
		dfs(0);
		return ans+1;
	}
}
int node[N][N];
bool con[N][N];
int fa[N];
int root(int x){
	if(fa[x]==-1){
		return x;
	}
	return fa[x]=root(fa[x]);
}
inline bool check(){
	memset(fa,-1,n<<2);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(con[i][j]){
				int x=root(i),y=root(j);
				if(x==y){
					return false;
				}
				fa[x]=y;
			}
		}
	}
	return true;
}
inline int hush(){
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(con[i][j]){
				ans|=1<<node[i][j];
			}
		}
	}
	return ans;
}
bool valid[1<<E],vis[1<<E];
int posx[N*N],posy[N*N];
int dis[1<<E];
queue<int>q;
int main(){
	n=ni;
	int k=ni,ns=0;
	if(k==0){
		puts("1");
		return 0;
	}else if(k==1){
		printf("%d\n",k1::work());
		return 0;
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			node[i][j]=ns;
			posx[ns]=i,posy[ns]=j;
			ns++;
		}
	}
	memset(valid,0,sizeof(valid));
	memset(vis,0,sizeof(vis));
	for(int s=0;s<(1<<ns);s++){
		int cnt=0;
		memset(con,0,sizeof(con));
		for(int i=0;i<ns;i++){
			if((s>>i)&1){
				cnt++;
				con[posx[i]][posy[i]]=true;
			}
		}
		if(cnt==n-1){
			valid[s]=check();
		}
	}
	memset(con,0,sizeof(con));
	for(int i=1;i<n;i++){
		int f=ni;
		con[min(i,f)][max(i,f)]=true;
	}
	memset(dis,-1,sizeof(dis));
	int x=hush();
	assert(valid[x]);
	dis[x]=0;
	q.push(x);
	while(!q.empty()){
		x=q.front();
		q.pop();
		assert(dis[x]<k);
		for(int i=0;i<ns;i++){
			if((x>>i)&1){
				for(int j=0;j<ns;j++){
					if(((x>>j)&1)==0){
						int t=x^(1<<i)^(1<<j);
						if(valid[t]&&dis[t]==-1){
							dis[t]=dis[x]+1;
							if(dis[t]<k){
								q.push(x);
							}
						}
					}
				}
			}
		}
	}
	int cnt=0;
	for(int i=0;i<(1<<ns);i++){
		if(~dis[i]){
			cnt++;
		}
	}
	printf("%d\n",cnt);
}