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
const int N=10;
int vis[N*N],posx[N*N],posy[N*N],ps=0;
int cur=0,ans=0,ex,ey,n,m;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
void dfs(){
	if(cur>ans){
		ans=cur;
	}
	for(int i=0;i<ps;i++){
		if(vis[i]==0){
			vis[i]++,cur++;
			int dx=ex-posx[i],dy=ey-posy[i];
			for(int j=0;j<ps;j++){
				posx[j]+=dx,posy[j]+=dy;
				if(!valid(posx[j],posy[j])){
					vis[j]++;
				}
			}
			dfs();
			vis[i]--,cur--;
			for(int j=0;j<ps;j++){
				if(!valid(posx[j],posy[j])){
					vis[j]--;
				}
				posx[j]-=dx,posy[j]-=dy;
			}
		}
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("exit.in","r",stdin);
	freopen("exit.ans","w",stdout);
#endif
	n=ni,m=ni;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='o'){
				posx[ps]=i,posy[ps]=j,ps++;
			}else if(s[j]=='E'){
				ex=i,ey=j;
			}
		}
	}
	dfs();
	printf("%d\n",ans);
	return 0;
}
