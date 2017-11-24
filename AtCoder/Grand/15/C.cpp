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
const int N=2010;
char mat[N][N];
int __deg[N][N],_deghor[N][N],_degver[N][N];
int main(){
	int n=ni,m=ni,tot=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	memset(__deg,0,sizeof(__deg));
	memset(_deghor,0,sizeof(_deghor));
	memset(_degver,0,sizeof(_degver));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='1'){
				__deg[i][j]=-2;
				static const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
				for(int d=0;d<4;d++){
					__deg[i][j]+=mat[i+dx[d]][j+dy[d]]=='1';
				}
			}
			__deg[i][j]+=__deg[i-1][j]+__deg[i][j-1]-__deg[i-1][j-1];
			_deghor[i][j]=_deghor[i][j-1]+(mat[i][j]=='1'&&mat[i-1][j]=='1');
			_degver[i][j]=_degver[i-1][j]+(mat[i][j]=='1'&&mat[i][j-1]=='1');
		}
	}
	while(tot--){
		int x1=ni,y1=ni,x2=ni,y2=ni;
		int sum=__deg[x2][y2]-__deg[x1-1][y2]-__deg[x2][y1-1]+__deg[x1-1][y1-1];
		sum-=_deghor[x1][y2]-_deghor[x1][y1-1];
		sum-=_deghor[x2+1][y2]-_deghor[x2+1][y1-1];
		sum-=_degver[x2][y1]-_degver[x1-1][y1];
		sum-=_degver[x2][y2+1]-_degver[x1-1][y2+1];
		printf("%d\n",(-sum)>>1);
	}
	return 0;
}
