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
const int N=100010,INF=0x7f7f7f7f;
int pval[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int liml[N],limr[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(liml,128,sizeof(liml));
		memset(limr,127,sizeof(limr));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool dfs1(int x,int fa){
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(!dfs1(v,x))return false;
				if(limr[v]<INF){
					if(limr[x]==INF){
						liml[x]=liml[v]-1,limr[x]=limr[v]+1;
					}else if((limr[x]&1)!=(limr[v]&1)){
						apmax(liml[x],liml[v]-1);
						apmin(limr[x],limr[v]+1);
						if(liml[x]>limr[x])return false;
					}else return false;
				}
			}
		}
		return true;
	}
	void dfs2(int x,int fa){
		if(fa==0){
			pval[x]=limr[x];
		}else{
			pval[x]=min(limr[x],pval[fa]+1);
			assert(pval[x]>=liml[x]);
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs2(v,x);
			}
		}
	}
}
int main(){
	int n=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	for(int tot=ni;tot--;){
		int x=ni;
		T::liml[x]=T::limr[x]=ni;
	}
	if(!T::dfs1(1,0)){
		puts("No");
		return 0;
	}
	puts("Yes");
	T::dfs2(1,0);
	for(int i=1;i<=n;i++){
		printf("%d\n",pval[i]);
	}
	putchar('\n');
	return 0;
}
