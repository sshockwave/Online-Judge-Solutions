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
const int N=3010,N2=N*N;
int n,m;
int mat[N][N],tim=0;
int quex[N2],quey[N2],qh=0,qt=0;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline void psh(int x,int y){
	if(mat[x][y]==tim)return;
	mat[x][y]=tim;
	quex[qt]=x,quey[qt]=y,qt++;
}
inline void bfs(){
	int tx[4],ty[4];
	bool val[4],fil[4];
	while(qh<qt){
		int x=quex[qh],y=quey[qh];
		assert(valid(x,y));
		qh++;
		for(int d=0;d<4;d++){
			tx[d]=x+dx[d],ty[d]=y+dy[d];
			val[d]=valid(tx[d],ty[d]);
			fil[d]=mat[tx[d]][ty[d]]==tim;
		}
		for(int d1=0,d2=1;d1<4;++d1,(++d2)&=3){
			if(val[d1]&&fil[d1]&&val[d2]&&fil[d2]){
				psh(x+dx[d1]+dx[d2],y+dy[d1]+dy[d2]);
			}
		}
		for(int d=0;d<4;d++){
			if(!(val[d]&&fil[d]))continue;
			int d2=(d+1)&3;
			if(val[d2]&&!fil[d2]){
				int tx2=tx[d]+dx[d2],ty2=ty[d]+dy[d2];
				if(valid(tx2,ty2)&&mat[tx2][ty2]==tim){
					psh(tx[d2],ty[d2]);
				}
			}
			d2=(d+3)&3;
			if(val[d2]&&!fil[d2]){
				int tx2=tx[d]+dx[d2],ty2=ty[d]+dy[d2];
				if(valid(tx2,ty2)&&mat[tx2][ty2]==tim){
					psh(tx[d2],ty[d2]);
				}
			}
		}
	}
}
char s[N][N];
inline void bd(){
	qh=qt=0;
	tim++;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='x'){
				psh(i,j);
			}
		}
	}
	bfs();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
#endif
	n=ni,m=ni;
	int tot=ni;
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
	}
	bd();
	for(int n2=n*m;puts(qt==n2?"S":"U"),tot--;){
		int x=ni,y=ni;
		if(s[x][y]=='x'){
			s[x][y]='.';
			bd();
		}else{
			s[x][y]='x';
			psh(x,y);
			bfs();
		}
	}
	return 0;
}
