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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=12,S=65,N2=12*12;
lint ans=0;
lint g[S];
int n,gcnt,n2;
int col[N],cs=0;
namespace lb{
	const int N=::N2;
	lint a[N];
	inline void init(){
		memset(a,0,n2*sizeof(a[0]));
	}
	inline bool ins(lint x){//true if inserted
		for(int i=n2-1;i>=0;i--){
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					return true;
				}
			}
		}
		return false;
	}
}
lint mu[]={0,1,-1,2,-6,24,-120,720,-5040,40320,-362880};
void dfs(int x,int cs){
	if(x>n){
		lint mask=0;
		int ps=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				mask|=(lint)(col[i]!=col[j])<<ps++;
			}
		}
		lb::init();
		int cnt=0;
		for(int i=1;i<=gcnt;i++){
			cnt+=!lb::ins(g[i]&mask);
		}
		ans+=mu[cs]<<cnt;
		return;
	}
	col[x]=cs+1,dfs(x+1,cs+1);
	for(int &i=col[x]=1;i<=cs;i++){
		dfs(x+1,cs);
	}
}
lint dfs2(int x,int cs){
	if(x==0)return mu[cs];
	lint ans=dfs2(x-1,cs+1);
	ans+=cs*dfs2(x-1,cs);
	return ans;
}
char s[N2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	gcnt=ni;
	memset(g,0,sizeof(g));
	for(int i=1;i<=gcnt;i++){
		scanf("%s",s);
		for(int j=0;s[j];j++){
			g[i]|=(lint)(s[j]-'0')<<j;
		}
	}
	n2=strlen(s);
	for(n=0;n*(n-1)/2!=n2;n++);/*
	memset(mu,0,sizeof(mu));
	mu[1]=1;
	for(int i=2;i<=n;i++){
		mu[i]=-dfs2(i,0);
	}*/
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
