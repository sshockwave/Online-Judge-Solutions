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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=100010,M=18;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int bmask[N];
int pval[M];
int pcnt[1<<M];
int f[1<<M];
bool con[M][M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	const int n=ni,m=ni;
	mset(bmask+1,0,n);
	for(int i=0;i<m;i++){
		pval[i]=ni;
		for(int tot=ni;tot--;){
			bmask[ni]|=1<<i;
		}
	}
	const int sm=1<<m;
	mset(pcnt,0,sm);
	lint ans=0;
	for(int i=1;i<=n;i++){
		++pcnt[bmask[i]];
		lint mnval=LINF;
		for(int a=0;a<m;a++){
			if(((bmask[i]>>a)&1)==0)continue;
			apmin(mnval,pval[a]);
			for(int b=0;b<m;b++){
				if(((bmask[i]>>b)&1)==0)continue;
				con[a][b]=true;
			}
		}
		ans-=mnval;
	}
	for(int s=0;s<sm;s++){
		f[s]=pcnt[s];
	}
	for(int i=0;i<m;i++){
		for(int s=0;s<sm;s++){
			if((s>>i)&1){
				f[s]+=f[s^(1<<i)];
			}
		}
	}
	for(int s=0;s<sm;s++){
		int ts=(sm-1)^s;
		if(s<ts){
			swap(f[s],f[ts]);
		}
	}
	for(int s=0;s<sm;s++){
		f[s]=n-f[s];
	}
	for(int s=0;s<sm;s++){
		if(pcnt[s]==0)continue;
		static bool vis[M];
		static lint dis[M];
		mset(vis,0,m);
		for(int i=0;i<m;i++){
			dis[i]=(s>>i)&1?pval[i]:LINF;
		}
		int ts=0;
		lint sum=0;
		for(int tot=m;tot--;){
			int x=-1;
			for(int i=0;i<m;i++){
				if(!vis[i]){
					if(x==-1||dis[x]>dis[i]){
						x=i;
					}
				}
			}
			vis[x]=true;
			sum+=dis[x]*(f[ts|(1<<x)]-f[ts]);
			ts|=1<<x;
			for(int i=0;i<m;i++){
				if(vis[i])continue;
				if(con[x][i]){
					apmin(dis[i],dis[x]+pval[i]);
				}
			}
		}
		ans+=sum*pcnt[s];
	}
	ans/=2;
	printf("%lld\n",ans);
	return 0;
}
