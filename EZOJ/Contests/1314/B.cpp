#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=510,MOD=998244353;
template<class T>inline int mod(const T &x){
	return x>=MOD?x%MOD:x;
}
inline int add(const int &a,const int &b){
	return mod(a+b);
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return mod((lint)a*b);
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int f[N][N],g[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	int n=ni;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	f[0][0]=f[1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0,_=i/2;j<=_;j++){
			for(int k=1;k<i;k++){//last subtree
				for(int l=0;l<=j;l++){//contribute from last subtree
					apadd(f[i][j],mul(f[i-k][j-l],g[k][l]));
					apadd(g[i][j],mul(g[i-k][j-l],add(f[k][l],g[k][l])));
					if(l){
						apadd(g[i][j],mul(f[i-k][j-l],f[k][l-1]));
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			printf("%d ",add(f[i][i-j],g[i][i-j]));
		}
		putchar('\n');
	}
}
