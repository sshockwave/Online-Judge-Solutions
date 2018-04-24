#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=1000010,facN=300,lenN=22,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
typedef vector<int>vi;
vi fact[N];
int factlen[N];
int goto1[N];
inline void init(int n){
	for(int i=1;i<=n;i++){
		factlen[i]=1;
		for(vi::iterator it=fact[i].begin(),ti=fact[i].end();it!=ti;++it){
			apmax(factlen[i],factlen[*it]+1);
		}
		for(int j=i;j<=n;j+=i){
			fact[j].push_back(i);
		}
		for(vi::iterator it=fact[i].begin(),ti=fact[i].end();it!=ti;++it){
		}
	}
}
lint dp[N][lenN];
int f[N],c[N];
int luccnt,lucnum[N];
int isluc[N],timluc=0;
int qry[N],m;
int base;
inline void work_dp(int x){
	if(x==1){
		dp[x][0]=0;
		return;
	}
	for(int i=1;i<=factlen[x];i++){
		dp[x][i]=LINF;
	}
	for(vi::iterator it=fact[x].begin(),ti=fact[x].end();it!=ti;++it){
		int v=*it;
		for(int k=v==1?0:1;k<factlen[v];k++){
			apmin(dp[x][k+1],dp[v][k]+f[fact[x/v].size()]);
		}
	}
	if(isluc[x]==timluc){
		int curc=c[base*x];
		for(int i=1;i<factlen[x];i++){
			apmin(dp[x][i+1],dp[x][i]+curc);
		}
	}
}
inline lint Main(){
	int a=ni,b=ni;
	if(a%b)return -m;
	vi vec;
	++timluc;
	for(int i=1;i<=luccnt;i++){
		if(a%lucnum[i]==0&&lucnum[i]%b==0){
			isluc[lucnum[i]/b]=timluc;
			vec.push_back(lucnum[i]);
			//vecans
		}
	}
	base=b;
	int dt=a/b;
	for(vi::iterator it=fact[dt].begin(),ti=fact[dt].end();it!=ti;++it){
		work_dp(*it);
	}
	lint ans=0;
	for(int i=1;i<=m;i++){
		int L=qry[i];
		if(L<=factlen[i]){
			ans+=dp[dt][L];
		}else{
			lint cur=LINF;
			for(vi::iterator it=vec.begin(),ti=vec.end();it!=ti;++it){
				//cout get ans
			}
			ans+=cur<LINF?cur:-1;
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gauss.in","r",stdin);
	freopen("gauss.out","w",stdout);
#endif
	mset(f,0,N-1);
	for(int i=1,ti=ni;i<=ti;i++){
		f[i]=ni;
	}
	init(N-1);
	m=ni;
	for(int i=1;i<=m;i++){
		qry[i]=ni;
	}
	luccnt=ni;
	for(int i=1;i<=luccnt;i++){
		lucnum[i]=ni,c[lucnum[i]]=ni;
	}
	for(int tot=ni;tot--;){
		printf("%lld\n",Main());
	}
	return 0;
}
