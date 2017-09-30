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
const int N=210,M=410;
int mat[N][M],nmat[N][M];
int des[N];
inline void Main(){
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mat[i][j]=ni;
		}
	}
	int tot=1;
	for(int i=1;i<=n;i++){
		des[i]=i;
		tot*=i;
	}
	for(;tot--;next_permutation(des+1,des+n+1)){
		for(int i=1;i<=n;i++){
			bool flag=false;
			for(int j=1;j<=m;j++){
				if(mat[i][j]==des[i]){
					flag=true;
				}
				nmat[i][j]=flag?des[i]:mat[i][j];
			}
		}
		bool flag=true;
		for(int j=1;j<=m&&flag;j++){
			bool vis[n+1];
			for(int i=1;i<=n;i++){
				vis[i]=false;
			}
			for(int i=1;i<=n;i++){
				if(mat[i][j]&&vis[nmat[i][j]]){
					flag=false;
				}
				vis[nmat[i][j]]=true;
			}
		}
		if(flag){
			for(int i=1;i<=n;i++){
				printf("%d ",des[i]);
			}
			putchar('\n');
			return;
		}
	}
	puts("\\(^o^)/");
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
