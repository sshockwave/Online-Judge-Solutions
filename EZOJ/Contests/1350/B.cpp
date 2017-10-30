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
const int N=510;
char mat[N][N];
int hor[N][N],ver[N][N],all[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	memset(mat,'#',sizeof(mat));
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	memset(hor,0,sizeof(hor));
	memset(ver,0,sizeof(ver));
	memset(all,0,sizeof(all));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			hor[i][j]=hor[i][j-1]+(mat[i][j]=='.'&&mat[i-1][j]=='.');
			ver[i][j]=ver[i-1][j]+(mat[i][j]=='.'&&mat[i][j-1]=='.');
			all[i][j]=all[i][j-1]+ver[i][j];
			for(int k=2;k<=i;k++){
				if(mat[k-1][j]=='.'&&mat[k][j]=='.'){
					all[i][j]++;
				}
			}
		}
	}
	for(int tot=ni;tot--;){
		int x1=ni,y1=ni,x2=ni,y2=ni;
		int part1=all[x2][y2]-all[x1-1][y2]-all[x2][y1-1]+all[x1-1][y1-1];
		int part2=hor[x1][y2]-hor[x1][y1-1];
		int part3=ver[x2][y1]-ver[x1-1][y1];
		printf("%d\n",part1-part2-part3);
	}
	return 0;
}
