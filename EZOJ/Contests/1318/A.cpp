#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
using namespace std;
typedef long long lint;
#define cout cerr
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=4010;
int MOD;
inline int mod(const int &x){
	return x>=MOD?x-MOD:x;
}
inline int mod(const lint &x){
	return x>=MOD?x%MOD:x;
}
inline int add(const int &a,const int &b){
	return mod(a+b);
}
inline int mul(const int &a,const int &b){
	return mod((lint)a*b);
}
inline int sqr(const int &x){
	return mul(x,x);
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int g[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("icefall.in","r",stdin);
	freopen("icefall.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		int n=ni;
		MOD=ni;
		g[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				g[i][j]=add(mul(2,g[i][j-1]),mul(j,g[i-1][j-1]));
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			apadd(ans,sqr(g[i][n]));
			apadd(ans,mul(g[i][n],g[i-1][n]));
		}
		printf("%d\n",mul(ans,2));
	}
}
