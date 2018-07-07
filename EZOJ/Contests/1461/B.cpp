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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1010;
int a[N];
bool f[N][N];
bool a_inc[N][N],a_dec[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("gameb.in","r",stdin);
	freopen("gameb.out","w",stdout);
#endif
	const int n=ni,tp=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int len=1;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			const int j=i+len-1;
			if(len==1){
				a_inc[i][j]=a_dec[i][j]=true;
			}else{
				a_inc[i][j]=a[i]<=a[i+1]&&a_inc[i+1][j];
				a_dec[i][j]=a[i]>=a[i+1]&&a_dec[i+1][j];
			}
			if((tp==1&&a_inc[i][j])||(tp==2&&(a_inc[i][j]||a_dec[i][j]))){
				f[i][j]=0;
			}else{
				f[i][j]=!f[i+1][j]||!f[i][j-1];
			}
		}
	}
	for(int tot=ni;tot--;){
		const int l=ni,r=ni;
		puts(f[l][r]?"se":"liulei");
	}
	return 0;
}
