#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=410;
int tim;
int dlen;
int mat[N][N];
inline void fill_mat(int x1,int x2,int y1,int y2){
	for(;y2-y1+1>=dlen;){
		for(int i=x1;i<=x2;i++){
			++tim;
			for(int j=y1;j<=y1+dlen-1;j++){
				mat[i][j]=tim;
			}
		}
		y1+=dlen;
	}
	for(;x2-x1+1>=dlen;){
		for(int j=y1;j<=y2;j++){
			++tim;
			for(int i=x1;i<=x1+dlen-1;i++){
				mat[i][j]=tim;
			}
		}
		x1+=dlen;
	}
	if(x2-x1<y2-y1){//flat
		for(int i=x1;i<=x2;i++){
			++tim;
			for(int j=y1;j<=y2;j++){
				mat[i][j]=tim;
			}
		}
	}else{//tall
		for(int j=y1;j<=y2;j++){
			++tim;
			for(int i=x1;i<=x2;i++){
				mat[i][j]=tim;
			}
		}
	}
}
inline void Main(){
	int r=ni,c=ni,d=dlen=ni;
	int lb;
	tim=0;
	fill_mat(1,r,1,c);
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			printf("%d ",mat[i][j]);
		}
		putchar('\n');
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("patience.in","r",stdin);
	freopen("patience.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
