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
const int N=200010;
int x[N],y[N];
bool vis[N];
bool dfs(int i){
	if(i==0){
		return true;
	}
	if(vis[i]){
		return dfs(i-1);
	}
	for(int j=1;j<i;j++){
		if(!vis[j]&&(x[i]==x[j]||y[i]==y[j])){
			vis[i]=vis[j]=true;
			if(dfs(i-1)){
				return true;
			}
			vis[i]=vis[j]=false;
		}
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
#endif
	int n=(ni<<1)+1;
	for(int i=1;i<=n;i++){
		x[i]=ni,y[i]=ni;
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		vis[i]=true;
		puts(dfs(n)?"OK":"NG");
	}
	return 0;
}
