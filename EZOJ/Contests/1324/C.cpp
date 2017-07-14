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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=35,MOD=998244353;
inline int abs(const int &x){
	return x>=0?x:-x;
}
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
bool mat[N<<1][N<<1];
int steps,K;
int f[N][N<<1][N<<1][N];
inline int work(int x,int y){
	memset(f,0,sizeof(f));
	f[0][N][N][x==0&&y==0]=1;
	for(int t=1;t<=steps;t++){
		for(int i=-t;i<=t;i++){
			for(int j=abs(i)-t,tj=t-abs(i);j<=tj;j++){
				if(mat[i+N][j+N]){
					continue;
				}
				bool flag=x==i&&y==j;
				for(int k=flag;k<=K;k++){
					lint tmp=0;
					tmp+=f[t-1][i-1+N][j+N][k-flag];
					tmp+=f[t-1][i+N][j-1+N][k-flag];
					tmp+=f[t-1][i+1+N][j+N][k-flag];
					tmp+=f[t-1][i+N][j+1+N][k-flag];
					f[t][i+N][j+N][k]=tmp%MOD;
				}
				if(flag){
					lint tmp=0;
					tmp+=f[t-1][i-1+N][j+N][K];
					tmp+=f[t-1][i+N][j-1+N][K];
					tmp+=f[t-1][i+1+N][j+N][K];
					tmp+=f[t-1][i+N][j+1+N][K];
					f[t][i+N][j+N][K]+=tmp%MOD;
				}
			}
		}
	}
	lint ans=0;
	for(int i=-steps;i<=steps;i++){
		for(int j=abs(i)-steps,tj=steps-abs(i);j<=tj;j++){
			ans+=f[steps][i+N][j+N][K];
		}
	}
	return ans%MOD;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("wander.in","r",stdin);
	freopen("wander.out","w",stdout);
#endif
	steps=ni;
	int tot=ni;
	K=ni;
	memset(mat,0,sizeof(mat));
	while(tot--){
		int x=ni,y=ni;
		mat[x+N][y+N]=1;
	}
	int ans=0;
	for(int i=-steps;i<=steps;i++){
		for(int j=abs(i)-steps,tj=steps-abs(i);j<=tj;j++){
			apadd(ans,work(i,j));
		}
	}
	printf("%d\n",ans);
	return 0;
}
