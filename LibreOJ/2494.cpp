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
const int N=1010,M=5010,O=1000000007;
unsigned mat[N][M/32+1],cur[M/32+1],impo[N][M/32+1];
int m,mtop;
char s[M];
int pw2[N];
lint ans;
inline bool any(unsigned int a[]){
	for(int i=0;i<=mtop;i++){
		if(a[i])return true;
	}
	return false;
}
void dfs(int x){
	if(x==0){
		for(int i=0;i<=mtop;i++){
			if(impo[0][i]&cur[i])return;
		}
		ans++;
		return;
	}
	if(!any(impo[x])){
		ans+=pw2[x];
		return;
	}
	bool andok=true,orok=true;
	for(int i=0;i<=mtop;i++){
		if(impo[x][i]&mat[x][i]&~cur[i]){
			orok=false;
		}
		if(impo[x][i]&~mat[x][i]&cur[i]){
			andok=false;
		}
		if(!orok&&!andok)break;
	}
	if(orok){
		for(int i=0;i<=mtop;i++){
			impo[x-1][i]=impo[x][i]&~mat[x][i];
		}
		dfs(x-1);
	}
	if(andok){
		for(int i=0;i<=mtop;i++){
			impo[x-1][i]=impo[x][i]&mat[x][i];
		}
		dfs(x-1);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hunt.in","r",stdin);
	freopen("hunt.out","w",stdout);
#endif
	int n=ni;
	m=ni,mtop=m>>5;
	int q=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			mat[i][j>>5]|=(unsigned)(s[j]=='1')<<(j&31);
		}
	}
	pw2[0]=1;
	for(int i=1;i<=n;i++){
		pw2[i]=(pw2[i-1]<<1)%O;
	}
	for(int i=1;i<=q;i++){
		scanf("%s",s+1);
		mset(cur,0,mtop+1);
		for(int j=1;j<=m;j++){
			cur[j>>5]|=(unsigned)(s[j]=='1')<<(j&31);
			impo[n][j>>5]|=1u<<(j&31);
		}
		ans=0,dfs(n);
		printf("%lld\n",ans%O);
	}
	return 0;
}
