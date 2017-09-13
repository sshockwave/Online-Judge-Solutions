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
const int N=600,INF=0x7f7f7f7f;
int w[N][N];
int val[N];
int u[N];
int ans=-INF;
int n,m;
int a[N],besta[N];
inline int lb(int x){
	return x&(-x);
}
void dfs(int i,int sum){
	if(i==n){
		if(sum>ans){
			for(int j=0;j<n;j++){
				besta[j]=a[j];
			}
			ans=sum;
		}
		return;
	}
	for(a[i]=0;a[i]<m;a[i]++){
		int dt=w[i][a[i]];
		for(int j=i;j;j^=lb(j)){
			int x=i^lb(j);
			if(a[x]>=val[x]||a[i]>=val[i]){
				dt+=u[i]^u[x];
			}
		}
		dfs(i+1,sum+dt);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ram.in","r",stdin);
	freopen("ram.out","w",stdout);
#endif
	n=1<<ni,m=1<<ni;
	for(int i=0;i<n;i++){
		val[i]=ni;
	}
	for(int i=0;i<n;i++){
		u[i]=ni;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			w[i][j]=ni;
		}
	}
	dfs(0,0);
	for(int i=0;i<n;i++){
		printf("%d ",besta[i]);
	}
	putchar('\n');
	return 0;
}
