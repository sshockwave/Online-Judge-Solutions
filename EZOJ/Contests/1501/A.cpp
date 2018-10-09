#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100,INF=0x7f7f7f7f;
bool con[N][N];
int lim;
namespace solve1{
	int cnt[N];
	bool vis[N];
	bool main(int n,int m){
		int rest=lim;
		mset(vis+1,0,m);
		for(;;){
			mset(cnt+1,0,n);
			for(int i=1;i<=m;i++){
				if(vis[i])continue;
				for(int j=1;j<=n;j++){
					cnt[j]+=con[i][j];
				}
			}
			int mxp=1;
			for(int j=2;j<=n;j++){
				if(cnt[j]>cnt[mxp]){
					mxp=j;
				}
			}
			if(cnt[mxp]==0)return false;
			if(rest==0)return false;
			--rest;
			bool okay=true;
			for(int i=1;i<=m;i++){
				vis[i]|=con[i][mxp];
				okay&=vis[i];
			}
			if(okay)return true;
		}
		return false;
	}
}
namespace solve2{
	int cnt[N];
	bool vis[N];
	int perm[N];
	bool main(int n,int m){
		for(int i=1;i<=m;i++){
			perm[i]=i;
		}
		random_shuffle(perm+1,perm+m+1);
		int rest=lim;
		mset(vis+1,0,m);
		for(int tt=1;tt<=m;tt++){
			if(vis[perm[tt]])continue;
			if(rest==0)return false;
			mset(cnt+1,0,n);
			for(int i=1;i<=m;i++){
				if(vis[i])continue;
				for(int j=1;j<=n;j++){
					cnt[j]+=con[i][j];
				}
			}
			int mxp=-1;
			for(int j=2;j<=n;j++){
				if(con[perm[tt]][j]){
					if(mxp==-1||cnt[j]>cnt[mxp]){
						mxp=j;
					}
				}
			}
			if(mxp==-1||cnt[mxp]==0)return false;
			--rest;
			for(int i=1;i<=m;i++){
				vis[i]|=con[i][mxp];
			}
		}
		return true;
	}
}
namespace solve3{
	int nn,mm;
	int cnt[N];
	int perm[N];
	int vis[N];
	bool dfs(int x,int ccnt){
		if(x>nn){
			for(int i=1;i<=mm;i++){
				if(vis[i]==0)return false;
			}
			return true;
		}
		if(ccnt<lim&&cnt[x]){
			for(int j=1;j<=mm;j++){
				if(con[j][x]){
					if(vis[j]==0){
						for(int p=1;p<=nn;p++){
							if(con[j][p]){
								--cnt[p];
							}
						}
					}
					vis[j]+=1;
				}
			}
			if(dfs(x+1,ccnt+1))return true;
			for(int j=1;j<=mm;j++){
				if(con[j][x]){
					vis[j]-=1;
					if(vis[j]==0){
						for(int p=1;p<=nn;p++){
							if(con[j][p]){
								++cnt[p];
							}
						}
					}
				}
			}
		}
		return dfs(x+1,ccnt);
	}
	bool main(int n,int m){
		nn=n,mm=m;
		mset(cnt+1,0,n);
		mset(vis+1,0,n);
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				cnt[j]+=con[i][j];
			}
		}
		return dfs(1,0);
	}
}
inline bool solve(int n,int m){
	if(solve1::main(n,m))return true;
	if(solve2::main(n,m))return true;
	if(solve2::main(n,m))return true;//cout
	return false;
}
int val[N];
char s1[N],s2[N],t[N];
inline int calc(char s[],int i,int j){
	return cabs(s[i]-t[j])+val[cabs(i-j)];
}
int n;
namespace brute{
	bool dci[N];
	inline int calc2(char s[],int i){
		int ans=INF;
		for(int j=1;j<=n;j++){
			if(dci[j]){
				apmin(ans,calc(s,i,j));
			}
		}
		return ans;
	}
	int ans;
	inline void calc(){
		int cur=0;
		for(int i=1;i<=n;i++){
			apmax(cur,calc2(s1,i));
			apmax(cur,calc2(s2,i));
		}
		apmin(ans,cur);
	}
	void dfs(int x,int ccnt){
		if(x>n){
			if(ccnt!=lim)return;
			calc();
			return;
		}
		if(ccnt<lim){
			dci[x]=true;
			dfs(x+1,ccnt+1);
		}
		if((n-x)+ccnt>=lim){
			dci[x]=false;
			dfs(x+1,ccnt);
		}
	}
	inline int main(){
		ans=INF;
		dfs(1,0);
		return ans;
	}
}
inline int Main(){
	n=ni;
	lim=ni;
	for(int i=0;i<n;i++){
		val[i]=ni;
	}
	scanf("%s%s%s",s1+1,s2+1,t+1);
	if(n<=20)return brute::main();//cout
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			apmax(r,calc(s1,i,j));
			apmax(r,calc(s2,i,j));
		}
	}
	for(;l<r;){
		const int m=(l+r)>>1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				con[i][j]=calc(s1,i,j)<=m;
				con[i+n][j]=calc(s2,i,j)<=m;
			}
		}
		if(solve(n,n<<1)){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
#endif
	for(int i=1,tot=ni;i<=tot;i++){
		printf("Case #%d: %d\n",i,Main());
	}
	return 0;
}
