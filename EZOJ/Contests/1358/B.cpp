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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
const int N=20,INF=0x7f7f7f7f;
char tp[N];
int r[N],b[N],ans=INF;
bool vis[N];
int n;
void dfs(int x,int rcnt,int bcnt,int R,int B,int tim){
	if(tim>=ans){
		return;
	}
	if(x==0){
		ans=tim;
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int dig=max(max(max(r[i]-R,0)-rcnt,max(b[i]-B,0)-bcnt),0);
			vis[i]=true;
			dfs(x-1,rcnt+dig-max(r[i]-R,0),bcnt+dig-max(b[i]-R,0),R+(tp[i]=='R'),B+(tp[i]=='B'),tim+dig+1);
			vis[i]=false;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chip.in","r",stdin);
	freopen("chip.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		tp[i]=nc(),r[i]=ni,b[i]=ni;
	}
	memset(vis,0,sizeof(vis));
	dfs(n,0,0,0,0,0);
	printf("%d\n",ans);
	return 0;
}
