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
const int N=3010;
namespace G{
	const int E=3010;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
}
namespace G2{
	const int E=3010;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
}
int lnk[N],cnt[N],tag[N],tag2[N],tim=0;
bool dfs(int x){
	if((cnt[x]&1)==0)return true;
	using namespace G;
	for(int i=head[x],v,w;~i;i=bro[i]){
		if((w=lnk[v=to[i]])==x){
			if(tag2[v]==tim)continue;
			tag2[v]=tim;
			for(int j=G2::head[v],u;~j;j=G2::bro[j]){
				u=G2::to[j];
				cnt[x]--,cnt[u]++,lnk[v]=u;
				if(dfs(u))return true;
				cnt[x]++,cnt[u]--,lnk[v]=x;
			}
		}else{
			if(tag[w]==tim)continue;
			tag[w]=tim;
			cnt[w]--,cnt[x]++,lnk[v]=x;
			if(dfs(w))return true;
			cnt[w]++,cnt[x]--,lnk[v]=w;
		}
	}
	return false;
}
inline int Main(int n,int m){
	G::init(m),G2::init(n);
	memset(lnk+1,0,n<<2);
	memset(cnt+1,0,m<<2);
	for(int i=1;i<=m;i++){
		for(int tot=ni;tot--;){
			int c=ni;
			G::ae(i,c);
			G2::ae(c,i);
			if(lnk[c]==0){
				lnk[c]=i;
				cnt[i]++;
			}
		}
	}
	for(int i=1;i<=m;i++){
		tag[i]=++tim,dfs(i);
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		ans+=cnt[i]>>1;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("study.in","r",stdin);
	freopen("study.out","w",stdout);
#endif
	for(int n,m;n=ni,m=ni,n&&m;){
		printf("%d\n",Main(n,m));
	}
	return 0;
}
