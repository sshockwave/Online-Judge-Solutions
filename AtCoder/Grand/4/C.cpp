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
const int N=510;
char mat[N][N];
bool b[N][N];
int main(){
	memset(b,0,sizeof(b));
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
		for(int j=i&1?min(2,m):m;j<=m;j++){
			b[i][j]=true;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			putchar(mat[i][j]=='#'||b[i][j]?'#':'.');
		}
		putchar('\n');
	}
	putchar('\n');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			putchar(mat[i][j]=='#'||!b[i][j]?'#':'.');
		}
		putchar('\n');
	}
	return 0;
}
