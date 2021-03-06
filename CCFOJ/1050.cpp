#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=110;
int a[N][N],b[N][N];
int main(){
	int n=ni,m=ni,k=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++){
			scanf("%d",&b[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			int cur=0;
			for(int x=1;x<=m;x++){
				cur+=a[i][x]*b[x][j];
			}
			printf("%d ",cur);
		}
		putchar('\n');
	}
}