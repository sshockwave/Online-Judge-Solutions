#include <iostream>
#include <cstring>
#include <cstdio>
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
const int N=2010,O=998244353;
inline void apadd(int &a,const int &b){
	a=(a+b)%O;
}
namespace gmath{
	const int N=::N*3;
	inline int fpow(int x,int n){
		int a=1;
		for(;n;n>>=1,x=(lint)x*x%O){
			if(n&1){
				a=(lint)a*x%O;
			}
		}
		return a;
	}
	inline int inv(int x){
		return fpow(x,O-2);
	}
	int fac[N],invfac[N];
	inline void init(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
		invfac[n]=inv(fac[n]);
		for(int i=n;i>=1;i--){
			invfac[i-1]=(lint)invfac[i]*i%O;
		}
	}
	inline int A(int n,int k){
		if(n<k)return 0;
		if(k==0)return 1;
		if(k==1)return n;
		if(k==2)return (lint)n*(n-1)%O;
		return (lint)fac[n]*invfac[n-k]%O;
	}
}
int n;
bool vis[3][N],mat[3][N];
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
inline bool valid(int x,int y){
	return x>=0&&x<3&&y>=1&&y<=n;
}
void mark(int x,int y){
	vis[x][y]=true;
	for(int d=0;d<4;d++){
		int tx=x+dx[d],ty=y+dy[d];
		int tx2=tx+dx[d],ty2=ty+dy[d];
		if(!valid(tx2,ty2))continue;
		if(vis[tx2][ty2]&&!vis[tx][ty]){
			mark(tx,ty);
		}
	}
}
char s[N];
int f[N][N][2];
inline int Main(){
	n=ni;
	gmath::init(n*3);
	memset(vis,0,sizeof(vis));
	memset(mat,0,sizeof(mat));
	for(int i=0;i<3;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			mat[i][j]=s[j]=='o';
			if(mat[i][j]){
				mark(i,j);
			}
		}
	}
	for(int i=0;i<3;i++){
		for(int j=1;j<=n;j++){
			if(!vis[i][j])return 0;
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		const int newcnt=!mat[0][i]+!mat[1][i]+!mat[2][i],sum=cnt+newcnt;
		memset(f[i],0,sizeof(f[i][0])*(sum+1));
		if(i==1){
			if(mat[1][i]){
				f[i][0][0]=1;
			}else{
				f[i][sum][0]=gmath::fac[newcnt-1];
			}
		}else for(int j=0,tj=mat[1][i-1]?0:cnt;j<=tj;j++){
			using gmath::A;
			lint F=f[i-1][j][0];
			if(F){
				/*
				   trans to [0]
				   requirements
				   if mat[1][i]==1 then new j==0 && the other two is arbitrary
				   else the other two has to go before j
				 */
				if(mat[1][i]){
					apadd(f[i][0][0],F*A(sum,newcnt)%O);
				}else for(int nj=newcnt;nj<=sum;nj++){
					apadd(f[i][nj][0],F*A(nj-1,newcnt-1)%O);
				}
				/*
				   trans to [1]
				   requirements
				   mat[1][i]==0
				   mat[1][i-1]==1 || old j < new j
				   at least one of mat[0][i] and mat[2][i] is > new j
				 */
				if(mat[1][i]==0&&newcnt>1){
					for(int nj=j+1;nj<=sum;nj++){//insert after nj
						if(newcnt>1&&j+newcnt-2<nj){//ins one after nj
							apadd(f[i][nj][1],F*(newcnt-1)*(sum-nj)%O*A(nj-1,newcnt-2)%O);
						}
						if(newcnt>2){//ins two after nj
							apadd(f[i][nj][1],F*A(sum-nj,2)%O);
						}
					}
				}
			}
			F=f[i-1][j][1];
			if(F){
				/*
				   new j < j
				   therefore no trans to [1]
				   trans to [0]
				   if mat[1][i]==1 then new j==0 && the other two is arbitrary
				   else the other two has to go before j
				 */
				if(mat[1][i]){
					apadd(f[i][0][0],F*A(sum,newcnt)%O);
				}else for(int nj=newcnt;nj<j+newcnt;nj++){
					apadd(f[i][nj][0],F*A(nj-1,newcnt-1)%O);
				}
			}
		}
		cnt=sum;
	}
	lint ans=0;
	for(int j=0;j<=cnt;j++){
		ans+=f[n][j][0];
	}
	return ans%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("disembrangle.in","r",stdin);
	freopen("disembrangle.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
