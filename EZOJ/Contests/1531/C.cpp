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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1010,D=8;
//#define PRECALC
#ifdef PRECALC
int mat[N][N];
const int dx[]={-3,-2,0,2,3,2,0,-2};
const int dy[]={0,2,3,2,0,-2,-3,-2};
int n;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n;
}
inline bool check(){
	//if(mat[3][5]+1!=mat[5][3])return false;
	if(mat[1][3]+1!=mat[3][5])return false;
	if(mat[3][3]!=n*n)return false;
	for(int d=0;d<8;d++){
		int tx=1+dx[d],ty=1+dy[d];
		if(valid(tx,ty)&&mat[tx][ty]==n*n)return true;
	}
	return false;
}
int cnt=0;
void dfs(int x,int y,int tim){
	mat[x][y]=tim;
	if(tim==n*n){
		if(check()){
			++cnt;
			cout<<"found solution!"<<endl;
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					cout<<mat[i][j]<<",";
				}
				cout<<endl;
			}
		}
	}else{
		for(int d=0;d<8;d++){
			int tx=x+dx[d],ty=y+dy[d];
			if(valid(tx,ty)&&mat[tx][ty]==0){
				dfs(tx,ty,tim+1);
			}
		}
	}
	mat[x][y]=0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("camel.in","r",stdin);
	freopen("camel.out","w",stdout);
#endif
	n=5;
	dfs(1,1,1);
	cout<<"cnt="<<cnt<<endl;
	return 0;
}
#else
int A[5][5]={
	1,14,6,9,15,
	21,11,3,18,23,
	5,8,25,13,7,
	2,17,22,10,16,
	20,12,4,19,24
};
int B[5][5]={
	1,11,18,4,10,
	16,22,8,13,23,
	19,5,25,20,6,
	2,12,17,3,9,
	15,21,7,14,24
};
int mat[N][N];
inline void putmat(int (*A)[5],int dx,int dy,int px,int py){
	py-=6;
	for(int i=1;i<=5;i++){
		for(int j=1;j<=5;j++){
			mat[i+dx][j+dy]=A[i-1][j-1]+(A[i-1][j-1]<=6?px:py);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("camel.in","r",stdin);
	freopen("camel.out","w",stdout);
#endif
	const int n=ni;
	const int tn=n/5;
	for(int i=1;i<=tn;i++){
		for(int j=1;j<=tn;j++){
			const int dt1=((i-1)*tn+(j-1))*6;
			const int dt2=((tn-i)*tn+(tn-j))*19;
			putmat(j<tn?A:B,(i-1)*5,(j-1)*5,dt1,tn*tn*6+dt2);
		}
	}
	for(int i=2;i<=tn;i+=2){
		for(int j=1;j<=5;j++){
			int ln=(i-1)*5+j;
			reverse(mat[ln]+1,mat[ln]+n+1);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ",mat[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
#endif
