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
int mat[N][N];
int main(){
	int n=ni,m=ni,r=ni,c=ni;
	bool flag=false;
	if(m%c==0){
		swap(n,m),swap(r,c),flag=true;
	}
	if(m%c){
		puts("Yes");
	}else{
		puts("No");
		return 0;
	}
	int a=m/c+1,b=-a-1;
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j+=c){
			mat[i][j]=a,mat[i][j-1]=b;
		}
	}
	if(flag){
		for(int j=1;j<=m;j++){
			for(int i=1;i<=n;i++){
				printf("%d ",mat[i][j]);
			}
			putchar('\n');
		}
	}else{
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				printf("%d ",mat[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;
}
