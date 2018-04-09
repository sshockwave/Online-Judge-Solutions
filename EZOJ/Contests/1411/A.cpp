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
const int N=110;
int n,k;
char mat[N][N];
int ext[N];
char extc[N];
inline bool check(int a,int b){
	char c='2';
	for(int i=a;i<a+k;i++){
		for(int j=b;j<b+k;j++){
			if(c<'2'&&mat[i][j]<'2'&&c!=mat[i][j])return false;
			if(mat[i][j]<'2'){
				c=mat[i][j];
			}
		}
	}
	return c<'2';
}
inline void mak(int a,int b){
	for(int i=a;i<a+k;i++){
		for(int j=b;j<b+k;j++){
			mat[i][j]='2';
		}
	}
}
inline bool work(){
	for(int i=1;i<=n-k+1;i++){
		for(int j=1;j<=n-k+1;j++){
			if(check(i,j)){
				mak(i,j);
				return true;
			}
		}
	}
	return false;
}
inline int Main(){
	n=ni,k=ni;
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	while(work());
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mat[i][j]<'2')return false;
		}
	}
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		putchar('0'+Main());
		putchar('\n');
	}
	return 0;
}
