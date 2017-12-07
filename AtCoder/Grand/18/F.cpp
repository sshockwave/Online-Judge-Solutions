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
const int N=100010;
#define clr(x) memset(x,0,sizeof(x))
int alnk[N],blnk[N];
int acnt[N],bcnt[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],ahead[N],bhead[N],e=0;
	inline void init(){
		memset(ahead,-1,sizeof(ahead));
		memset(bhead,-1,sizeof(bhead));
	}
	inline void ae(int u,int v,int head[]){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfs(int x,int head[],int lnk[],int cnt[]){
		int u=cnt[x]&1?0:x;
		for(int i=head[x];~i;i=bro[i]){
			int v=dfs(to[i],head,lnk,cnt);
			u=u?lnk[u]=v,lnk[v]=u,0:v;
		}
		assert(u);
		return u;
	}
}
int col[N];
void dfs(int x){
	if(alnk[x]&&col[alnk[x]]==0){
		col[alnk[x]]=-col[x];
		dfs(alnk[x]);
	}
	if(blnk[x]&&col[blnk[x]]==0){
		col[blnk[x]]=-col[x];
		dfs(blnk[x]);
	}
}
int main(){
	int n=ni,art,brt;
	T::init(),clr(alnk),clr(blnk),clr(acnt),clr(bcnt);
	for(int i=1;i<=n;i++){
		int fa=ni;
		if(fa==-1){
			art=i;
		}else{
			acnt[fa]++;
			T::ae(fa,i,T::ahead);
		}
	}
	for(int i=1;i<=n;i++){
		int fa=ni;
		if(fa==-1){
			brt=i;
		}else{
			bcnt[fa]++;
			T::ae(fa,i,T::bhead);
		}
	}
	for(int i=1;i<=n;i++){
		if((acnt[i]&1)!=(bcnt[i]&1)){
			puts("IMPOSSIBLE");
			return 0;
		}
	}
	puts("POSSIBLE");
	T::dfs(art,T::ahead,alnk,acnt);
	T::dfs(brt,T::bhead,blnk,bcnt);
	for(int i=1;i<=n;i++){
		if(!(acnt[i]&1)&&col[i]==0){
			col[i]=1;
			dfs(i);
		}
		printf("%d ",col[i]);
	}
	putchar('\n');
	return 0;
}
