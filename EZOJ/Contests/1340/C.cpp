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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=500010;
bool col[N];
int ans=0;
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
	int dfs(int x,int fa){
		int mx=0,mx2=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				int tmp=dfs(v,x);
				if(col[v]!=col[x]){
					tmp++;
				}
				if(tmp>mx){
					mx2=mx,mx=tmp;
				}else if(tmp>mx2){
					mx2=tmp;
				}
			}
		}
		apmax(ans,mx+mx2);
		return mx;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		col[i]=ni;
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(1,0);
	printf("%d\n",(ans>>1)+(ans&1));
	return 0;
}
