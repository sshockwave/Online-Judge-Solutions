#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <map>
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
const int N=1010,M=35,O=998244353;
int c[N][N],fac[N];
inline void gmath(int n){
	memset(c,0,sizeof(c));
	for(int i=0;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%O;
		}
	}
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
}
int g[M][M],n,m;
int ginv[M];
int que[M];
inline int gstate(int s){
	int qh=0,qt=0;
	for(int i=1;i<=m;i++){
		if((s>>i)&1){
			que[qt++]=i;
		}
	}
	while(qh<qt){
		int x=que[qh++];
		for(int i=1;i<=m;i++){
			if((s>>i)&1){
				if(((s>>g[x][i])&1)==0){
					s|=1<<g[x][i];
					que[qt++]=g[x][i];
				}
				if(((s>>g[i][x])&1)==0){
					s|=1<<g[i][x];
					que[qt++]=g[i][x];
				}
			}
		}
	}
	return s;
}
set<int>subg;
void dfs(int s){
	if(subg.find(s)!=subg.end())return;
	subg.insert(s);
	for(int i=1;i<=m;i++){
		if(((s>>i)&1)==0){
			dfs(gstate(s|(1<<i)));
		}
	}
}
inline bool valid(int s){
	for(int i=1;i<=m;i++){
		if((s>>i)&1){
			for(int j=1;j<=m;j++){
				bool flag=false;
				for(int k=1;k<=m;k++){
					if(((s>>k)&1)&&g[i][j]==g[j][k]){
						flag=true;
						break;
					}
				}
				if(!flag)return false;
			}
		}
	}
	return true;
}
int cnt[M],f[N];
inline int calc(int s){
	memset(cnt+1,0,m<<2);
	for(set<int>::iterator it=subg.begin(),ti=subg.end();it!=ti;it++){
		int t=*it;
		if((s|t)==t){
			int bitcnt=0;
			for(int i=1;i<=m;i++){
				bitcnt+=(t>>i)&1;
			}
			assert(m%bitcnt==0);
			cnt[m/bitcnt]++;
		}
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		lint ans=0;
		for(int j=1;j<=m&&j<=i;j++){
			if(cnt[j]){
				ans+=(lint)c[i-1][j-1]*fac[j-1]%O*cnt[j]%O*f[i-j]%O;
			}
		}
		f[i]=ans%O;
	}
	return f[n];
}
map<int,int>ans;
inline int Main(){
	n=ni,m=ni;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			g[i][j]=ni;
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=m;k++){
				if(g[i][g[j][k]]!=g[g[i][j]][k])return 0;
			}
		}
	}
	subg.clear(),dfs(0),subg.erase(0);
	ans.clear();
	for(set<int>::iterator it=subg.begin(),ti=subg.end();it!=ti;it++){
		if(valid(*it)){
			ans[*it]=calc(*it);
		}
	}
	for(map<int,int>::iterator it=ans.end(),ti=ans.begin();it!=ti;){
		lint tmp=0;
		for(map<int,int>::iterator it2=it--,ti=ans.end();it2!=ti;it2++){
			if((it->first|it2->first)==it2->first){
				tmp+=it2->second;
			}
		}
		it->second=(it->second+O-tmp%O)%O;
	}
	return ans.begin()->second;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("monkey.in","r",stdin);
	freopen("monkey.out","w",stdout);
#endif
	gmath(N-1);
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
