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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=5010,INF=0x7f7f7f7f;
int f[2][N][N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int leaf[N];
	int g[2][N];
	void dfs(int x,int fa){
		if(bro[head[x]]==-1){
			leaf[x]=1;
			f[0][x][0]=0;
			f[1][x][1]=0;
			return;
		}
		leaf[x]=0;
		f[0][x][0]=0;
		f[1][x][0]=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				memset(g[0],127,(leaf[x]+leaf[v]+1)<<2);
				memset(g[1],127,(leaf[x]+leaf[v]+1)<<2);
				for(int d=0;d<2;d++){
					for(int j=leaf[v];j>=0;j--){
						lint tmp=f[d][v][j];
						if(tmp<INF){
							for(int k=leaf[x];k>=0;k--){
								apmin(g[d][j+k],tmp+f[d][x][k]);
								apmin(g[!d][j+k],tmp+f[!d][x][k]+1);
							}
						}
					}
				}
				leaf[x]+=leaf[v];
				memcpy(f[0][x],g[0],(leaf[x]+1)<<2);
				memcpy(f[1][x],g[1],(leaf[x]+1)<<2);
			}
		}/*
		for(int i=0;i<=leaf[x];i++){
			cout<<"f[0]["<<x<<"]["<<i<<"]="<<f[0][x][i]<<endl;
			cout<<"f[1]["<<x<<"]["<<i<<"]="<<f[1][x][i]<<endl;
		}*/
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	if(n==2){
		puts("1");
		return 0;
	}
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	int rt=1;
	for(int &i=rt;i<=n&&T::bro[T::head[i]]==-1;i++);
	memset(f,127,sizeof(f));
	T::dfs(rt,0);
	assert((T::leaf[rt]&1)==0);
	int tmp=T::leaf[rt]>>1;
	printf("%d\n",min(f[0][rt][tmp],f[1][rt][tmp]));
	return 0;
}
