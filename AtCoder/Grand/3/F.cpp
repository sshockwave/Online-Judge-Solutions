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
const int N=1010,O=1000000007;
inline int fpow(int x,lint n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
struct Mat{
	const static int N=3;
	int a[N][N];
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				lint tmp=0;
				for(int k=0;k<N;k++){
					tmp+=(lint)a.a[i][k]*b.a[k][j]%O;
				}
				c.a[i][j]=tmp%O;
			}
		}
		return c;
	}
}trans,res=(Mat){1,0,0,0,1,0,0,0,1};
inline void matfpow(lint n){
	if(n==0){
		res=(Mat){1,0,0,0,1,0,0,0,1};
		return;
	}
	matfpow(n>>1);
	res=res*res;
	if(n&1){
		res=res*trans;
	}
}
char mat[N][N];
inline int Main(){
	int n=ni,m=ni;
	lint tot=next_num<lint>();
	if(tot<=1)return 1;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	int hor=0,ver=0;
	for(int i=1;i<=n;i++){
		hor+=mat[i][1]=='#'&&mat[i][m]=='#';
	}
	for(int j=1;j<=m;j++){
		ver+=mat[1][j]=='#'&&mat[n][j]=='#';
	}
	if(hor&&ver)return 1;
	if(!(hor||ver)){
		int cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cnt+=mat[i][j]=='#';
			}
		}
		return fpow(cnt,tot-1);
	}
	if(ver){
		for(int i=1,ti=max(n,m);i<=ti;i++){
			for(int j=1;j<i;j++){
				swap(mat[i][j],mat[j][i]);
			}
		}
		swap(hor,ver),swap(n,m);
	}
	memset(&trans,0,sizeof(trans));
	for(int i=1;i<=n;i++){
		bool all=true;
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='#'){
				trans.a[2][1]++;
				trans.a[2][2]++;
				if(mat[i][j-1]!='#'){
					trans.a[2][0]++;
					trans.a[2][1]++;
				}
			}else{
				all=false;
			}
		}
		if(all){
			trans.a[2][0]--;
			trans.a[0][0]++;
		}else if(mat[i][1]=='#'&&mat[i][m]=='#'){
			trans.a[2][0]-=2;
			trans.a[1][0]++;
		}
		if(mat[i][1]=='#'&&mat[i][m]=='#'){
			trans.a[2][1]-=2;
			trans.a[1][1]++;
		}
	}
	matfpow(tot-2);
	int vec[Mat::N]={0,0,0};
	for(int i=1;i<=n;i++){
		bool all=true;
		int cnt=0;
		for(int j=1;j<=m;j++){
			if(mat[i][j]=='#'){
				if(mat[i][j-1]!='#'){
					cnt++;
				}
			}else{
				all=false;
			}
		}
		if(all){
			vec[0]++;
		}else if(mat[i][1]=='#'&&mat[i][m]=='#'){
			vec[1]++;
			vec[2]+=cnt-2;
		}else{
			vec[2]+=cnt;
		}
	}
	lint ans=0;
	for(int i=0;i<Mat::N;i++){
		lint tmp=0;
		for(int j=0;j<Mat::N;j++){
			tmp+=(lint)res.a[i][j]*vec[j]%O;
		}
		ans+=tmp<<(i==1);
	}
	return ans%O;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
