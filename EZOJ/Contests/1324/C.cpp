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
inline int cabs(const int &x){
	return x>=0?x:-x;
}
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
bool mat[N<<1][N<<1];
int steps,K;
int f[N][N<<1][N<<1];
inline void trans(int t,int x,int y,int v){
	if(mat[x][y]){
		return;
	}
	apadd(f[t][x-1][y],v);
	apadd(f[t][x][y-1],v);
	apadd(f[t][x+1][y],v);
	apadd(f[t][x][y+1],v);
}
inline void search1(int x,int y){
	memset(f,0,sizeof(f));
	f[0][N][N]=1;
	for(int t=0;t<steps;t++){
		for(int i=-t;i<=t;i++){
			for(int j=cabs(i)-t,tj=t-cabs(i);j<=tj;j++){
				if(x!=i||y!=j){
					trans(t+1,i+N,j+N,f[t][i+N][j+N]);
				}
			}
		}
	}
}
inline void search2(int x,int y,int steps){
	memset(f,0,sizeof(f));
	f[0][x+N][y+N]=1;
	for(int t=0;t<steps;t++){
		for(int i=-t;i<=t;i++){
			for(int j=cabs(i)-t,tj=t-cabs(i);j<=tj;j++){
				if(t==0||i||j){
					trans(t+1,i+x+N,j+y+N,f[t][i+x+N][j+y+N]);
				}
			}
		}
	}
}
inline void search3(int x,int y,int steps,int a[]){
	memset(f,0,sizeof(f));
	f[0][x+N][y+N]=1;
	for(int t=0;t<steps;t++){
		lint cnt=0;
		for(int i=-t;i<=t;i++){
			for(int j=cabs(i)-t,tj=t-cabs(i);j<=tj;j++){
				trans(t+1,i+x+N,j+y+N,f[t][i+x+N][j+y+N]);
				if(!mat[i+x+N][j+y+N]){
					cnt+=f[t][i+x+N][j+y+N];
				}
			}
		}
		a[t]=cnt%MOD;
	}
	lint cnt=0;
	for(int i=-steps;i<=steps;i++){
		for(int j=cabs(i)-steps,tj=steps-cabs(i);j<=tj;j++){
			if(!mat[i+x+N][j+y+N]){
				cnt+=f[steps][i+x+N][j+y+N];
			}
		}
	}
	a[steps]=cnt%MOD;
}
int g[N],h[N],any[N];
inline int work(int x,int y){
	search1(x,y);
	int dis1=cabs(x)+cabs(y);
	for(int i=dis1;i<=steps;i++){
		g[i]=f[i][x+N][y+N];
	}
	search2(x,y,steps-dis1);
	for(int i=2,ti=steps-dis1;i<=ti;i+=2){
		h[i]=f[i][x+N][y+N];
	}
	for(int i=1;i<K;i++){
		for(int j=steps,tj=dis1+((i-1)<<1);j>=tj;j--){
			for(int k=j+2;k<=steps;k+=2){
				apadd(g[k],mul(g[j],h[k-j]));
			}
			g[j]=0;
		}
	}
	search3(x,y,steps-dis1-(K-1)*2,any);
	lint ans=0;
	for(int i=dis1+(K-1)*2;i<=steps;i++){
		ans+=mul(g[i],any[steps-i]);
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
		for(int j=cabs(i)-steps,tj=steps-cabs(i);j<=tj;j++){
			if(!mat[i+N][j+N]){
				apadd(ans,work(i,j));
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
