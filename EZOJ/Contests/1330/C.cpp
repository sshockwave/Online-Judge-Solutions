#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=5010;
int mat[N][N];
int ans[N];
int cel[N],stk[N],cnt[N];
inline void work(int n,int m){
	memset(cel+1,0,m<<2);
	for(int i=1;i<=n;i++){
		int ss=0;
		int sum=0;
		for(int j=1;j<=m;j++){
			cel[j]++;
		}
		for(int j=1;j<=m;j++){
			if(mat[i][j]==-1){
				cel[j]=0;
			}
			int tmp=1;
			for(;ss>=1&&cel[j]<=stk[ss-1];ss--,sum-=stk[ss]*cnt[ss],tmp+=cnt[ss]);
			sum+=cel[j]*tmp;
			stk[ss]=cel[j],cnt[ss]=tmp,ss++;
			if(mat[i][j]>0){
				ans[mat[i][j]]+=sum;
			}
		}
	}
}
inline void work2(int n,int m){
	for(int i=1;i<=n;i++){
		int l=0;
		for(int j=1;j<=m;j++){
			if(mat[i][j]==-1){
				l=j;
			}else if(mat[i][j]){
				ans[mat[i][j]]-=j-l;
			}
		}
	}
}
inline void work3(int n,int m){
	for(int j=1;j<=m;j++){
		int l=0;
		for(int i=1;i<=n;i++){
			if(mat[i][j]==-1){
				l=i;
			}else if(mat[i][j]){
				ans[mat[i][j]]-=i-l;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
#endif
	memset(mat,0,sizeof(mat));
	int n=ni,m=ni,tot1=ni,tot2=ni;
	while(tot1--){
		int x=ni,y=ni;
		mat[x][y]=-1;
	}
	for(int i=1;i<=tot2;i++){
		int x=ni,y=ni;
		mat[x][y]=i;
	}
	work(n,m);
	work2(n,m);
	work3(n,m);
	for(int i=1;i<=n;i++){
		reverse(mat[i]+1,mat[i]+m+1);
	}
	work(n,m);
	for(int j=1;j<=m;j++){
		for(int i=1,t=n;i<t;i++,t--){
			swap(mat[i][j],mat[t][j]);
		}
	}
	work(n,m);
	work2(n,m);
	work3(n,m);
	for(int i=1;i<=n;i++){
		reverse(mat[i]+1,mat[i]+m+1);
	}
	work(n,m);
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]+1);
	}
	return 0;
}
