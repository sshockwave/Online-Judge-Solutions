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
const int N=12,S=184756,INF=0x7f7f7f7f;
int n,m;
int val[N][N];
int idx[N][N];
int pos[N];
int f[S];
void dfs(int x,int id,int step){
	if(x==0){
		int &ans=f[id]=step&1?INF:-INF;
		if(id==idx[n][m])return ans=0,void();
		for(int i=1;i<=n;i++){
			if(pos[i]<pos[i-1]){
				int nid=id;
				nid-=idx[i][pos[i]]-idx[i-1][pos[i]];
				nid+=idx[i][pos[i]+1]-idx[i-1][pos[i]+1];
				if(step&1){
					apmin(ans,f[nid]);
				}else{
					apmax(ans,f[nid]+val[i][pos[i]+1]);
				}
			}
		}
		return;
	}
	for(int &i=pos[x]=m;i>=pos[x+1];i--){
		dfs(x-1,id+idx[x][i]-idx[x-1][i],step+i);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
#endif
	n=ni,m=ni;
	memset(idx,0,sizeof(idx));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			idx[i][j]=idx[i][j-1]+(1+idx[i-1][m]-idx[i-1][j-1]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			val[i][j]=ni;
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int b=ni;
			sum-=b,val[i][j]+=b;
		}
	}
	pos[0]=m,pos[n+1]=0;
	dfs(n,0,0);
	printf("%d\n",f[0]+sum);
	return 0;
}
