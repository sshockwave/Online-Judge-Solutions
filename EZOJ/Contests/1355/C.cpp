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
const int N=1010,N2=N*N,L=20000010;
char s[L],*mat[N2];
int nxt[N2][4],dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int node[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("appoint.in","r",stdin);
	freopen("appoint.out","w",stdout);
#endif
	int n=ni,m=ni,tot=ni;
	char *str=s;
	for(int i=0,ti=n+1;i<=ti;i++){
		for(int j=0,tj=m+1;j<=tj;j++){
			static int nn=0;
			node[i][j]=++nn;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%s",mat[node[i][j]]=str);
			while(*(str++));
			for(int d=0;d<4;d++){
				int tx=i+dx[d],ty=j+dy[d];
				nxt[node[i][j]][d]=node[tx][ty];
				nxt[node[tx][ty]][d^2]=node[i][j];
			}
		}
	}
	while(tot--){
		int x1=ni,y1=ni,x2=ni,y2=ni,r=ni,c=ni;
		int p1=node[x1][0],p2=node[x2][0];
		for(int i=1;i<=y1;p1=nxt[p1][1],i++);
		for(int i=1;i<=y2;p2=nxt[p2][1],i++);
		int len[]={c,r,c,r};
		for(int d=0;d<4;d++){
			int t=(d+1)&3;
			for(int i=1;i<=len[d];p1=nxt[p1][t],p2=nxt[p2][t],i++){
				assert(p1&&p2);
				assert(nxt[nxt[p1][d]][d^2]==p1);
				assert(nxt[nxt[p2][d]][d^2]==p2);
				swap(nxt[nxt[p1][d]][d^2],nxt[nxt[p2][d]][d^2]);
				swap(nxt[p1][d],nxt[p2][d]);
			}
			p1=nxt[p1][t^2],p2=nxt[p2][t^2];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1,p=node[i][0];p=nxt[p][1],j<=m;j++){
			printf("%s ",mat[p]);
		}
		putchar('\n');
	}
	return 0;
}
