#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double ld;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=51;
ld f[2][N][N];
inline double work(int n,int m){
	memset(f,0,sizeof(f));
	if(n>m){
		swap(n,m);
	}
	bool r=false;
	f[r][1][1]=1;
	int sz=n*m;
	ld ans=0,lst=0;
	for(int p=1;p<sz;p++,r=!r){
		ans+=(f[r][n][m]-lst)*p,lst=f[r][n][m];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				f[!r][i][j]=0;
			}
		}
		ld rst=sz-p;
		for(int i=1,ti=min(n,p);i<=ti;i++){
			for(int j=1,tj=min(m,p);j<=tj;j++){
				ld cur=f[r][i][j]/rst;
				if(i<n&&j<m){
					f[!r][i+1][j+1]+=(n-i)*(m-j)*cur;
				}
				if(p<i*j){
					f[!r][i][j]+=(i*j-p)*cur;
				}
				if(i<n){
					f[!r][i+1][j]+=(n-i)*j*cur;
				}
				if(j<m){
					f[!r][i][j+1]+=(m-j)*i*cur;
				}
			}
		}
	}
	ans+=(f[r][n][m]-lst)*sz;
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%.12lf\n",work(ni,ni));
	}
	return 0;
}
