#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <algorithm>
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
const int N=2010;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
bool con[N][N];
int n,a[N];
struct cmp2{
	inline bool operator () (int x,int y){
		return a[x]<a[y];
	}
};
int dfn[N],tim=0;
int lst[N];
void dfs(int x){
	dfn[x]=++tim;
	for(int i=1,v;i<=n;i++){
		if(dfn[v=lst[i]]==0&&con[x][v]){
			dfs(v);
		}
	}
}
int deg[N];
inline void topsort(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(con[i][j]&&dfn[i]<dfn[j]){
				deg[j]++;
			}
		}
	}
	priority_queue<int,vector<int>,cmp2>q;
	for(int i=1;i<=n;i++){
		if(deg[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int x=q.top();
		q.pop();
		printf("%d ",a[x]);
		for(int v=1;v<=n;v++){
			if(con[x][v]&&dfn[x]<dfn[v]&&(--deg[v])==0){
				q.push(v);
			}
		}
	}
}
inline bool lcmp(int x,int y){
	return a[x]<a[y];
}
int main(){
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		lst[i]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			con[i][j]=gcd(a[i],a[j])!=1;
		}
	}
	sort(lst+1,lst+n+1,lcmp);
	memset(dfn,0,sizeof(dfn));
	for(int i=1;i<=n;i++){
		if(dfn[lst[i]]==0){
			dfs(lst[i]);
		}
	}
	topsort();
	putchar('\n');
	return 0;
}
