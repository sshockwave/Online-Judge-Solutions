#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 50010
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int k[N],b[N],rlist[N],stk[N],stop=0;
bool vis[N];
bool rlistcmp(int u,int v){
	return k[u]<k[v];
}
inline bool omit(int x){
	long long k1=k[stk[stop-2]],b1=b[stk[stop-2]],k2=k[stk[stop-1]],b2=b[stk[stop-1]],k3=k[x],b3=b[x];
	return b3*k2-k3*b2>=k1*(b3-b2)+b1*(k2-k3);
}
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		scanf("%d%d",k+i,b+i);
		rlist[i]=i;
	}
	sort(rlist+1,rlist+1+n,rlistcmp);
	for(int i=1;i<=n;i++){
		while(stop>1&&omit(rlist[i])){
			stop--;
		}
		stk[stop++]=rlist[i];
	}
	memset(vis,0,sizeof(vis));
	for(int i=0;i<stop;i++){
		vis[stk[i]]=true;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){
			printf("%d ",i);
		}
	}
}
