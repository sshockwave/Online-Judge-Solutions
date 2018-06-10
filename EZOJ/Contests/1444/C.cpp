#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=410;
int tim;
int dlen;
int mat[N][N];
inline void fill_mat(int x1,int x2,int y1,int y2){
	const int d=dlen;
	for(;y2-y1+1>=d*2;){
		for(int i=x1;i<=x2;i++){
			++tim;
			for(int j=y1;j<=y1+d-1;j++){
				mat[i][j]=tim;
			}
		}
		y1+=d;
	}
	for(;x2-x1+1>=d*2;){
		for(int j=y1;j<=y2;j++){
			++tim;
			for(int i=x1;i<=x1+d-1;i++){
				mat[i][j]=tim;
			}
		}
		x1+=d;
	}
	const int r=x2-x1+1,c=y2-y1+1;
	if(r<=d||c<=d||(r*c+d-1)/d==r/d*c+c/d*(r%d)+min(r%d,c%d)){
		for(;y2-y1+1>=d;){
			for(int i=x1;i<=x2;i++){
				++tim;
				for(int j=y1;j<=y1+d-1;j++){
					mat[i][j]=tim;
				}
			}
			y1+=d;
		}
		for(;x2-x1+1>=d;){
			for(int j=y1;j<=y2;j++){
				++tim;
				for(int i=x1;i<=x1+d-1;i++){
					mat[i][j]=tim;
				}
			}
			x1+=d;
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
	}else{
		const int v=(r*c+d-1)/d-r;
		typedef vector<int>vi;
		vi vec;
		for(int j=0;j<v;j++){
			vec.push_back(j*d%r);
		}
		sort(vec.begin(),vec.end());
		for(int j=0;j<v;j++){
			++tim;
			for(int i=vec[j],t=0;t<d;t++,i=i+1<r?i+1:0){
				mat[i+x1][j+y1]=tim;
			}
		}
		for(int i=x1;i<=x2;i++){
			++tim;
			for(int j=y1;j<=y2;j++){
				if(mat[i][j]==0){
					mat[i][j]=tim;
				}
			}
		}
	}
}
inline void Main(){
	int r=ni,c=ni;
	dlen=ni;
	tim=0;
	for(int i=1;i<=r;i++){
		mset(mat[i]+1,0,c);
	}
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
